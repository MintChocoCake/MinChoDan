#include "stdafx.h"
#include "BottomBody.h"
#include "ObjMgr.h"

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
	m_Delay = 600.f;

    Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CBottomBody::Update(void)
{
	if (m_dwHP <= 0)
		Change_State(BOSS_STATE_DIE);

	if (m_iCurState != BOSS_STATE_DIE)
	{
		if (m_Delay >= 0.f)
			--m_Delay;
		else
		{
			Change_State(rand() % 2 + 1);
			m_Delay = 600.f;
		}
		if (m_iCurState == BOSS_STATE_ATTACK_01)
			Set_Bmp(590.f, 257.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_01);
		else if (m_iCurState == BOSS_STATE_ATTACK_02)
			Set_Bmp(590.f, 257.f, BOSS_STATE_ATTACK_02, BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_02);
		else
			Set_Bmp(514.f, 192.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_BOTTOM_BODY);
	}
	else
	{
		Set_Bmp(514.f, 192.f, BOSS_STATE_DIE, BMP_KEY_BOSS_BOTTOM_BODY_DIE);
	}

	Attack();
	SetIdle();

    Update_Rect();
    return 0;
}

void CBottomBody::LateUpdate(void)
{
    Update_Active();

	if (m_iCurState != BOSS_STATE_DIE || m_tFrame.dwStart != m_tFrame.dwEnd)
		Update_Frame();
}

void CBottomBody::Release(void)
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
	case CBottomBody::BOSS_STATE_DIE:
		Set_Pos(m_BasePos.x, m_BasePos.y - 2.f);
		return { 0, 11, BOSS_STATE_DIE, 100 };
		break;
	}
}

void CBottomBody::Attack()
{
	// ¿À¸¥ÂÊ
	if (m_iCurState == BOSS_STATE_ATTACK_01 && m_tFrame.dwStart == 12)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >= m_tInfo.fX)
		{
			CObjMgr::Get_Instance()->Get_Player()->Sub_HP(m_dwDamage);
		}
	}
	// ¿ÞÂÊ
	else if (m_iCurState == BOSS_STATE_ATTACK_02 && m_tFrame.dwStart == 12)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX <= m_tInfo.fX)
		{
			CObjMgr::Get_Instance()->Get_Player()->Sub_HP(m_dwDamage);
		}
	}
}
