#pragma once
#include "Block.h"
class CRotateFire :
	public CBlock
{
public:
	CRotateFire();
	virtual ~CRotateFire();

public:
	virtual void LateUpdate(void) override;

private:
	bool m_bSpawn;

};

