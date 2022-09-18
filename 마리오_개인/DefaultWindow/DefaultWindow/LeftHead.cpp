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

    Change_State(BOSS_STATE_IDLE);

    Update_Rect();

	

}

int CLeftHead::Update(void)
{

	// 보스 가 스킬 사용시 스킬을 생성하여 좌표 넘겨주기
	if (m_iCurState == BOSS_STATE_ATTACK_01)
		Set_Bmp(546.f, 645.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_LEFT_HEAD_ATTACK_01);
	else
		Set_Bmp(261.f, 209.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_LEFT_HEAD);
	
	

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
	
	//CObj* pObj;
	INFO* pInfo;

	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_PLAYER:
		pInfo = &_pTarget->Get_Info();

		if (abs(pInfo->fY - m_tInfo.fY) < pInfo->fCY && pInfo->fX - pInfo->fCX * 0.7f <= m_tInfo.fX
			&& pInfo->fX + pInfo->fCX * 0.7f >= m_tInfo.fX) {
			if (Get_Cast() == true)
			{

				_pTarget->Add_HP(Get_Damage() * -5.f);
			}
		}
		break;
		
	default:
		break;
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
	case CBoss::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}

