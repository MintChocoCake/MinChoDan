#include "stdafx.h"
#include "Mococo.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"


CMococo::CMococo() : m_dwShotTimer(0)
{
	m_eMobID = MONSTER_ID_MOCOCO;
}


CMococo::~CMococo()
{
}

void CMococo::Initialize(void)
{
	CMonster::Initialize();

	m_dwShotTimer = GetTickCount();
}

void CMococo::Act()
{
	CMonster::Act();
}
