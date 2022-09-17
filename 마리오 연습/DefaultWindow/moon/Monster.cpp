#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Item.h"
#include "ScrollMgr.h"

CMonster::CMonster() : m_fAirTime(0.f), m_eMobID(MONSTER_ID_MUSHROOM), m_eCurState(MONSTER_STATE_NONE)
{

}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 53.f;
	m_tInfo.fCY = 70.f;

	m_fSpeed = 2.f;
	m_eType = OBJ_TYPE_MONSTER;

	const MOB& data = arrMobTable[m_eMobID];
	m_dwHP = data.dwHP;
	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(data.eBmp)->Get_BmpDC());

	ChangeState(MONSTER_STATE_WALK);
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bActive) {
		Act();
	}

	Update_Frame();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate(void)
{
	Update_Rect();
	Update_Active();
	
	if (m_tInfo.fY > WINCY)
		Set_Dead();
}

void CMonster::Release(void)
{
}

void CMonster::OnCollision(CObj * _pTarget)
{
	INFO* pInfo;
	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_BLOCK:
		pInfo = &_pTarget->Get_Info();

		if (abs(pInfo->fY - m_tInfo.fY) < pInfo->fCY) {
			m_fSpeed *= -1.f;
		}

		if (pInfo->fX - pInfo->fCX * 0.7f <= m_tInfo.fX &&
			pInfo->fX + pInfo->fCX * 0.7f >= m_tInfo.fX) {
			if (pInfo->fY > m_tInfo.fY) {
				m_fAirTime = 0.0f;
				m_tInfo.fY = _pTarget->Get_Info().fY - (_pTarget->Get_Info().fCY + m_tInfo.fCY) * 0.5f;
			}
		}
		break;

	/*case OBJ_TYPE_HILL:
		hill = dynamic_cast<CHill*>(_pTarget);
		fTempY = hill->Get_Y(m_tInfo.fX);

		if (0 > m_fCurJumpDir) {
			StopJump();
			m_tInfo.fY = fTempY - m_tInfo.fCY * 0.5f;
		}
		break;*/
	default:
		break;
	}
}

void CMonster::OnCollisionEnter(CObj * _pTarget)
{
	CObj* pObj;
	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_BULLET_PLAYER:
		--m_dwHP;
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
	default:
		break;
	}
}

void CMonster::Act()
{
	m_tInfo.fX -= m_fSpeed;

	m_tInfo.fY += (9.8f * pow(m_fAirTime, 2)) * 0.5f;
	m_fAirTime += 0.1f;
}

void CMonster::ChangeState(MONSTER_STATE _eState)
{
	if (m_eCurState == _eState)
		return;

	FRAME tFrame;
	switch (_eState)
	{
	case MONSTER_STATE_WALK:
		tFrame = { 0, 1, MONSTER_STATE_WALK, 200 };
		break;
	}

	m_tFrame = tFrame;
	m_eCurState = _eState;
	m_tFrame.dwTimer = GetTickCount();
}
