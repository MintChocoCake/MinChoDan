#include "stdafx.h"
#include "BombMob.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"

CBombMob::CBombMob()
{
	m_eMobID = MONSTER_ID_BOMB;
}

CBombMob::~CBombMob()
{
}

void CBombMob::Initialize(void)
{
	CMonster::Initialize();
}

void CBombMob::OnCollisionEnter(CObj * _pTarget)
{
	CObj* pObj;
	DWORD dwDamage;
	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_BLOCK:
		m_fAirTime = 0.f;

		break;
	case OBJ_TYPE_BULLET_PLAYER:
		dwDamage = CObjMgr::Get_Instance()->Get_Player()->Get_Damage();
		MakeDamageFont(dwDamage);

		m_dwHP -= dwDamage;
		if (0 >= m_dwHP) {
			Set_Dead();

			const MOB& data = arrMobTable[m_eMobID];
			if (data.eDropItem != ITEM_ID_NONE) {
				pObj = CAbstractFactory::Create<CItem>(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY);
				dynamic_cast<CItem*>(pObj)->Set_ItemID(data.eDropItem);
				CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_ITEM)->push_back(pObj);
			}
		}
		break;
	case OBJ_TYPE_PLAYER:
		Set_Dead();
		break;
	}
}

void CBombMob::Act()
{
	m_tInfo.fX -= m_fSpeed;
	m_tInfo.fY -= 15.f * sinf(90) * m_fAirTime - (9.8f * pow(m_fAirTime, 2)) * 0.5f;
	m_fAirTime += 0.1f;
	m_bActive;
}
