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

<<<<<<< Updated upstream
	if (WINCX - TILEC * TILEX > m_fScrollX)
		m_fScrollX = WINCX - TILEC * TILEX;

	if (WINCY - TILEC * TILEY > m_fScrollY)
		m_fScrollY = WINCY - TILEC * TILEY;
=======
	// 800 - 35 * 
	if (WINCX - TILEC * TILEX + 30 > m_fScrollX)
		m_fScrollX = WINCX - TILEC * TILEX + 30;

	if (WINCY - TILEC * TILEY + 30 > m_fScrollY)
		m_fScrollY = WINCY - TILEC * TILEY + 20;
>>>>>>> Stashed changes
}

void CScrollMgr::Initialize()
{
	m_fScrollX = 0.f;
	m_fScrollY = 0.f;
}
