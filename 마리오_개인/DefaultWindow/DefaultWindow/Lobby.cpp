#include "stdafx.h"
#include "Lobby.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Cursor.h"
#include "UIButton.h"
#include "CollisionMgr.h"

CLobby::CLobby()
{
}


CLobby::~CLobby()
{
	Release();
}

void CLobby::Initialize(void)
{
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER)->push_back(
		CAbstractFactory::Create<CCursor>()
	);

	CObj* pBtn = CAbstractFactory::Create<CUIButton>(200.f, 350.f);
	dynamic_cast<CUIButton*>(pBtn)->SetButtonID(CUIButton::BUTTON_ID_START);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_UI)->push_back(pBtn);

	CObj* pBtn1 = CAbstractFactory::Create<CUIButton>(400.f, 350.f);
	dynamic_cast<CUIButton*>(pBtn1)->SetButtonID(CUIButton::BUTTON_ID_EDIT);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_UI)->push_back(pBtn1);

	CObj* pBtn2 = CAbstractFactory::Create<CUIButton>(600.f, 350.f);
	dynamic_cast<CUIButton*>(pBtn2)->SetButtonID(CUIButton::BUTTON_ID_EXIT);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_UI)->push_back(pBtn2);
}

void CLobby::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CLobby::LateUpdate(void)
{
	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER), 
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_UI)
	);
}

void CLobby::Render(HDC hDC)
{
	HDC Back = CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BACK)->Get_BmpDC();
	HDC BG = CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_LOBBYBG)->Get_BmpDC();
	BitBlt(Back, 0, 0, WINCX, WINCY, BG, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(Back);

	BitBlt(hDC, 0, 0, WINCX, WINCY, Back, 0, 0, SRCCOPY);
}

void CLobby::Release(void)
{
	CObjMgr::Get_Instance()->Delete_Group(OBJ_TYPE_PLAYER);
	CObjMgr::Get_Instance()->Delete_Group(OBJ_TYPE_UI);
}
