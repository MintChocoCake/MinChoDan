#include "stdafx.h"
#include "CTunnelMonster.h"

CTunnelMonster::CTunnelMonster()
{
	m_eMobID = MONSTER_ID_TUNNEL;
}

CTunnelMonster::~CTunnelMonster()
{
}

void CTunnelMonster::Initialize(void)
{
	CMonster::Initialize();
	m_DestY = m_tInfo.fY - 70.f;
	m_BaseY = m_tInfo.fY;
}

void CTunnelMonster::OnCollision(CObj* _pTarget)
{
}
void CTunnelMonster::Act()
{
	if (isUP)
	{
		if (m_tInfo.fY >= m_DestY)
			m_tInfo.fY -= m_fSpeed;
		else
			isUP = false;
	}
	if (!isUP)
	{
		if (m_tInfo.fY <= m_BaseY)
			m_tInfo.fY += m_fSpeed;
		else
			isUP = true;
	}
}

FRAME CTunnelMonster::SetFrame(int _iState)
{
	return { 0, 0, MONSTER_STATE_WALK, 200 };
}
