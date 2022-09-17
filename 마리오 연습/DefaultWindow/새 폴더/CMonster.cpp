#include "stdafx.h"
#include "CMonster.h"
#include "CScrollMgr.h"
#include "CBitmapMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 500.f;
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;
	m_fSpeed = 1.5f;

	CBitmapMgr::GetInstance()->Insert_bmp(L"../Image/Monster/Monster_00.bmp", L"Monster_00");
}

int CMonster::Update(void)
{
	if (m_Dead)
		return OBJ_DEAD;
	if (m_Delay >= 0)
	{
		--m_Delay;

		if (!isAttack && m_tInfo.fY <= m_BaseY)
		{
			m_tInfo.fY += m_fSpeed;
		}
	}
	if (m_Delay <= 0)
	{
		isAttack = true;
		Attack();
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate(void)
{
}

void CMonster::Render(HDC hDC)
{
	POINT Scroll = CScrollMgr::GetInstance()->GetScroll();
	//Rectangle(hDC, m_tRect.left + Scroll.x, m_tRect.top + Scroll.y, m_tRect.right + Scroll.x, m_tRect.bottom + Scroll.y);

	HDC	hMonsterDC = CBitmapMgr::GetInstance()->Find_bmp(L"Monster_00");
	GdiTransparentBlt(hDC, (int)m_tRect.left + Scroll.x, (int)m_tRect.top - Scroll.y, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMonsterDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));

}

void CMonster::Release(void)
{
}

void CMonster::Attack()
{
	if (isAttack && m_tInfo.fY >= m_BaseY - 200.f)
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else
	{
		isAttack = false;
		m_Delay = 360.f;
	}
}
