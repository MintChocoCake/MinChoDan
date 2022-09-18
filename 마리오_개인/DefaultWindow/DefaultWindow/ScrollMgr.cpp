#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (-10 < m_fScrollX)
		m_fScrollX = -10;

	if (-10 < m_fScrollY)
		m_fScrollY = -10;
	// TILEC * TILEX + 30

	if (WINCX - TILEC * TILEX > m_fScrollX)
		m_fScrollX = WINCX - TILEC * TILEX;

	if (WINCY - TILEC * TILEY > m_fScrollY)
		m_fScrollY = WINCY - TILEC * TILEY;
}

void CScrollMgr::Initialize()
{
	m_fScrollX = 0.f;
	m_fScrollY = 0.f;
}
