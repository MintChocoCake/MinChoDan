#include "stdafx.h"
#include "CTunnel.h"
#include "CScrollMgr.h"
#include "CBitmapMgr.h"
#include "CMonster.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CTunnel::CTunnel()
{
}

CTunnel::CTunnel(INFO _tInfo)
{
    memcpy(&m_tInfo, &_tInfo, sizeof(INFO));
    CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Stage/Tunnel.bmp", L"Box_Tunnel");
    CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Stage/Tunnel_Out.bmp", L"Box_Tunnel_Out");
}

CTunnel::~CTunnel()
{
    Release();
}

void CTunnel::Initialize(void)
{
    POINT Scroll = CScrollMgr::GetInstance()->GetScroll();

    m_tInfo.fX = m_tBoxInfo.fX;
    m_tInfo.fY = m_tBoxInfo.fY;
    m_tInfo.fCX = m_tBoxInfo.fCX;
    m_tInfo.fCY = m_tBoxInfo.fCY;
    m_tBoxInfo.eType;
}

int CTunnel::Update(void)
{
    Update_Rect();
    return OBJ_NOEVENT;
}

void CTunnel::LateUpdate(void)
{
}

void CTunnel::Render(HDC hDC)
{
    POINT Scroll = CScrollMgr::GetInstance()->GetScroll();
    //Rectangle(hDC, m_tRect.left + Scroll.x, m_tRect.top + Scroll.y, m_tRect.right + Scroll.x, m_tRect.bottom + Scroll.y);

    if (m_tBoxInfo.eType == BOX_IN_TUNNEL)
    {
        HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Tunnel");
        GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
    }
    else if(m_tBoxInfo.eType == BOX_OUT_TUNNEL)
    {
        HDC	hBoxDC = CBitmapMgr::GetInstance()->Find_bmp(L"Box_Tunnel_Out");
        GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hBoxDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
    }
}

void CTunnel::Release(void)
{
}

