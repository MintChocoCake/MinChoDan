#include "stdafx.h"
#include "LeftHeadSkill.h"


CLeftHeadSkill::CLeftHeadSkill(float _fX , float _fY)
{
	m_tHitBox.fX = _fX;
	m_tHitBox.fY = _fY;
}


CLeftHeadSkill::~CLeftHeadSkill()
{
	Release();
}

void CLeftHeadSkill::Initialize(void)
{
	m_tHitBox.fCX = 50.f;
	m_tHitBox.fCY = 50.f;
}

int CLeftHeadSkill::Update(void)
{
	Update_Rect();
	return 0;
}

void CLeftHeadSkill::LateUpdate(void)
{
}

void CLeftHeadSkill::Release(void)
{
}

void CLeftHeadSkill::OnCollision(CObj * _pTarget)
{
}

void CLeftHeadSkill::OnCollisionEnter(CObj * _pTarget)
{

	INFO* pInfo;

	switch(_pTarget->Get_Type())
	{
	case OBJ_TYPE_PLAYER:
		pInfo = &_pTarget->Get_Info();

		// 플레이어와 히트 박스의 거리 < 플레이어의 x 축크기 
		if (abs(pInfo->fY - m_tInfo.fY) < pInfo->fCY &&
			pInfo->fX - pInfo->fCY * 0.7f <= m_tInfo.fX &&
			pInfo->fX + pInfo->fCX * 0.7f >= m_tInfo.fX)
		{

		}
		

	default:
		break;
	}
}
