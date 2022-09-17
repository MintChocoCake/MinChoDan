#pragma once
#include "Monster.h"
class CGunner :
	public CMonster
{
public:
	CGunner();
	virtual ~CGunner();

public:
	virtual void Initialize(void) override;

protected:
	virtual void Act() override;

private:
	list<CObj*>* m_pBullets;
	DWORD m_dwShotTimer;
};

