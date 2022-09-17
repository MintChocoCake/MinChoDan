#pragma once
#include "Obj.h"

class CHill :
	public CObj
{
public:
	CHill();
	virtual ~CHill();

public:
	LINE& Get_LineInfo() { return m_tLineInfo; }
	float Get_Y(float _fX) { return m_fSlope * _fX + m_fYInter; }

public:
	void Set_Left(MYPOINT& _tLeft) { m_tLineInfo.tLeft = _tLeft; }
	void Set_Right(MYPOINT& _tRight) { m_tLineInfo.tRight = _tRight; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override {};
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override {};
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

private:
	LINE m_tLineInfo;
	float m_fSlope;
	float m_fYInter;
	bool m_bStart;
};

