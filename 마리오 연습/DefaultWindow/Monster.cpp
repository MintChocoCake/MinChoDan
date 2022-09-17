#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 2.f;

	m_pFrame_Key = L"GoomBa";

	m_ePreState = STATE_END;
	m_eCurState = LEFTIDLE;

	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Monster/MonsterGoomBa.bmp", L"GoomBa");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Monster/TutleLeft.bmp", L"TutleLeft");


	if (GOOMBA == m_eMos_Type)
	{
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 0;
		m_tFrame.iMotion = 3;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	if (TUTLE == m_eMos_Type)
	{
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 0;
		m_tFrame.iMotion = 4;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
}

int CMonster::Update(void)
{
	m_tInfo.fX -= m_fSpeed;

	float	fY = 0;

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (bLineCol)
	{
		m_tInfo.fY = fY;
	}

	Moster_Move();
	State_Change();
	Move_Frame();

	Update_Rect();

	return 0;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
	
	int	iScroll_X = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int	iScroll_Y = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();



	if (GOOMBA == m_eMos_Type)
	{
		HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(m_pFrame_Key);

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + iScroll_X,
			(int)m_tRect.top + iScroll_Y,  // 왜 플러스지
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 172, 255));
	}

	if (TUTLE == m_eMos_Type)
	{
		HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(m_pFrame_Key);

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + iScroll_X,
			(int)m_tRect.top + iScroll_Y,  // 왜 플러스지
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
		
}

void CMonster::Release(void)
{
}

void CMonster::Moster_Move(void)
{
	if (GOOMBA == m_eMos_Type)
	{
		m_pFrame_Key = L"GoomBa";
		m_eCurState = LEFTWALK;
	}
	if (TUTLE == m_eMos_Type)
	{
		m_pFrame_Key = L"TutleLeft";
		m_eCurState = LEFTWALK;
	}
}

void CMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CMonster::LEFTWALK:
			if (GOOMBA == m_eMos_Type)
			{
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 2;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
			if (TUTLE == m_eMos_Type)
			{
				m_tFrame.iStart = 0;
				m_tFrame.iEnd = 4;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount();
				break;
			}
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}
