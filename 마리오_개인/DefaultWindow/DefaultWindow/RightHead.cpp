#include "stdafx.h"
#include "RightHead.h"

CRightHead::CRightHead()
{
    m_eMobID = MONSTER_ID_BOSS_HEAD_RIGHT;
}

CRightHead::~CRightHead()
{
}

void CRightHead::Initialize(void)
{
    CMonster::Initialize();

    Change_State(BOSS_STATE_IDLE);
    Update_Rect();
}

int CRightHead::Update(void)
{
    Update_Rect();
    return 0;
}

void CRightHead::LateUpdate(void)
{
    Update_Active();
    Update_Frame();
}

void CRightHead::Release(void)
{
}

void CRightHead::OnCollision(CObj* _pTarget)
{
}

void CRightHead::OnCollisionEnter(CObj* _pTarget)
{
}

FRAME CRightHead::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CBoss::BOSS_STATE_IDLE:
	default:
		return { 0, 8, BOSS_STATE_IDLE, 100 };
		break;
	case CBoss::BOSS_STATE_ATTACK_01:
		return{ 0, 3, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CBoss::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}