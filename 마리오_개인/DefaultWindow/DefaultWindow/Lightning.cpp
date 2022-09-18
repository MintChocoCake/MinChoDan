#include "stdafx.h"
#include "Lightning.h"
#include "BmpMgr.h"

CLightning::CLightning()
{
}


CLightning::~CLightning()
{
}

void CLightning::Initialize(void)
{
	CBullet::Initialize();

	m_tInfo.fCX = 180.f;
	m_tInfo.fCY = 845.f;

	m_eType = OBJ_TYPE_BULLET_MONSTER;

	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BOSS_RIGHT_HEAD_EFFECT_01)->Get_BmpDC());

	Change_State(0);
}

int CLightning::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bStart) {
		m_bStart = true;
	}

	if (m_tFrame.dwStart == m_tFrame.dwEnd)
		Set_Dead();

	return OBJ_NOEVENT;
}

FRAME CLightning::SetFrame(int _iState)
{
	return FRAME{ 0, 9, 0, 100 };
}