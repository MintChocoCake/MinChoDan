#include "stdafx.h"
#include "Tutle.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"


CTutle::CTutle() : m_dwShotTimer(0)
{
	m_eMobID = MONSTER_ID_TUTLE;
}


CTutle::~CTutle()
{
}

void CTutle::Initialize(void)
{
	CMonster::Initialize();

	m_dwShotTimer = GetTickCount();

}

void CTutle::Act()
{
	CMonster::Act();
}
