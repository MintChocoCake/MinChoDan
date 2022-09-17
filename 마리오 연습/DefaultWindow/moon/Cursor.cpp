#include "stdafx.h"
#include "Cursor.h"
#include "BmpMgr.h"

CCursor::CCursor()
{
	m_bActive = true;
}


CCursor::~CCursor()
{
}

void CCursor::Initialize(void)
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;

	m_eType = OBJ_TYPE_PLAYER;
	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_CURSOR)->Get_BmpDC());
}

int CCursor::Update(void)
{
	POINT pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();

	return 0;
}
