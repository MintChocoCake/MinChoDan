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

	CreateChild();
	Change_State(BOSS_STATE_IDLE);
	Update_Rect();
}

int CBoss::Update(void)
{
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

void CBoss::Set_State(float _fCX, float _fCY, BMP_KEY _eBmp)
{
	// m_eMobID = _eID;
	// const BLOCK& tData = arrBlockTable[m_eBlockID];

	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(_eBmp)->Get_BmpDC());

	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;

	Update_Rect();
}
void CBoss::CreateChild()
{
	CObj* _Obj = CAbstractFactory::Create<CLeftBody>();
	_Obj->Set_Pos(m_tInfo.fX - 105.f, m_tInfo.fY + 209.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CRightBody>();
	_Obj->Set_Pos(m_tInfo.fX + 105.f, m_tInfo.fY + 209.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CBottomBody>();
	_Obj->Set_Pos(m_tInfo.fX, m_tInfo.fY + 373.4f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CLeftHead>();
	_Obj->Set_Pos(m_tInfo.fX - 120.f, m_tInfo.fY + 62.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);

	_Obj = CAbstractFactory::Create<CRightHead>();
	_Obj->Set_Pos(m_tInfo.fX + 120.f, m_tInfo.fY + 62.f);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(_Obj);
}
FRAME CBoss::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CBoss::BOSS_STATE_IDLE:
	default:
		return { 0, 8, BOSS_STATE_IDLE, 100 };
		break;
	case CBoss::BOSS_STATE_ATTACK:
		return{ 0, 3, BOSS_STATE_ATTACK, 100 };
		break;
	case CBoss::BOSS_STATE_SKILL:
		return { 0, 0, BOSS_STATE_SKILL, 100000 };
		break;
	}
}
