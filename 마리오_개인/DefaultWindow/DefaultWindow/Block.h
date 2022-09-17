#pragma once
#include "Obj.h"

class CBlock :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	BLOCK_ID Get_BlockID() { return m_eBlockID; }

public:
	void Set_BlockID(BLOCK_ID _eID);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	//virtual void Render(HDC hDC) override;
	virtual void Release(void) override {};
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

public:
	BLOCK_ID m_eBlockID;
};

