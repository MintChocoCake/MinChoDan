#include "stdafx.h"
#include "RotateBullet.h"

CRotateBullet::CRotateBullet() : m_fDistance(0.f), m_fAngle(200.f)
{
	ZeroMemory(&m_tCenter, sizeof(MYPOINT));
	m_bActive = true;
}

CRotateBullet::~CRotateBullet()
{
}

void CRotateBullet::SetRotateInfo(MYPOINT & _tCenter, float _fDistance)
{
	m_tCenter = _tCenter; 
	m_fDistance = _fDistance;
	m_tInfo.fX = m_tCenter.fX + m_fDistance * cosf(m_fAngle * PI / 180);
	m_tInfo.fY = m_tCenter.fY + m_fDistance * sinf(m_fAngle * PI / 180);
}

int CRotateBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_tCenter.fX + m_fDistance * cosf(m_fAngle * PI / 180);
	m_tInfo.fY = m_tCenter.fY + m_fDistance * sinf(m_fAngle * PI / 180);

	m_fAngle += m_fSpeed;

	return OBJ_NOEVENT;
}
//
//void CRotateBullet::LateUpdate(void)
//{
//	Update_Rect();
//	Update_Active();
//}

void CRotateBullet::OnCollisionEnter(CObj * _pTarget)
{
}
