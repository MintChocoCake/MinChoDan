#include "stdafx.h"
#include "Obj.h"
#include "ScrollMgr.h"

static DWORD dwINSTANCE_NUMBER = 0;

CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_bActive(false), m_iCurState(-1) 
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));

	m_dwInstanceID = dwINSTANCE_NUMBER++;
}

CObj::~CObj()
{
}

bool CObj::Col_Before(DWORD _dwTarget)
{
	auto iter = m_ColSet.find(_dwTarget);

	if(iter == m_ColSet.end())
		return false;

	return true;
}

void CObj::Add_Col(DWORD _dwTarget)
{
	m_ColSet.insert(_dwTarget);
}

void CObj::Delete_Col(DWORD _dwTarget)
{
	auto iter = m_ColSet.find(_dwTarget);

	if (iter == m_ColSet.end())
		return;

	m_ColSet.erase(iter);
}

void CObj::Render(HDC hDC)
{
	if (!m_bActive)	return;

	LONG lScrollX = (LONG)CScrollMgr::Get_Instance()->Get_X();
	LONG lScrollY = (LONG)CScrollMgr::Get_Instance()->Get_Y();

	GdiTransparentBlt(hDC, m_tRect.left + lScrollX, m_tRect.top + lScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, *m_hBmpDC, 
		m_tFrame.dwStart * (int)m_tInfo.fCX, m_tFrame.dwMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));

	//�浹 Ȯ�ο�
	//Rectangle(hDC, m_tRect.left + lScrollX, m_tRect.top + lScrollY, m_tRect.right + lScrollX, m_tRect.bottom + lScrollY);
}

FRAME CObj::SetFrame(int _iState)
{
	return FRAME{ 0, 0, 0, 1000 };
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));

	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Update_Frame(void)
{
	if (m_tFrame.dwTimer + m_tFrame.dwSpeed < GetTickCount()) {
		++m_tFrame.dwStart;

		if (m_tFrame.dwStart > m_tFrame.dwEnd)
			m_tFrame.dwStart = 0;

		m_tFrame.dwTimer = GetTickCount();
	}
}

void CObj::Update_Active(void)
{
	LONG lScrollX = (LONG)CScrollMgr::Get_Instance()->Get_X();
	LONG lScrollY = (LONG)CScrollMgr::Get_Instance()->Get_Y();

	if (-100 <= lScrollX + m_tInfo.fX && lScrollX + m_tInfo.fX <= WINCX + 100)
		m_bActive = true;
	else m_bActive = false;
}

void CObj::Change_State(int _iState)
{
	if (m_iCurState == _iState)
		return;

	FRAME tFrame = SetFrame(_iState);

	m_tFrame = tFrame;
	m_iCurState = _iState;
	m_tFrame.dwTimer = GetTickCount();
}



