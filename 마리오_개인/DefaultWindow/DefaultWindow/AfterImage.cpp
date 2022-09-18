#include "stdafx.h"
#include "AfterImage.h"
#include "BmpMgr.h"

CAfterImage::CAfterImage()
{
	m_bActive = true;
}

CAfterImage::~CAfterImage()
{

}

void CAfterImage::Initialize(void)
{
	m_tInfo.fCX = 53.f;
	m_tInfo.fCY = 70.f;

	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_LEFT)->Get_BmpDC());

	Update_Rect();
	
}

int CAfterImage::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	return 0;
}

void CAfterImage::LateUpdate(void)
{

}

void CAfterImage::Release(void)
{

}

void CAfterImage::OnCollision(CObj* _pTarget)
{
}

void CAfterImage::OnCollisionEnter(CObj* _pTarget)
{
}

void CAfterImage::Set_Alpha(int _Alpha)
{
	if (Dir == DIRECTION_LEFT)
	{
		if (_Alpha == 0)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_LEFT)->Get_BmpDC());
		else if (_Alpha == 1)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_LEFT_01)->Get_BmpDC());
		else if (_Alpha == 2)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_LEFT_02)->Get_BmpDC());
		else if (_Alpha == 3)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_LEFT_03)->Get_BmpDC());
		else
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_LEFT_03)->Get_BmpDC());
	}
	else if (Dir == DIRECTION_RIGHT)
	{
		if (_Alpha == 0)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_RIGHT)->Get_BmpDC());
		else if (_Alpha == 1)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_RIGHT_01)->Get_BmpDC());
		else if (_Alpha == 2)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_RIGHT_02)->Get_BmpDC());
		else if (_Alpha == 2)
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_RIGHT_03)->Get_BmpDC());
		else
			m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_RIGHT_03)->Get_BmpDC());
	}
}
