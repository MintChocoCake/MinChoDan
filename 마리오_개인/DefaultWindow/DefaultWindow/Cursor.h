#pragma once
#include "Obj.h"
class CCursor :
	public CObj
{
public:
	CCursor();
	virtual ~CCursor();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override {};
	virtual void Release(void) override {};
	virtual void OnCollision(CObj* _pTarget) override {};
	virtual void OnCollisionEnter(CObj* _pTarget) override {};
};

