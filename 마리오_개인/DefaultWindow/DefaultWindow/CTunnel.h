#pragma once
#include "Block.h"

class CTunnel : public CBlock
{
public:
	CTunnel();
	virtual ~CTunnel();

public:
	virtual void Initialize(void) override;
};