#include "stdafx.h"
#include "SecondBullet.h"
#include "BmpMgr.h"

CSecondBullet::CSecondBullet() : m_bStart(false)
{
}


CSecondBullet::~CSecondBullet()
{
}

void CSecondBullet::Initialize(void)
{
	CBullet::Initialize();

	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 42.f;

	m_eType = OBJ_TYPE_BULLET_MONSTER;

	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BULLET_SECOND_RIGHT)->Get_BmpDC());

	Change_State(0);
}

int CSecondBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bStart) {
		m_bStart = true;

		if(0 > m_fXDir)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BULLET_SECOND_LEFT)->Get_BmpDC());
	}
	m_tInfo.fX += m_fXDir * m_fSpeed;

	return OBJ_NOEVENT;
}

FRAME CSecondBullet::SetFrame(int _iState)
{
	return FRAME{0, 3, 0, 100};
}
