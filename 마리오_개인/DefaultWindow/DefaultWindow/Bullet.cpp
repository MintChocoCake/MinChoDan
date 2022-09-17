#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "Block.h"
#include "ScrollMgr.h"

CBullet::CBullet() : m_fAirTime(0.f)
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 8.f;

	m_dwHP = 1;
	m_eType = OBJ_TYPE_BULLET_MONSTER;

	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BULLET)->Get_BmpDC());
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fXDir * m_fSpeed;
	m_tInfo.fY -= 10.f * sinf(90) * m_fAirTime - (9.8f * pow(m_fAirTime, 2)) * 0.5f;

	m_fAirTime += 0.1f;

	return OBJ_NOEVENT;
}

void CBullet::LateUpdate(void)
{
 	Update_Rect();
	Update_Active();

	if (!m_bActive)
		Set_Dead();
}

void CBullet::Release(void)
{
}

void CBullet::OnCollision(CObj * _pTarget)
{
}

void CBullet::OnCollisionEnter(CObj * _pTarget)
{
	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_MONSTER:
	case OBJ_TYPE_PLAYER:
		Set_Dead();
		break;
	case OBJ_TYPE_BLOCK:
		switch (dynamic_cast<CBlock*>(_pTarget)->Get_BlockID()) {
		case BLOCK_ID_TILE:
			m_fAirTime = 0.f;
			break;
		default:
			Set_Dead();
			break;
		}
		break;
	default:
		break;
	}

}
