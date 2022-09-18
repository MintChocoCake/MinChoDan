#pragma once
#include "Obj.h"
#include "Define.h"

class CDoubleJumpEffect :
	public CObj
{
public:
	CDoubleJumpEffect();
	virtual ~CDoubleJumpEffect();

public:
	void Set_Dir(DIRECTION _eDir);

public:
	virtual void Initialize(void) override;
	virtual void LateUpdate(void) override;
	virtual FRAME SetFrame(int _iState);

	virtual int  Update(void);
	virtual void Release(void) {};
	virtual void OnCollision(CObj* _pTarget) {};
	virtual void OnCollisionEnter(CObj* _pTarget) {};
};

