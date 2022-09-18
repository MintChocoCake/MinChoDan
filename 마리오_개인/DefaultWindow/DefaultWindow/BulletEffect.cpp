#include "stdafx.h"
#include "BulletEffect.h"
#include "BmpMgr.h"

CBulletEffect::CBulletEffect()
{
	m_bActive = true;
}


CBulletEffect::~CBulletEffect()
{
}

void CBulletEffect::Set_Dir(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIRECTION_LEFT:
		m_hBmpDC = &CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BULLET_EFFECT_LEFT)->Get_BmpDC();
		break;
	case DIRECTION_RIGHT:
		m_hBmpDC = &CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BULLET_EFFECT_RIGHT)->Get_BmpDC();
		break;
	}
}

void CBulletEffect::Initialize(void)
{
	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 259.f;

	m_eType = OBJ_TYPE_EFFECT;

	Change_State(0);

	Update_Rect();
}

void CBulletEffect::LateUpdate(void)
{
	Update_Frame();

	if (m_tFrame.dwStart == m_tFrame.dwEnd)
		Set_Dead();
}

FRAME CBulletEffect::SetFrame(int _iState)
{
	return FRAME{ 0, 5, 0, 50 };
}

int CBulletEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}
