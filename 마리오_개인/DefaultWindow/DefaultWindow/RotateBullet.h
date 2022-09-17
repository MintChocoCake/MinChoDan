#pragma once
#include "Bullet.h"
class CRotateBullet :
	public CBullet
{
public:
	CRotateBullet();
	virtual ~CRotateBullet();

public:
	void SetRotateInfo(MYPOINT& _tCenter, float _fDistance);

public:
	virtual int  Update(void) override;
	//virtual void LateUpdate(void) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

private:
	MYPOINT m_tCenter;
	float m_fDistance;
	float m_fAngle;
};

