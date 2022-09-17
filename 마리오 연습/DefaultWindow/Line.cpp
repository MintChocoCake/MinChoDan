#include "stdafx.h"
#include "Line.h"


CLine::CLine()
	
{
}

CLine::CLine(MYPOINT& _tLeft, MYPOINT & _tRight)
	: m_tInfo(_tLeft,_tRight) // �� why -> LINE ����ü �����ڰ� MYPOINT& �ŰԺ����� 2�� �����ϱ�
{
}

CLine::CLine(LINE & _tLine)
{
	memcpy(&m_tInfo, &_tLine, sizeof(LINE));
	// m_tInfo �� _tLine �� ������ �����ϰڴ�.
}


CLine::~CLine()
{
}

void CLine::Render(HDC _hDC)
{
	// ��ũ�� X �� ��������
	int iScroll_X = CScrollMgr::Get_Instance()->Get_Scroll_X();
	int	iScroll_Y = CScrollMgr::Get_Instance()->Get_Scroll_Y();
	// ���� ���� �����ϴ� ���� : �̷��� ���� ������ ������ �׸� �� ���� �Լ��� ȣ���ؾ��ؼ� �׸�ŭ ���귮�� �����Ѵ�

	// X ��ǥ�ڿ� + ��ũ�� X 
	MoveToEx(_hDC, (int)m_tInfo.tL_Point.fX + iScroll_X, (int)m_tInfo.tL_Point.fY + iScroll_Y, nullptr);
	LineTo(_hDC, (int)m_tInfo.tR_Point.fX + iScroll_X, (int)m_tInfo.tR_Point.fY + iScroll_Y);
	// ���� ���� ��ǥ�� ������ �������� , ������ ���� ��ǥ�� ������ �������� ���� �׾�� 
}
