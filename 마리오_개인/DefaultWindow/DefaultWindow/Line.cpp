#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
{
}

CLine::CLine(MYPOINT & _tLeft, MYPOINT & _tRight) : m_tInfo({_tLeft, _tRight})
{
}

CLine::~CLine()
{
}

void CLine::Initialize()
{
	m_fSlope = (m_tInfo.tLeft.fY - m_tInfo.tRight.fY) / (m_tInfo.tLeft.fX - m_tInfo.tRight.fX);
	m_fYInter = m_tInfo.tLeft.fY - m_fSlope * m_tInfo.tLeft.fX;

	if (m_tInfo.tLeft.fX > m_tInfo.tRight.fX) {
		MYPOINT temp = m_tInfo.tLeft;
		m_tInfo.tLeft = m_tInfo.tRight;
		m_tInfo.tRight = temp;
	}
}

void CLine::Render(HDC _HDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_X();
	float fScrollY = CScrollMgr::Get_Instance()->Get_Y();

	MoveToEx(_HDC, (int)(m_tInfo.tLeft.fX + fScrollX), (int)(m_tInfo.tLeft.fY + fScrollY), nullptr);
	LineTo(_HDC, (int)(m_tInfo.tRight.fX + fScrollX), (int)(m_tInfo.tRight.fY + fScrollY));
}
