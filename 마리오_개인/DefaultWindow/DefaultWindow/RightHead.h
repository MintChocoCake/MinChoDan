#pragma once
#include "Boss.h"

class CRightHead : public CBoss
{
public:
	CRightHead();
	virtual ~CRightHead();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual FRAME SetFrame(int _iState);
private:
	void Attack();
	bool isCast = false;
};

