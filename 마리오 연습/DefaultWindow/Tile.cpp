#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_tInfo.fCX = TILE_CX;
	m_tInfo.fCY = TILE_CY;

	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Edit/tailGold.bmp", L"Tile");
}

int CTile::Update(void)
{
	Update_Rect();

	return OBJ_NO_EVENT;
}

void CTile::Late_Update(void)
{
}

void CTile::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Tile");

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	BitBlt(hDC,
		(int)m_tRect.left + iScrollX,
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_iDrawID * (int)m_tInfo.fCX,
		0,
		SRCCOPY);
}

void CTile::Release(void)
{
}
