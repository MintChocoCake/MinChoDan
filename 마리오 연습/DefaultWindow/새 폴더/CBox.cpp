#include "stdafx.h"
#include "CBox.h"
#include "CScrollMgr.h"
#include "CBitmapMgr.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CMonster.h"

CBox::CBox()
{
}

CBox::CBox(BOX _tInfo)
{
	memcpy(&m_tBoxInfo, &_tInfo, sizeof(BOX));
	m_tInfo.fX = m_tBoxInfo.fX;
	m_tInfo.fY = m_tBoxInfo.fY;
	m_tInfo.fCX = m_tBoxInfo.fCX;
	m_tInfo.fCY = m_tBoxInfo.fCY;
	Initialize();

	CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Stage/Block.bmp", L"Box_Ground");
	CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Stage/Block.bmp", L"Box_Dirt");
	CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Stage/Tunnel.bmp", L"Box_Tunnel");
	CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Stage/Tunnel_Out.bmp", L"Box_Tunnel_Out");
	CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Block/Item.bmp", L"Box_Item");
}

CBox::~CBox()
{
}

void CBox::Initialize(void)
{
	m_tInfo.fX = m_tBoxInfo.fX;
	m_tInfo.fY = m_tBoxInfo.fY;
	m_tInfo.fCX = m_tBoxInfo.fCX;
	m_tInfo.fCY = m_tBoxInfo.fCY;

	if(m_tBoxInfo.eType == BOX_IN_TUNNEL)
		CObjMgr::GetInstance()->AddObj(OBJ_MONSTER, CAbstractFactory<CMonster>::CreateMonster(m_tInfo.fX - 200.f, m_tInfo.fY - 450.f, m_tInfo.fY + m_tInfo.fCY * 0.5f));
}

int CBox::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBox::LateUpdate(void)
{
}

void CBox::Render(HDC hDC)
{
	POINT Scroll = CScrollMgr::GetInstance()->GetScroll();
	//Rectangle(hDC, m_tRect.left + Scroll.x, m_tRect.top - Scroll.y, m_tRect.right + Scroll.x, m_tRect.bottom - Scroll.y);
	
	if(m_tBoxInfo.eType == BOX_NORMAL)
	{
		HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Ground");
		GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
	}
	else if(m_tBoxInfo.eType == BOX_DIRT)
	{
		HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Dirt");
		GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
	}
	else if (m_tBoxInfo.eType == BOX_IN_TUNNEL)
	{
		HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Tunnel");
		GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
	}
	else if (m_tBoxInfo.eType == BOX_OUT_TUNNEL)
	{
		HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Tunnel_Out");
		GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
	}
	else if (m_tBoxInfo.eType == BOX_ITEM)
	{
		HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Item");
		GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
	}
}

void CBox::Release(void)
{
}
