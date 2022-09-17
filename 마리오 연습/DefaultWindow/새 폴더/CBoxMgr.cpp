#include "stdafx.h"
#include "CBoxMgr.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
#include "CBox.h"
#include "CAbstractFactory.h"
#include "CTunnel.h"
#include "CItemBlock.h"

CBoxMgr* CBoxMgr::m_pInstance = nullptr;

CBoxMgr::CBoxMgr()
{
}

CBoxMgr::~CBoxMgr()
{
}

void CBoxMgr::Initialize(void)
{
	//for (int i = 0; i < 100; ++i)
	//{
	//	CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CBox>::CreateBox(i * 50.f, 475.f, BOX_NORMAL));
	//}
	//for (int i = 0; i < 100; ++i)
	//{
	//	CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CBox>::CreateBox(i * 50.f, 475.f + 50.F, BOX_DIRT));
	//}
	//for (int i = 0; i < 100; ++i)
	//{
	//	CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CBox>::CreateBox(i * 50.f, 475.f + 100.F, BOX_DIRT));
	//}
	LoadBox();
}

void CBoxMgr::Update(void)
{
	int X = CObjMgr::GetInstance()->GetMousePos().x - (CObjMgr::GetInstance()->GetMousePos().x % 50);
	int Y = CObjMgr::GetInstance()->GetMousePos().y - (CObjMgr::GetInstance()->GetMousePos().y % 50) - 25.f;

	if (CKeyMgr::GetInstance()->KeyDown('P'))
		SaveBox();

	if (CKeyMgr::GetInstance()->KeyDown('C'))
		CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CBox>::CreateBox(X, Y, BOX_NORMAL));

	if (CKeyMgr::GetInstance()->KeyDown('V'))
		CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CItemBlock>::CreateBox(X, Y, BOX_ITEM));
	
	if (CKeyMgr::GetInstance()->KeyDown('B'))
		CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CTunnel>::Create_Tunnel_In_Box(X, Y, BOX_IN_TUNNEL));
	
	if (CKeyMgr::GetInstance()->KeyDown('N'))
		CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CTunnel>::Create_Tunnel_Out_Box(X, Y, BOX_OUT_TUNNEL));
	
	if (CKeyMgr::GetInstance()->KeyDown('M'))
		CObjMgr::GetInstance()->GetGroundList()->push_back(CAbstractFactory<CTunnel>::Create_Tunnel_In_Box(X, Y, BOX_FAKE_TUNNEL));
	
}

void CBoxMgr::LateUpdate(void)
{
}

void CBoxMgr::Render(HDC hDC)
{
	for (auto& iter : BoxList)
		iter->Render(hDC);
}

void CBoxMgr::Release(void)
{
}

void CBoxMgr::SaveBox()
{
	HANDLE SaveFile = CreateFile(L"../Data/Ground.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == SaveFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;
		
	for (auto& iter : *(CObjMgr::GetInstance()->GetGroundList()))
	{
		WriteFile(SaveFile, &(dynamic_cast<CBox*>(iter)->GetBoxInfo()), sizeof(BOX), &dwByte, nullptr);
	}

	// ���� �Ҹ�
	CloseHandle(SaveFile);

	MessageBox(g_hWnd, _T("Save ����"), L"����", MB_OK);
}

void CBoxMgr::LoadBox()
{
	// ���� ����
	HANDLE		hFile = CreateFile(L"../Data/Ground.dat",
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
	BOX		tInfo{};

	while (true)
	{
		// ���� ����
		ReadFile(hFile, &tInfo, sizeof(BOX), &dwByte, nullptr);
		// 1. ������ ����
		// 2. ������ �������� �ּ�
		// 3. ������ �������� ũ�� ����
		// 4. ����ó�� �� ������ �ּ�
		// 5. ��

		if (0 == dwByte)
			break;

		CObjMgr::GetInstance()->AddObj(OBJ_GROUND, new CBox(tInfo));
	}

	// ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load ����"), L"����", MB_OK);
}