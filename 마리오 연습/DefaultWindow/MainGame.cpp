#include "stdafx.h"
#include "MainGame.h"

CMainGame::CMainGame()
	: m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);
	/*
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CLineMgr::Get_Instance()->Initialize();

	// 더블 버퍼링을위해 2개 ?
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/background_mountain1.bmp", L"Ground"); // 배경1
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/background_mountain2.bmp", L"Back");  // 배경2

	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/878295734368210975.bmp", L"logo"); // 로고
	*/

	// 씬 매니저 사용시 
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Map/1-1.bmp", L"Back");
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/background_mountain1.bmp", L"Ground");
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Logo/878295734368210975.bmp", L"Logo");
	CSceneMgr::Get_Instance()->Scen_Change(CSceneMgr::SC_LOGO);
	//CSceneMgr::Get_Instance()->Scen_Change(CSceneMgr::SC_MENU);
	//CSceneMgr::Get_Instance()->Scen_Change(CSceneMgr::SC_STAGE);
	
	
}

void CMainGame::Update(void)
{
	// 신 매니저 사용 전
	/*CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();*/

	// 신 매니저 사용 시
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	// 신 매니저 사용 전
	/*CLineMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();*/

	// 신 매니저 사용 시
	CScrollMgr::Get_Instance()->Scroll_Lock();
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		TCHAR		szBuff[32] = L"";

		HDC hLogoDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"logo");

		BitBlt(m_DC, 0, 0, WINCX, WINCY, hLogoDC, 0, 0, SRCCOPY);

		wsprintf(szBuff, L"엔터키를 눌러주세요.");
		TextOut(m_DC, 400, 300, szBuff, lstrlen(szBuff));
	}*/

	// 씬 매니저 사용전
	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		m_bLogo = true;
	}

	if (false == m_bLogo)
	{
		HDC hLogoDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"logo");

		BitBlt(m_DC, 0, 0, WINCX, WINCY, hLogoDC, 0, 0, SRCCOPY);
	}

	else
	{
		++m_iFPS;

		if (m_dwTime + 1000 < GetTickCount())
		{
			swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
			SetWindowText(g_hWnd, m_szFPS);

			m_iFPS = 0;
			m_dwTime = GetTickCount();
		}

		Rectangle(m_DC, 0, 0, WINCX, WINCY);*/


		// 수정모드 
		/*
		TCHAR		szBuff[32] = L"";
		// 좌표 테스트
		POINT		Show_pt{};
		POINT		Show_pt2{};

		GetCursorPos(&Show_pt);
		ScreenToClient(g_hWnd, &Show_pt);

		GetCursorPos(&Show_pt2);
		ScreenToClient(g_hWnd, &Show_pt2);

		Show_pt2.x -= (long)CScrollMgr::Get_Instance()->Get_Scroll_X();
		Show_pt2.y -= (long)CScrollMgr::Get_Instance()->Get_Scroll_Y();


		wsprintf(szBuff, L"Mouse_X : %d", (int)Show_pt.x);
		TextOut(m_DC, 20, 50, szBuff, lstrlen(szBuff));
		wsprintf(szBuff, L"Mouse_Y : %d", (int)Show_pt.y);
		TextOut(m_DC, 20, 100, szBuff, lstrlen(szBuff));

		wsprintf(szBuff, L"Mouse_X+Scroll_X : %d", (int)Show_pt2.x);
		TextOut(m_DC, 20, 150, szBuff, lstrlen(szBuff));
		wsprintf(szBuff, L"Mouse_Y+Scroll_Y : %d", (int)Show_pt2.y);
		TextOut(m_DC, 20, 200, szBuff, lstrlen(szBuff));

		float Player_fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
		float Player_fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;

		wsprintf(szBuff, L"PlayerX : %d", (int)Player_fX);
		TextOut(m_DC, 20, 250, szBuff, lstrlen(szBuff));
		wsprintf(szBuff, L"PlayerY : %d", (int)Player_fY);
		TextOut(m_DC, 20, 300, szBuff, lstrlen(szBuff));

		CLineMgr::Get_Instance()->Render(m_DC);
		CObjMgr::Get_Instance()->Render(m_DC);
		*/
		// 텍스처 출력
		
		// 각각 하나씩 사용하는 2중버퍼? 라 핸들을 따로 만들어줌
	// 씬 매니저 사용전
		/*
		HDC hBackDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Back");
		HDC hGroundDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Ground");

		// 깜빡 거림 해결법 : 2중 버퍼
		BitBlt(hBackDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

		//택스처 적용시 
		CLineMgr::Get_Instance()->Render(hBackDC);
		CObjMgr::Get_Instance()->Render(hBackDC);

		BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
		
	} */

	// 신 매니저 사용 후 

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC hBackDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Back");
	//HDC hGroundDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Ground");

	int iScroll_X = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScroll_Y = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	CSceneMgr::Get_Instance()->Render(hBackDC);

	//BitBlt(hBackDC, iScroll_X, iScroll_Y, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);
	// 2880  800
	BitBlt(m_DC, 0, 0, 2880, 800, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBitmapMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Distroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}