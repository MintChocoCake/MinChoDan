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
	m_BasePos.x = m_tInfo.fX;
	m_BasePos.y = m_tInfo.fY;

    Change_State(BOSS_STATE_IDLE);

	Update_Rect();
}

int CBottomBody::Update(void)
{
	if (m_iCurState == BOSS_STATE_ATTACK_01)
		Set_Bmp(590.f, 257.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_01);
	else if(m_iCurState == BOSS_STATE_ATTACK_02)
		Set_Bmp(590.f, 257.f, BOSS_STATE_ATTACK_02, BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_02);
	else
		Set_Bmp(514.f, 192.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_BOTTOM_BODY);

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
		Set_Pos(m_BasePos.x, m_BasePos.y);
		return { 0, 2, BOSS_STATE_IDLE, 100 };
		break;
	case CBottomBody::BOSS_STATE_ATTACK_01:
		Set_Pos(m_BasePos.x + 39.f, m_BasePos.y - 12.f);
		return{ 0, 16, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CBottomBody::BOSS_STATE_ATTACK_02:
		Set_Pos(m_BasePos.x - 38.f, m_BasePos.y - 12.f);
		return{ 0, 16, BOSS_STATE_ATTACK_02, 100 };
		break;
	case CBottomBody::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}