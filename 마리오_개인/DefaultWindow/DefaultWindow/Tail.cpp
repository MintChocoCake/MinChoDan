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
	Update_Rect();
	return 0;
}

void CTail::LateUpdate(void)
{
	Update_Active();
	Update_Frame();
}

void CTail::Release(void)
{
}

void CTail::OnCollision(CObj* _pTarget)
{
}

void CTail::OnCollisionEnter(CObj* _pTarget)
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
	case CTail::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}