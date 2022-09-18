#pragma once
#include "Obj.h"
class CMyFont :
	public CObj
{
public:
	CMyFont();
	virtual ~CMyFont();

public:
	void Set_Number(int _iNum);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override {};
	virtual void Release(void) override {};
	virtual void OnCollision(CObj* _pTarget) override {};
	virtual void OnCollisionEnter(CObj* _pTarget) override {};
	virtual FRAME SetFrame(int _iState);
	void SetFont(BMP_KEY _eBmp);
private:
	DWORD m_dwTimer;
};

