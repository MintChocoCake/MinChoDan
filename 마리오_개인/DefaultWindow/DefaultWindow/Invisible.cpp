#include "stdafx.h"
#include "Invisible.h"
#include "BmpMgr.h"

CInvisible::CInvisible() : m_bReveal(false), m_ePivotY(-1.f), m_bMoving(false)
{
}


CInvisible::~CInvisible()
{
}

void CInvisible::Reveal()
{
	if (!m_bReveal) {
		m_bReveal = true;
		m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BLOCK_ITEM_BOX)->Get_BmpDC());
		m_ePivotY = m_tInfo.fY;
	}
	m_bMoving = true;
}

int CInvisible::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bMoving) {
		m_tInfo.fY -= m_fSpeed;

		if (m_ePivotY - 15 > m_tInfo.fY)
			m_fSpeed *= -1.f;
		if (m_tInfo.fY > m_ePivotY) {
			m_tInfo.fY = m_ePivotY;
			m_bMoving = false;
			m_fSpeed *= -1.f;
		}
	}

	return OBJ_NOEVENT;
}

void CInvisible::LateUpdate(void)
{
	Update_Active();
	Update_Rect();
}
