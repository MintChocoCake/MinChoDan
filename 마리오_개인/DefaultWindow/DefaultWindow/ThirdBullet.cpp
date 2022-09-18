#include "stdafx.h"
#include "ThirdBullet.h"
#include "BmpMgr.h"

CThirdBullet::CThirdBullet()
{
}


CThirdBullet::~CThirdBullet()
{
}

void CThirdBullet::Initialize(void)
{
	CBullet::Initialize();

	m_tInfo.fCX = 608.f;
	m_tInfo.fCY = 146.f;

	m_eType = OBJ_TYPE_BULLET_MONSTER;

	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BULLET_THIRD_RIGHT)->Get_BmpDC());

	Change_State(0);
}

int CThirdBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bStart) {
		m_bStart = true;

		if (0 > m_fXDir)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BULLET_THIRD_LEFT)->Get_BmpDC());
	}
	m_tInfo.fX += m_fXDir * m_fSpeed;

	if (m_tFrame.dwStart == m_tFrame.dwEnd)
		Set_Dead();

	return OBJ_NOEVENT;
}

FRAME CThirdBullet::SetFrame(int _iState)
{
	return FRAME{ 0, 9, 0, 50 };
}
