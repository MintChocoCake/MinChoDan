#pragma once
#include "LeftHead.h"
class CLeftHeadSkill :
	public CLeftHead
{
public:
	CLeftHeadSkill(float _fX, float _fY);
	virtual ~CLeftHeadSkill();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

private:
	INFO		m_tHitBox;
	RECT		m_tHitBox_Rect;

};

