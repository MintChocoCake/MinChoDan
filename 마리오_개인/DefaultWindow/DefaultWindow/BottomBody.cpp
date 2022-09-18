#include "stdafx.h"
#include "BottomBody.h"

CBottomBody::CBottomBody()
{
    m_eMobID = MONSTER_ID_BOSS_BODY_BOTTOM;
}

CBottomBody::~CBottomBody()
{
}

void CBottomBody::Initialize(void)
{
    CMonster::Initialize();

    Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CBottomBody::Update(void)
{
    Update_Rect();
    return 0;
}

void CBottomBody::LateUpdate(void)
{
    Update_Active();
    Update_Frame();
}

void CBottomBody::Release(void)
{
}

void CBottomBody::OnCollision(CObj* _pTarget)
{
}

void CBottomBody::OnCollisionEnter(CObj* _pTarget)
{
}
FRAME CBottomBody::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CBottomBody::BOSS_STATE_IDLE:
	default:
		return { 0, 2, BOSS_STATE_IDLE, 100 };
		break;
	case CBottomBody::BOSS_STATE_ATTACK:
		return{ 0, 3, BOSS_STATE_ATTACK, 100 };
		break;
	case CBottomBody::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}