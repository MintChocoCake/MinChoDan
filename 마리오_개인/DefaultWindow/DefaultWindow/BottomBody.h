#pragma once
#include "Boss.h"

class CBottomBody : public CBoss
{
public:
	CBottomBody();
	virtual ~CBottomBody();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;
	virtual FRAME SetFrame(int _iState);
};

