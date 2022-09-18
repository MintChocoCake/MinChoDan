#pragma once
#include "Monster.h"
class CTutle :
	public CMonster
{
public:
	CTutle();
	virtual ~CTutle();

public:
	virtual void Initialize(void) override;

protected:
	virtual void Act() override;

private:
	DWORD m_dwShotTimer;
};

