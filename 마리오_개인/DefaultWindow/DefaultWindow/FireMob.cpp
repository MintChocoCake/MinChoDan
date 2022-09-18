#include "stdafx.h"
#include "FireMob.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"

CFireMob::CFireMob()
{
	m_eMobID = MONSTER_ID_FIRE;
}


CFireMob::~CFireMob()
{
}

void CFireMob::Initialize(void)
{
	CMonster::Initialize();
}

void CFireMob::OnCollisionEnter(CObj * _pTarget)
{
	CObj* pObj;
	INFO* pInfo;
	DWORD dwDamage;
	switch (_pTarget->Get_Type())
	{
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

void CFireMob::Act()
{
	INFO& tPlrInfo = CObjMgr::Get_Instance()->Get_Player()->Get_Info();

	float fBase = tPlrInfo.fX - m_tInfo.fX;
	float fHeight = tPlrInfo.fY - m_tInfo.fY;

	float fDia = sqrtf(pow(fBase, 2) + pow(fHeight, 2));

	float fRadian = acosf(fBase / fDia);
	if (tPlrInfo.fY > m_tInfo.fY)
		fRadian = 2 * PI - fRadian;

	m_tInfo.fX += m_fSpeed * cosf(fRadian);
	m_tInfo.fY -= m_fSpeed * sinf(fRadian);
}
