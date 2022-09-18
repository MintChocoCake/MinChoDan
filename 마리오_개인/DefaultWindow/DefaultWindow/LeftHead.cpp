#include "stdafx.h"
#include "LeftHead.h"
#include "CollisionMgr.h"

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

	if (m_bCast)
	{
		m_tHitBox.fX = m_tInfo.fX - m_tInfo.fCX / 0.5f;
		m_tHitBox.fY = m_tInfo.fY; -m_tInfo.fCY / 0.5f;
		m_tHitBox.fCX = 50.f;
		m_tHitBox.fCY = 50.f;

		Update_Rect();
	}

}

void CLeftHead::Release(void)
{
}

void CLeftHead::OnCollision(CObj* _pTarget)
{
	m_tHitBox_Rect.top;
	m_tHitBox_Rect.left;
	m_tHitBox_Rect.bottom;
	m_tHitBox_Rect.right;

	

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

