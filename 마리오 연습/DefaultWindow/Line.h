#pragma once

#include "Define.h"
#include "ScrollMgr.h"


class CLine
{
public:
	CLine();
	CLine(MYPOINT& _tLeft, MYPOINT& _tRight);
	CLine(LINE& _tLine);
	~CLine();

public:
	const	LINE&		Get_Info()const { return m_tInfo; }

public:
	void			Render(HDC _hDC);

private:
	// ����ü�� ���� �����ϱ� ���� ?
	LINE			m_tInfo;

};

