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
	// 구조체로 값을 전달하기 위해 ?
	LINE			m_tInfo;

};

