#include "stdafx.h"
#include "Hill.h"
#include "ScrollMgr.h"

CHill::CHill() : m_fSlope(0.f), m_fYInter(0.f)
{
	ZeroMemory(&m_tLineInfo, sizeof(LINE));
}

CHill::~CHill()
{
}

void CHill::Initialize(void)
{
	m_eType = OBJ_TYPE_HILL;
}

int CHill::Update(void)
{
	if (!m_bStart) {
		m_bStart = true;
		m_fSlope = (m_tLineInfo.tLeft.fY - m_tLineInfo.tRight.fY) / (m_tLineInfo.tLeft.fX - m_tLineInfo.tRight.fX);
		m_fYInter = m_tLineInfo.tLeft.fY - m_fSlope * m_tLineInfo.tLeft.fX;

		if (m_tLineInfo.tLeft.fX > m_tLineInfo.tRight.fX) {
			MYPOINT temp = m_tLineInfo.tLeft;
			m_tLineInfo.tLeft = m_tLineInfo.tRight;
			m_tLineInfo.tRight = temp;
		}
	}

	return OBJ_NOEVENT;
}

void CHill::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_X();
	float fScrollY = CScrollMgr::Get_Instance()->Get_Y();

	MoveToEx(hDC, (int)(m_tLineInfo.tLeft.fX + fScrollX), (int)(m_tLineInfo.tLeft.fY + fScrollY), nullptr);
	LineTo(hDC, (int)(m_tLineInfo.tRight.fX + fScrollX), (int)(m_tLineInfo.tRight.fY + fScrollY));
}

void CHill::OnCollision(CObj * _pTarget)
{
}

void CHill::OnCollisionEnter(CObj * _pTarget)
{
}
