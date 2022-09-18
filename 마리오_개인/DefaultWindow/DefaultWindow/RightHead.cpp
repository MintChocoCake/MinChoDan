#include "stdafx.h"
#include "RightHead.h"
#include "AbstractFactory.h"
#include "Lightning.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

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
	m_Delay = 900.f;

    Change_State(BOSS_STATE_IDLE);
    Update_Rect();
}

int CRightHead::Update(void)
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
			m_Delay = 900.f;
		}

		if (m_iCurState == BOSS_STATE_ATTACK_01)
		{
			Set_Bmp(349.f, 353.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_RIGHT_HEAD_ATTACK_01);
			if (!isCast)
				Attack();
		}
		else
		{
			Set_Bmp(261.f, 209.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_RIGHT_HEAD);
			isCast = false;
		}
	}
	else
		Set_Bmp(253.f, 209.f, BOSS_STATE_DIE, BMP_KEY_BOSS_RIGHT_HEAD_DIE);

	SetIdle();
    Update_Rect();
    return 0;
}

void CRightHead::LateUpdate(void)
{
    Update_Active();
	if (m_iCurState != BOSS_STATE_DIE || m_tFrame.dwStart != m_tFrame.dwEnd)
		Update_Frame();
}

void CRightHead::Release(void)
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
	case CBoss::BOSS_STATE_DIE:
		Set_Pos(m_BasePos.x, m_BasePos.y);
		return { 0, 12, BOSS_STATE_DIE, 100 };
		break;
	}
}

void CRightHead::Attack()
{
	isCast = true;
	for (int i = 0; i < 10; ++i)
	{
		int RandX = rand() % WINCX - CScrollMgr::Get_Instance()->Get_X();
		CObj* pObj = CAbstractFactory::Create<CLightning>(RandX, m_tInfo.fY);
		pObj->Set_Type(OBJ_TYPE_BULLET_MONSTER);

		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_MONSTER)->push_back(pObj);
	}
}
