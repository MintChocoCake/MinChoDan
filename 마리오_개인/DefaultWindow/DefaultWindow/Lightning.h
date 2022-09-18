#pragma once
#include "Bullet.h"

class CLightning : public CBullet
{
public:
	CLightning();
	virtual ~CLightning();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override {};
	virtual FRAME SetFrame(int _iState);

private:
	bool m_bStart;
};

