#include "stdafx.h"
#include "Wing.h"

CWing::CWing()
{
	m_eMobID = MONSTER_ID_BOSS_WING;
}

CWing::~CWing()
{
}

void CWing::Initialize(void)
{
	CMonster::Initialize();

	Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CWing::Update(void)
{
	if (m_dwHP <= 0)
		Change_State(BOSS_STATE_DIE);

	if (m_iCurState != BOSS_STATE_DIE)
	{
		Change_State(BOSS_STATE_IDLE);
	}
	else
	{
		Set_Bmp(574.f, 297.f, BOSS_STATE_DIE, BMP_KEY_BOSS_WING_DIE);
	}

	Update_Rect();
	return 0;
}

void CWing::LateUpdate(void)
{
	Update_Active();
	if (m_iCurState != BOSS_STATE_DIE || m_tFrame.dwStart != m_tFrame.dwEnd)
		Update_Frame();
}

void CWing::Release(void)
{
}

FRAME CWing::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CWing::BOSS_STATE_IDLE:
	default:
		return { 0, 4, BOSS_STATE_IDLE, 100 };
		break;
	case CWing::BOSS_STATE_ATTACK_01:
		return{ 0, 3, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CWing::BOSS_STATE_DIE:
		return { 0, 12, BOSS_STATE_DIE, 100 };
		break;
	}
}