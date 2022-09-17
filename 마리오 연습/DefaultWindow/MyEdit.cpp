#include "stdafx.h"
#include "MyEdit.h"




CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CTileMgr::Get_Instance()->Initialize();
}

int CMyEdit::Update(void)
{
	CTileMgr::Get_Instance()->Update();

	return 0;
}

void CMyEdit::Late_Update(void)
{
	Key_Check();
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	CTileMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release(void)
{
}

void CMyEdit::Key_Check(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_Scroll_Y(5.f);
	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_Scroll_Y(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 0);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CTileMgr::Get_Instance()->Save_Tile();

}
