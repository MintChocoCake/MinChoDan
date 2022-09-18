#pragma once
#include "Monster.h"
class CBombMob :
	public CMonster
{
public:
	CBombMob();
	virtual ~CBombMob();

public:
	virtual void Initialize(void) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

protected:
	virtual void Act() override;

private:
	float m_fAirTime;
};

