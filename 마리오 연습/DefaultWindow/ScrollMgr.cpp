#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*		CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScroll_X(0.f) , m_fScroll_Y(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	// 화면 밖으로 나가면 스크롤 값 고정
	if (0.f < m_fScroll_X)
		m_fScroll_X = 0.f;
	
	if (0.f < m_fScroll_Y)
		m_fScroll_Y = 0.f;

	// 오른쪽 끝에 닿으면 윈도우크기 - 오른쪽 화면 끝( 배경신의 끝 )

	//if (WINCX - 10000.f > m_fScroll_X)
	//	m_fScroll_X = WINCX - 10000.f;

	if (WINCX - STAGE_SCENE_X > m_fScroll_X)
		m_fScroll_X = WINCX - STAGE_SCENE_X;
	// 왼쪽 끝에 닿으면 윈도우크기 - 왼쪽 화면 끝( 배경신의 끝 )
	if (WINCY - STAGE_SCENE_Y2 > m_fScroll_Y)
		m_fScroll_Y = WINCY - STAGE_SCENE_Y2;

	/*
	// 오른쪽 끝에 닿으면 윈도우크기 - 오른쪽 화면 끝
	if (WINCX - 1920 > m_fScroll_X)
		m_fScroll_X = WINCX - 1920;
	// 왼쪽 끝에 닿으면 윈도우크기 - 왼쪽 화면 끝
	if (WINCY - 1200 > m_fScroll_Y)
		m_fScroll_Y = WINCY - 1200;
		*/
}
