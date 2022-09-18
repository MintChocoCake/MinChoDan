#pragma once
#include "Monster.h"
class CFireMob :
	public CMonster
{
public:
	CFireMob();
	virtual ~CFireMob();

public:
	virtual void Initialize(void) override;
	virtual void OnCollision(CObj* _pTarget) override {};
	virtual void OnCollisionEnter(CObj* _pTarget) override;

protected:
	virtual void Act() override;
};

