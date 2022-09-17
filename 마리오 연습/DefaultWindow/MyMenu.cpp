#include "stdafx.h"
#include "MyMenu.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Menu/TitleScreen.bmp", L"Menu");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Butten/PlayGameButten.bmp", L"Start");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Butten/MapEditorButten.bmp", L"Edit");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Butten/ExitButten.bmp", L"Exit");

	CObj*		pButton = CAbstractFactory<CMyButton>::Create(400.f, 300.f);
	pButton->Set_Frame_Key(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pButton);

	pButton = CAbstractFactory<CMyButton>::Create(400.f, 370.f);
	pButton->Set_Frame_Key(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pButton);

	pButton = CAbstractFactory<CMyButton>::Create(400.f, 440.f);
	pButton->Set_Frame_Key(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pButton);

}

int CMyMenu::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Menu");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
}
