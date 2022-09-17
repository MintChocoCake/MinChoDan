#include "stdafx.h"
#include "Gunner.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "ObjMgr.h"

CGunner::CGunner() : m_dwShotTimer(0), m_pBullets(nullptr)
{
	m_eMobID = MONSTER_ID_GUNNER;
}


CGunner::~CGunner()
{
}

void CGunner::Initialize(void)
{
	CMonster::Initialize();

	m_dwShotTimer = GetTickCount();
	m_pBullets = CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_MONSTER);
}

void CGunner::Act()
{
	CMonster::Act();

	CObj* pObj;
	if (m_dwShotTimer + 1000 < GetTickCount()) {
		pObj = CAbstractFactory::Create<CBullet>(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CBullet*>(pObj)->SetXDir(-1.f);
		m_pBullets->push_back(pObj);
		m_dwShotTimer = GetTickCount();
	}
}
