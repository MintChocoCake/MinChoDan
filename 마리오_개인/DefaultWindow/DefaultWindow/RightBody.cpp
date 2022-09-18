#include "stdafx.h"
#include "RightBody.h"

CRightBody::CRightBody()
{
    m_eMobID = MONSTER_ID_BOSS_BODY_RIGHT;
}

CRightBody::~CRightBody()
{
}

void CRightBody::Initialize(void)
{
    CMonster::Initialize();
	m_BasePos.x = m_tInfo.fX;
	m_BasePos.y = m_tInfo.fY;

    Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CRightBody::Update(void)
{
	if (m_dwHP <= 0)
		Change_State(BOSS_STATE_DIE);

	if (m_iCurState != BOSS_STATE_DIE)
	{
		Change_State(BOSS_STATE_IDLE);
		Set_Bmp(215.f, 144.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_RIGHT_BODY);
	}
	else
	{
		Set_Bmp(210.f, 141.f, BOSS_STATE_DIE, BMP_KEY_BOSS_RIGHT_BODY_DIE);
	}

    Update_Rect();
    return 0;
}

void CRightBody::LateUpdate(void)
{
    Update_Active();
	if (m_iCurState != BOSS_STATE_DIE || m_tFrame.dwStart != m_tFrame.dwEnd)
		Update_Frame();
}

void CRightBody::Release(void)
{
}

FRAME CRightBody::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CRightBody::BOSS_STATE_IDLE:
	default:
		return { 0, 4, BOSS_STATE_IDLE, 100 };
		break;
	case CRightBody::BOSS_STATE_ATTACK_01:
		return{ 0, 3, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CRightBody::BOSS_STATE_DIE:
		Set_Pos(m_BasePos.x - 0.4f, m_BasePos.y);
		return { 0, 14, BOSS_STATE_DIE, 100 };
		break;
	}
}