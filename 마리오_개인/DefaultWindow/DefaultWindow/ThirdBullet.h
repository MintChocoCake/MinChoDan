#pragma once
#include "Bullet.h"
class CThirdBullet :
	public CBullet
{
public:
	CThirdBullet();
	virtual ~CThirdBullet();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override {};
	virtual FRAME SetFrame(int _iState);

private:
	bool m_bStart;
};

