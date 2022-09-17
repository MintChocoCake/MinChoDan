#include "stdafx.h"
#include "TileMgr.h"



CTileMgr*   CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize(void)
{
	// ?
	m_vecTile.reserve(TILE_X * TILE_Y);

	for (int i = 0; i < TILE_Y; ++i)
	{
		for (int j = 0; j < TILE_X; ++j)
		{
			float	fX = float((TILE_CX >> 1) + (j * TILE_CX));
			float	fY = float((TILE_CY >> 1) + (i * TILE_CY));

			CObj*	pObj = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pObj);
		}
	}
}

void CTileMgr::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	TCHAR	szBuf[128] = L"";

	int iCullX = abs((int)CScrollMgr::Get_Instance()->Get_Scroll_X() / TILE_CX);
	int iCullY = abs((int)CScrollMgr::Get_Instance()->Get_Scroll_Y() / TILE_CY);

	int iCullEndX = iCullX + WINCX / TILE_CX + 2;
	int	iCullEndY = iCullY + WINCY / TILE_CY + 2;
	
	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = 0; j < iCullEndX; ++j)
		{
			int		iIndex = i * TILE_X + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;
			
			m_vecTile[iIndex]->Render(hDC);
			// 타일 인덱스 
			/*wsprintf(szBuf, L"%d", iIndex);
			TextOut(hDC, m_vecTile[iIndex]->Get_Info().fX,
				m_vecTile[iIndex]->Get_Info().fY, szBuf, lstrlen(szBuf));*/
		}
	}
}

void CTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
	// 늘어난 vector 의 버퍼 줄이기 ?
}

void CTileMgr::Picking_Tile(POINT _pt, const int & _iDrawID, const int & _iOption)
{
	int x = _pt.x / TILE_CX;
	int y = _pt.y / TILE_CY;

	int	iIndex = y * TILE_X + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);
	
}

void CTileMgr::Save_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../IsData/Tile.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	int			iDrawID = 0, iOption = 0;
	DWORD		dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();

		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 성공"), L"성공", MB_OK);
}

void CTileMgr::Load_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../IsData/Tile.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	INFO		tInfo{};
	int			iDrawID = 0, iOption = 0;

	Release();
	// 데이터가 겹치지 않게 불러오기전 릴리즈를 통해 메모리를 비워준다.

	while (true)
	{
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		
		CObj*	pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pObj)->Set_Option(iOption);

		m_vecTile.push_back(pObj);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 성공"), L"성공", MB_OK);
}
