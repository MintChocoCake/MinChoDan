#include "stdafx.h"
#include "CItemBlock.h"
#include "CBitmapMgr.h"
#include "CScrollMgr.h"

CItemBlock::CItemBlock()
{
}

CItemBlock::~CItemBlock()
{
}

void CItemBlock::Initialize(void)
{
	m_tInfo.fX = m_tBoxInfo.fX;
	m_tInfo.fY = m_tBoxInfo.fY;
	m_tInfo.fCX = m_tBoxInfo.fCX;
	m_tInfo.fCY = m_tBoxInfo.fCY;


	UPDest = m_tInfo.fY - 20.f;
	DownDest = m_tInfo.fY;

	CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Block/Item.bmp", L"Box_Item");
}

int CItemBlock::Update(void)
{		
	Update_Rect();
	return 0;
}

void CItemBlock::LateUpdate(void)
{
}

void CItemBlock::Render(HDC hDC)
{
	POINT Scroll = CScrollMgr::GetInstance()->GetScroll();
	HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Item");
	GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
}

void CItemBlock::Release(void)
{
}

void CItemBlock::CollisonEffect()
{
	if (!isDown && m_tInfo.fY >= UPDest)
		m_tInfo.fY -= 2.f;
	else
		isDown = true;

	if (isDown && m_tInfo.fY <= DownDest)
		m_tInfo.fY += 2.f;
	else
		isDown = false;
}

void CItemBlock::DropRandomItem()
{
	// 랜덤 아이템 드랍
}
