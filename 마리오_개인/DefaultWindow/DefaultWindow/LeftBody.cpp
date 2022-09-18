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

    Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CLeftBody::Update(void)
{
    Update_Rect();
    return 0;
}

void CLeftBody::LateUpdate(void)
{
    Update_Active();
    Update_Frame();
}

void CLeftBody::Release(void)
{
}

void CLeftBody::OnCollision(CObj* _pTarget)
{
}

void CLeftBody::OnCollisionEnter(CObj* _pTarget)
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
	case CLeftBody::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}