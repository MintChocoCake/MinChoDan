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
	// ȭ�� ������ ������ ��ũ�� �� ����
	if (0.f < m_fScroll_X)
		m_fScroll_X = 0.f;
	
	if (0.f < m_fScroll_Y)
		m_fScroll_Y = 0.f;

	// ������ ���� ������ ������ũ�� - ������ ȭ�� ��( ������ �� )

	//if (WINCX - 10000.f > m_fScroll_X)
	//	m_fScroll_X = WINCX - 10000.f;

	if (WINCX - STAGE_SCENE_X > m_fScroll_X)
		m_fScroll_X = WINCX - STAGE_SCENE_X;
	// ���� ���� ������ ������ũ�� - ���� ȭ�� ��( ������ �� )
	if (WINCY - STAGE_SCENE_Y2 > m_fScroll_Y)
		m_fScroll_Y = WINCY - STAGE_SCENE_Y2;

	/*
	// ������ ���� ������ ������ũ�� - ������ ȭ�� ��
	if (WINCX - 1920 > m_fScroll_X)
		m_fScroll_X = WINCX - 1920;
	// ���� ���� ������ ������ũ�� - ���� ȭ�� ��
	if (WINCY - 1200 > m_fScroll_Y)
		m_fScroll_Y = WINCY - 1200;
		*/
}
