#pragma once
#include "Monster.h"
class CMococo :
	public CMonster
{
public:
	CMococo();
	virtual ~CMococo();

public:
	virtual void Initialize(void) override;

protected:
	virtual void Act() override;

private:
	DWORD m_dwShotTimer;
};

