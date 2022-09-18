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
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;

private:
	bool m_bReveal;
	float m_ePivotY;
	bool m_bMoving;
};

