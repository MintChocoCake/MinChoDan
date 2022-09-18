#include "stdafx.h"
#include "Block.h"
#include "Define.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"

CBlock::CBlock() : m_eBlockID(BLOCK_ID_TILE), m_ePivotY(-1.f), m_bMoving(false)
{
}

CBlock::~CBlock()
{
}

void CBlock::Set_BlockID(BLOCK_ID _eID)
{
	m_eBlockID = _eID;
	const BLOCK& tData = arrBlockTable[m_eBlockID];

	m_dwHP = tData.dwHP;
	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(tData.eBmp)->Get_BmpDC());

	m_tInfo.fCX = tData.m_fCX;
	m_tInfo.fCY = tData.m_fCY;
	m_ePivotY = m_tInfo.fY;

	Update_Rect();
}

void CBlock::Initialize(void)
{
	m_eType = OBJ_TYPE_BLOCK;
	m_fSpeed = 3.f;
}

int CBlock::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bMoving) {
		m_tInfo.fY -= m_fSpeed;

		if (m_ePivotY - 15 > m_tInfo.fY)
			m_fSpeed *= -1.f;
		if (m_tInfo.fY > m_ePivotY) {
			m_tInfo.fY = m_ePivotY;
			m_bMoving = false;
			m_fSpeed *= -1.f;
		}
	}

	return OBJ_NOEVENT;
}

void CBlock::LateUpdate(void)
{
	Update_Active();	
	Update_Rect();
}

void CBlock::OnCollision(CObj * _pTarget)
{
}

void CBlock::OnCollisionEnter(CObj * _pTarget)
{
	//float fTempX;
	INFO* pInfo;
	CObj* pObj;
	ITEM_ID eDropItem;

	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_PLAYER:
		if (0 > m_dwHP)	return;
		pInfo = &_pTarget->Get_Info();
		//fTempX = (pInfo->fCX + m_tInfo.fCX * 0.5f;

		if (pInfo->fY > m_tInfo.fY + m_tInfo.fCY * 0.5f) {
			if (pInfo->fX > m_tInfo.fX - m_tInfo.fCX * 0.7f &&
				pInfo->fX < m_tInfo.fX + m_tInfo.fCX * 0.7f) {
				--m_dwHP;
				m_bMoving = true;
				eDropItem = arrBlockTable[m_eBlockID].eDropItem;
				if (eDropItem != ITEM_ID_NONE) {
					pObj = CAbstractFactory::Create<CItem>(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY);
					dynamic_cast<CItem*>(pObj)->Set_ItemID(eDropItem);
					CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_ITEM)->push_back(pObj);
				}

				if (0 >= m_dwHP) Set_Dead();
			}				
		}

		break;
	default:
		break;
	}
}
