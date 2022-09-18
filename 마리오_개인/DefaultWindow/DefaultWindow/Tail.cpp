#include "stdafx.h"
#include "Tail.h"


CTail::CTail()
{
	m_eMobID = MONSTER_ID_BOSS_TAIL;
}

CTail::~CTail()
{
}

void CTail::Initialize(void)
{
	CMonster::Initialize();

	Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CTail::Update(void)
{
	if (m_dwHP <= 0)
		Change_State(BOSS_STATE_DIE);

	if (m_iCurState != BOSS_STATE_DIE)
	{
		Change_State(BOSS_STATE_IDLE);
	}
	else 
	{
		Set_Bmp(406.f, 146.f, BOSS_STATE_DIE, BMP_KEY_BOSS_TAIL_DIE);
	}
	Update_Rect();
	return 0;
}

void CTail::LateUpdate(void)
{
	Update_Active();

	if (m_iCurState != BOSS_STATE_DIE || m_tFrame.dwStart != m_tFrame.dwEnd)
		Update_Frame();
}

void CTail::Release(void)
{
}

FRAME CTail::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CTail::BOSS_STATE_IDLE:
	default:
		return { 0, 3, BOSS_STATE_IDLE, 100 };
		break;
	case CTail::BOSS_STATE_ATTACK_01:
		return{ 0, 3, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CTail::BOSS_STATE_DIE:
		return { 0, 8, BOSS_STATE_DIE, 100 };
		break;
	}
}