#include "stdafx.h"
#include "LeftHead.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "ObjMgr.h"

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
	m_BasePos.x = m_tInfo.fX;
	m_BasePos.y = m_tInfo.fY;
	m_Delay = 1200.f;

    Change_State(BOSS_STATE_IDLE);

    Update_Rect();

	

}

int CLeftHead::Update(void)
{
	if (m_dwHP <= 0)
		Change_State(BOSS_STATE_DIE);

	if (m_iCurState != BOSS_STATE_DIE)
	{
		if (m_Delay >= 0.f)
			--m_Delay;
		else 
		{
			Change_State(1);
			m_Delay = 1200.f;
		}

		if (m_iCurState == BOSS_STATE_ATTACK_01)
			Set_Bmp(546.f, 645.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_LEFT_HEAD_ATTACK_01);
		else
			Set_Bmp(261.f, 209.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_LEFT_HEAD);
	}
	else
	{
		Set_Bmp(253.f, 209.f, BOSS_STATE_DIE, BMP_KEY_BOSS_LEFT_HEAD_DIE);
	}
	
	Attack();
	SetIdle();
    Update_Rect();
    return 0;
}

void CLeftHead::LateUpdate(void)
{
    Update_Active();

	if (m_iCurState != BOSS_STATE_DIE || m_tFrame.dwStart != m_tFrame.dwEnd)
		Update_Frame();

}

void CLeftHead::Release(void)
{
}

void CLeftHead::Attack()
{
	if (m_iCurState == BOSS_STATE_ATTACK_01 && m_tFrame.dwStart == 18)
	{
		if (abs(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY) < CObjMgr::Get_Instance()->Get_Player()->Get_Info().fCY &&
			CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - CObjMgr::Get_Instance()->Get_Player()->Get_Info().fCX * 0.7f <= m_tInfo.fX &&
			CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX + CObjMgr::Get_Instance()->Get_Player()->Get_Info().fCX * 0.7f >= m_tInfo.fX)
		{
			CObjMgr::Get_Instance()->Get_Player()->Sub_HP(m_dwDamage);
		}
	}
}

FRAME CLeftHead::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CBoss::BOSS_STATE_IDLE:
	default:
		Set_Pos(m_BasePos.x, m_BasePos.y);
		return { 0, 8, BOSS_STATE_IDLE, 100 };
		break;
	case CBoss::BOSS_STATE_ATTACK_01: 
		Set_Pos(m_BasePos.x - 119.5f, m_BasePos.y + 172.5f);
		return{ 0, 22, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CBoss::BOSS_STATE_DIE:
		return { 0, 12, BOSS_STATE_DIE, 100 };
		break;
	}
}

