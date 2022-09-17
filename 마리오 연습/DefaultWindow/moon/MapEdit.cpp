#include "stdafx.h"
#include "MapEdit.h"
#include "ObjMgr.h"
#include "MapMgr.h"
#include "BmpMgr.h"

CMapEdit::CMapEdit()
{
}


CMapEdit::~CMapEdit()
{
	Release();
}

void CMapEdit::Initialize(void)
{
	CMapMgr::Get_Instance()->SetActive(true);
	CMapMgr::Get_Instance()->Load_Map();
}

void CMapEdit::Update(void)
{
	CMapMgr::Get_Instance()->Update();
}

void CMapEdit::LateUpdate(void)
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMapEdit::Render(HDC hDC)
{
	HDC hBack = CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BACK)->Get_BmpDC();
	HDC hGround = CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_GROUND)->Get_BmpDC();

	BitBlt(hBack, 0, 0, WINCX, WINCY, hGround, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hBack);
	CMapMgr::Get_Instance()->Render(hBack);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

void CMapEdit::Release(void)
{
	CObjMgr::Get_Instance()->Release();
	CMapMgr::Get_Instance()->SetActive(false);
}