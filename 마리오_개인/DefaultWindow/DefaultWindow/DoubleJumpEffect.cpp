#include "stdafx.h"
#include "DoubleJumpEffect.h"
#include "BmpMgr.h"

CDoubleJumpEffect::CDoubleJumpEffect()
{
	m_bActive = true;
}


CDoubleJumpEffect::~CDoubleJumpEffect()
{
}

void CDoubleJumpEffect::Set_Dir(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIRECTION_LEFT:
		m_hBmpDC = &CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_DOUBLE_JUMP_LEFT)->Get_BmpDC();
		break;
	case DIRECTION_RIGHT:
		m_hBmpDC = &CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_DOUBLE_JUMP_RIGHT)->Get_BmpDC();
		break;
	}
}

void CDoubleJumpEffect::Initialize(void)
{
	m_tInfo.fCX = 297.f;
	m_tInfo.fCY = 204.f;

	m_eType = OBJ_TYPE_EFFECT;

	Change_State(0);

	Update_Rect();
}

void CDoubleJumpEffect::LateUpdate(void)
{
	Update_Frame();

	if (m_tFrame.dwStart == m_tFrame.dwEnd)
		Set_Dead();
}

FRAME CDoubleJumpEffect::SetFrame(int _iState)
{
	return FRAME{ 0, 7, 0, 100 };
}

int CDoubleJumpEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}
