#pragma once
#include "Obj.h"
#include "Define.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();
public:
	virtual void		Initialize(void)  override;
	virtual int		Update(void)	  override;
	virtual void		LateUpdate(void)  override;
	virtual void		Render(HDC hDC)	  override;
	virtual void		Release(void)	  override;
public:
	void SetBasePos(float _fY) {m_BaseY = _fY; }
private:
	void Attack();
private:
	float m_Delay = 360.f;
	bool isAttack = false;
	float m_BaseY = 0.f;
};

