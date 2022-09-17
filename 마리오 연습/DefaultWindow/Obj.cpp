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
	// 프레임 제한 ? 시간 + 속도 < 겟티카운트 -> 애니메이션 재생 시간 조정
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// 프레임 인덱스 증가 ( 진행 )
		++m_tFrame.iStart;
		// 재생속도 초기화 ? 재생 진행도 초기화
		m_tFrame.dwTime = GetTickCount();

		// 프레임의 인덱스 시작점이 끝에 가면 초기화
		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}
}
