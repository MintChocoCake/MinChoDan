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
	Update_Rect();
	return 0;
}

void CWing::LateUpdate(void)
{
	Update_Active();
	Update_Frame();
}

void CWing::Release(void)
{
}

void CWing::OnCollision(CObj* _pTarget)
{
}

void CWing::OnCollisionEnter(CObj* _pTarget)
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
	case CWing::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}