#pragma once
#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(MYPOINT& _tLeft, MYPOINT& _tRight);
	~CLine();

public:
	LINE& GetInfo() { return m_tInfo; }
	float GetY(float _fX) { return m_fSlope * _fX + m_fYInter; }

public:
	void SetLeft(MYPOINT& _tLeft) { m_tInfo.tLeft = _tLeft; }
	void SetRight(MYPOINT& _tRight) { m_tInfo.tRight = _tRight; }

public:
	void Initialize();
	void Render(HDC _HDC);

private:
	LINE m_tInfo;
	float m_fSlope;
	float m_fYInter;
};

