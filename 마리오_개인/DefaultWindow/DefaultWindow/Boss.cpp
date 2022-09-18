#include "stdafx.h"
#include "Boss.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "LeftHead.h"
#include "AbstractFactory.h"
#include "RightHead.h"
#include "LeftBody.h"
#include "RightBody.h"
#include "BottomBody.h"
#include "Wing.h"
#include "Tail.h"
CBoss::CBoss()
{
	m_eMobID = MONSTER_ID_BOSS;
}

CBoss::~CBoss()
{
	
}

void CBoss::Initialize(void)
{
	CMonster::Initialize();
	Set_Pos(m_tInfo.fX, m_tInfo.fY + 15.f);
	m_BasePos.x = m_tInfo.fX;
	m_BasePos.y = m_tInfo.fY;
	m_Delay = 1500.f;
	CreateChild();
	Change_State(BOSS_STATE_IDLE);

	Update_Rect();
}

int CBoss::Update(void)
{
	if (m_Delay >= 0.f)
		--m_Delay;
	else
	{
		Change_State(1);
		m_Delay = 1500.f;
	}

	if (m_iCurState == BOSS_STATE_ATTACK_01)
		Set_Bmp(552.f, 777.f, BOSS_STATE_ATTACK_01, BMP_KEY_BOSS_CENTER_HEAD_ATTACK_01);
	else
		Set_Bmp(161.f, 332.f, BOSS_STATE_IDLE, BMP_KEY_BOSS_CENTER_HEAD);

	Attack();
	SetIdle();
	Update_Rect();
	return 0;
}

void CBoss::LateUpdate(void)
{
	Update_Frame();
	Update_Active();
}

void CBoss::Release(void)
{
}

void CBoss::OnCollision(CObj* _pTarget)
{
}

void CBoss::OnCollisionEnter(CObj* _pTarget)
{
}

void CBoss::Set_Bmp(float _fCX, float _fCY, int _iState, BMP_KEY _eBmp)
{
	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(_eBmp)->Get_BmpDC());
	Change_State(_iState);
	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;
	m_tFrame.dwMotion = 0;

	Update_Rect();
}
void CBoss::CreateChild()
{
	CObj* _Obj = CAbstractFactory::Create<CWing>(m_BasePos.x + 0.f, m_BasePos.y + 244.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CTail>(m_BasePos.x + 220.f, m_BasePos.y + 373.4f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CBottomBody>(m_BasePos.x + 0.f, m_BasePos.y + 373.4f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CLeftBody>(m_BasePos.x - 105.f, m_BasePos.y + 209.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CRightBody>(m_BasePos.x + 105.f, m_BasePos.y + 209.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CLeftHead>(m_BasePos.x - 120.f, m_BasePos.y + 62.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CRightHead>(m_BasePos.x + 120.f, m_BasePos.y + 62.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);
}

void CBoss::Attack()
{
	if (m_iCurState == BOSS_STATE_ATTACK_01 && m_tFrame.dwStart == 18)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX <= m_tInfo.fX + (m_tInfo.fCX * 0.5f) &&
			CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >= m_tInfo.fX - (m_tInfo.fCX * 0.5f))
		{
			CObjMgr::Get_Instance()->Get_Player()->Sub_HP(m_dwDamage);
		}
	}
}

FRAME CBoss::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CBoss::BOSS_STATE_IDLE:
	default:
		Set_Pos(m_BasePos.x, m_BasePos.y);
		return { 0, 8, BOSS_STATE_IDLE, 100 };
		break;
	case CBoss::BOSS_STATE_ATTACK_01:
		Set_Pos(m_tInfo.fX, m_tInfo.fY + 132.f);
		return{ 0, 25, BOSS_STATE_ATTACK_01, 100 };
		break;
	case CBoss::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		Cast_On();
		break;
	}
}