#include "stdafx.h"
#include "LeftBody.h"

CLeftBody::CLeftBody()
{
    m_eMobID = MONSTER_ID_BOSS_BODY_LEFT;
}

CLeftBody::~CLeftBody()
{
}

void CLeftBody::Initialize(void)
{
    CMonster::Initialize();
	m_BasePos.x = m_tInfo.fX;
	m_BasePos.y = m_tInfo.fY;

    Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CLeftBody::Update(void)
{
	if (m_dwHP <= 0)
		Change_State(BOSS_STATE_DIE);

	if (m_iCurState != BOSS_STATE_DIE)
	{
		Change_State(BOSS_STATE_IDLE);
	}
	else
	{
		Set_Bmp(210.f, 141.f, BOSS_STATE_DIE, BMP_KEY_BOSS_LEFT_BODY_DIE);
	}

    Update_Rect();
    return 0;
}

void CLeftBody::LateUpdate(void)
{
    Update_Active();
	if (m_iCurState != BOSS_STATE_DIE || m_tFrame.dwStart != m_tFrame.dwEnd)
		Update_Frame();
}

void CLeftBody::Release(void)
{
}

FRAME CLeftBody::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CLeftBody::BOSS_STATE_IDLE:
	default:
		return { 0, 4, BOSS_STATE_IDLE, 100 };
		break;
	case CLeftBody::BOSS_STATE_ATTACK_01:
		return{ 0, 3, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CLeftBody::BOSS_STATE_DIE:
		return { 0, 14, BOSS_STATE_DIE, 100 };
		break;
	}
}