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

private:
	bool m_bReveal;

};

