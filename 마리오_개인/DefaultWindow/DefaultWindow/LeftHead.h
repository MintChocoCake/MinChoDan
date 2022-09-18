#pragma once
#include "Boss.h"

class CLeftHead : public CBoss
{
public:
	CLeftHead();
	virtual ~CLeftHead();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;
	virtual FRAME SetFrame(int _iState);

public:

	//void		HitBox_Rect(void);


private:
	INFO		m_tHitBox;
	RECT		m_tHitBox_Rect;

};