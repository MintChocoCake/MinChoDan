#pragma once
#include "Boss.h"

class CRightBody : public CBoss
{
public:
	CRightBody();
	virtual ~CRightBody();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual FRAME SetFrame(int _iState);
};

