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