#include "stdafx.h"
#include "Item.h"
#include "BmpMgr.h"

CItem::CItem() : m_dwTimer(0)
{
}


CItem::~CItem()
{
}

void CItem::Set_ItemID(ITEM_ID _eID)
{
	m_eItemID = _eID;

	BMP_KEY eKey = arrItemBmpTable[_eID];
	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(eKey)->Get_BmpDC());

	Update_Rect();
	m_dwTimer = GetTickCount();
}

void CItem::Initialize(void)
{
	m_tInfo.fCX = 24.f;
	m_tInfo.fCY = 24.f;

	m_fSpeed = 0.5f;

	m_eType = OBJ_TYPE_ITEM;
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY -= m_fSpeed;

	if (m_dwTimer + 300 < GetTickCount()) {
		m_fSpeed *= -1.f;
		m_dwTimer = GetTickCount();
	}


	return OBJ_NOEVENT;
}

void CItem::LateUpdate(void)
{
	Update_Rect();
	Update_Active();
}

void CItem::Release(void)
{
}

void CItem::OnCollision(CObj * _pTarget)
{
}

void CItem::OnCollisionEnter(CObj * _pTarget)
{
	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_PLAYER:
		Set_Dead();
		break;
	default:
		break;
	}
}
