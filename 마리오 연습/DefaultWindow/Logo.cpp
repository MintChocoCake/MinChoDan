#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Logo/878295734368210975.bmp", L"Logo");
}

int CLogo::Update(void)
{
	//CSceneMgr::Get_Instance()->Update();
	return 0;
}

void CLogo::Late_Update(void)
{
	// ����
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		// enum �� Ŭ������ �����ѵ� ����
		CSceneMgr::Get_Instance()->Scen_Change(CSceneMgr::SC_MENU);
		return;
	}
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Logo");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

}

void CLogo::Release(void)
{
}
