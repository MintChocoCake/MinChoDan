#pragma once
#include "Boss.h"

class CWing : public CBoss
{
public:
	CWing();
	virtual ~CWing();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual FRAME SetFrame(int _iState);
};

