#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f) , m_fAngle(0.f), m_bDead(false), m_pTarget(nullptr), m_pFrame_Key(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Move_Frame(void)
{
	// ������ ���� ? �ð� + �ӵ� < ��Ƽī��Ʈ -> �ִϸ��̼� ��� �ð� ����
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// ������ �ε��� ���� ( ���� )
		++m_tFrame.iStart;
		// ����ӵ� �ʱ�ȭ ? ��� ���൵ �ʱ�ȭ
		m_tFrame.dwTime = GetTickCount();

		// �������� �ε��� �������� ���� ���� �ʱ�ȭ
		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}
}
