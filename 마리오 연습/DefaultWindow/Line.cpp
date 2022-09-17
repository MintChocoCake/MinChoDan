#include "stdafx.h"
#include "Line.h"


CLine::CLine()
	
{
}

CLine::CLine(MYPOINT& _tLeft, MYPOINT & _tRight)
	: m_tInfo(_tLeft,_tRight) // 왜 why -> LINE 구조체 생성자가 MYPOINT& 매게변수를 2개 받으니깐
{
}

CLine::CLine(LINE & _tLine)
{
	memcpy(&m_tInfo, &_tLine, sizeof(LINE));
	// m_tInfo 에 _tLine 의 정보를 복사하겠다.
}


CLine::~CLine()
{
}

void CLine::Render(HDC _hDC)
{
	// 스크롤 X 값 가져오기
	int iScroll_X = CScrollMgr::Get_Instance()->Get_Scroll_X();
	int	iScroll_Y = CScrollMgr::Get_Instance()->Get_Scroll_Y();
	// 따리 변수 선언하는 이유 : 이렇게 하지 않으면 라인을 그릴 때 마다 함수를 호출해야해서 그만큼 연산량이 증가한다

	// X 좌표뒤에 + 스크롤 X 
	MoveToEx(_hDC, (int)m_tInfo.tL_Point.fX + iScroll_X, (int)m_tInfo.tL_Point.fY + iScroll_Y, nullptr);
	LineTo(_hDC, (int)m_tInfo.tR_Point.fX + iScroll_X, (int)m_tInfo.tR_Point.fY + iScroll_Y);
	// 왼쪽 점의 좌표를 가져온 지점부터 , 오른쪽 점의 좌표를 가져온 지점까지 줄을 그어라 
}
