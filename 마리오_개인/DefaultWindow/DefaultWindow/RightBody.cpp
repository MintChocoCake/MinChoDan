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

    Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CRightBody::Update(void)
{
    Update_Rect();
    return 0;
}

void CRightBody::LateUpdate(void)
{
    Update_Active();
    Update_Frame();
}

void CRightBody::Release(void)
{
}

void CRightBody::OnCollision(CObj* _pTarget)
{
}

void CRightBody::OnCollisionEnter(CObj* _pTarget)
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
	case CRightBody::BOSS_STATE_ATTACK:
		return{ 0, 3, BOSS_STATE_ATTACK, 100 };
		break;
	case CRightBody::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}