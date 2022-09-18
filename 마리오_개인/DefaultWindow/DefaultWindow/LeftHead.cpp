#include "stdafx.h"
#include "LeftHead.h"

CLeftHead::CLeftHead()
{
    m_eMobID = MONSTER_ID_BOSS_HEAD_LEFT;
}

CLeftHead::~CLeftHead()
{
}

void CLeftHead::Initialize(void)
{
    CMonster::Initialize();

    Change_State(BOSS_STATE_IDLE);
	Set_Bmp(546.f, 645.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_LEFT_HEAD_ATTACK_01);
	Set_Pos(m_tInfo.fX - 120.f, m_tInfo.fY + 172.f);
    Update_Rect();
}

int CLeftHead::Update(void)
{
    Update_Rect();
    return 0;
}

void CLeftHead::LateUpdate(void)
{
    Update_Active();
    Update_Frame();
}

void CLeftHead::Release(void)
{
}

void CLeftHead::OnCollision(CObj* _pTarget)
{
}

void CLeftHead::OnCollisionEnter(CObj* _pTarget)
{
}

FRAME CLeftHead::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CBoss::BOSS_STATE_IDLE:
	default:
		return { 0, 8, BOSS_STATE_IDLE, 100 };
		break;
	case CBoss::BOSS_STATE_ATTACK_01:
		return{ 0, 22, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CBoss::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}