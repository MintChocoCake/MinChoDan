#include "stdafx.h"
#include "RotateFire.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "RotateBullet.h"

CRotateFire::CRotateFire() : m_bSpawn(false)
{
}


CRotateFire::~CRotateFire()
{
}

void CRotateFire::LateUpdate(void)
{
	list<CObj*>* pBullets = CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_MONSTER);
	CObj* pTarget;

	if (m_bActive) {
		if (!m_bSpawn) {
			m_bSpawn = true;
			for (int i = 0; i < 4; ++i) {
				pTarget = CAbstractFactory::Create<CRotateBullet>();
				dynamic_cast<CRotateBullet*>(pTarget)->SetRotateInfo(MYPOINT{ m_tInfo.fX, m_tInfo.fY }, 10 + i * 30.f);
				pBullets->push_back(pTarget);
			}
		}
	}

	Update_Active();
}
