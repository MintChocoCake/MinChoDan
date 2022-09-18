#include "stdafx.h"
#include "MyFont.h"
#include "BmpMgr.h"

CMyFont::CMyFont()
{
	m_bActive = true;
}


CMyFont::~CMyFont()
{
}

void CMyFont::Set_Number(int _iNum)
{
	m_tFrame.dwStart = _iNum;
}

void CMyFont::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 26.f;

	m_fSpeed = 0.5f;
	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_DAMAGE)->Get_BmpDC());
	m_dwTimer = GetTickCount();
}

int CMyFont::Update(void)
{
	if (m_dwTimer + 1000 < GetTickCount())
		return OBJ_DEAD;

	m_tInfo.fY -= m_fSpeed;
	Update_Rect();

	return 0;
}

FRAME CMyFont::SetFrame(int _iState)
{
	return FRAME{ 0, 9, 0, 10000 };
}
