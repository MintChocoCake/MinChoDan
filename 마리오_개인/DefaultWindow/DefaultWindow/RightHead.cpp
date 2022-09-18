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
	m_BasePos.x = m_tInfo.fX;
	m_BasePos.y = m_tInfo.fY;

    Change_State(BOSS_STATE_IDLE);
    Update_Rect();
}

int CRightHead::Update(void)
{
	if(m_iCurState == BOSS_STATE_ATTACK_01)
		Set_Bmp(349.f, 353.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_RIGHT_HEAD_ATTACK_01);
	else
		Set_Bmp(261.f, 209.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_RIGHT_HEAD);

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
		Set_Pos(m_BasePos.x, m_BasePos.y);
		return { 0, 8, BOSS_STATE_IDLE, 100 };
		break;
	case CBoss::BOSS_STATE_ATTACK_01:
		Set_Pos(m_BasePos.x + 40.f, m_BasePos.y + 70.5f);
		return{ 0, 16, BOSS_STATE_ATTACK_01, 100 }; 
		break;
	case CBoss::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}