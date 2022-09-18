#pragma once
#include "Block.h"
class CInvisible :
	public CBlock
{
public:
	CInvisible();
	virtual ~CInvisible();

public:
	void Reveal();
	virtual void LateUpdate(void) override;

private:
	bool m_bReveal;


};

