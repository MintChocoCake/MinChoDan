#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	: m_bJump(false), m_fPower(0.f), m_fTime(0.f), m_fPI(3.141592f)
{
	ZeroMemory(&m_tBarrel, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 200.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 5.f;

	m_fDistance = 100.f;
	m_fPower = 20.f;

	// 택스처
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/ui_item_star.bmp", L"Player");

	// 플레이어 스프라이트
	
	m_ePreState = STATE_END;
	m_eCurState = LEFTIDLE;

	m_pFrame_Key = L"Player_LEFT";
	
	// 플레이어의 움직임 마다 이미지 출력
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Player/Mario.bmp", L"Player_LEFT");

	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Player/SmallMarioLeft.bmp", L"Player_LEFT");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Player/SmallMarioRight.bmp", L"Player_RIGHT");


	// 씬의 여러 기능 조절
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iMotion = 9;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();;
}

int CPlayer::Update(void)
{
	Key_Input();
	Jump();
	OffSet();

	State_Change();

	Move_Frame();

	Update_Rect();

	return OBJ_NO_EVENT;
}

void CPlayer::Late_Update(void)
{
	//m_tBarrel.x = LONG(m_tInfo.fX + m_fDistance * cos(m_fAngle * (PI / 180.f)));
	//m_tBarrel.y = LONG(m_tInfo.fY - m_fDistance * sin(m_fAngle * (PI / 180.f)));
}

void CPlayer::Render(HDC hDC)
{
	// 따로 스크롤 x 를 담지않으면 함수를 호출해야함으로 연산량이 쓸대없이 증가
	int	iScroll_X = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int	iScroll_Y = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	// 수정모드
	/*
	Rectangle(hDC,
		m_tRect.left + iScroll_X,
		m_tRect.top - iScroll_Y,
		m_tRect.right + iScroll_X,
		m_tRect.bottom - iScroll_Y);

	MoveToEx(hDC, (int)m_tInfo.fX + iScroll_X, (int)m_tInfo.fY - iScroll_Y, nullptr);
	
	LineTo(hDC, m_tBarrel.x + iScroll_X, m_tBarrel.y - iScroll_Y);
	*/

	// 텍스처 입힌 플레이어 
	// 신 매니저 사용 전
	/*HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Player");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScroll_X,
		(int)m_tRect.top - iScroll_Y,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(246, 83, 166));*/

	// 신 매니저 사용 후 

	HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(m_pFrame_Key);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScroll_X,
		(int)m_tRect.top + iScroll_Y,  // 왜 플러스지
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));

}

void CPlayer::Release(void)
{
	
}

void CPlayer::Key_Input(void)
{
	// 신 매니저 적용 전
	
	/*if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (!m_bJump)
		{
			m_bJump = true;
		}
	}*/

	// 신 매니저 적용후 
	// 키 값으로 맞는 이미지를찾고 현재씬을 행동에 알맞게 움직인다
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrame_Key = L"Player_LEFT";
		m_eCurState = LEFTWALK;
	}
	/*else
		m_eCurState = LEFTIDLE;*/

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrame_Key = L"Player_RIGHT";
		m_eCurState = RIGHTWALK;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}
	else
		m_eCurState = RIGHTIDLE;

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (!m_bJump)
		{
			m_bJump = true;
		}
	}

}

void CPlayer::Jump(void)
{
	// 점프는 되는데 선위에 있으면동작안함..
	float	fY = 0;

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);
	//bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &m_tInfo.fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		// 선의 x 범위 안이며 , 선이 플레이어 보다 높아지면 (착지)
		if (bLineCol && fY < m_tInfo.fY)
			//if (m_fTime > 7.f)
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY - m_tInfo.fCX / 2.f;

		}

	}
	else if(bLineCol)
		m_tInfo.fY = fY - m_tInfo.fCX / 2.f;
	else
	{
		if (m_tInfo.fY <= WINCY)
			m_tInfo.fY += 5.f;
	}

	//// 선이 플레이어 보다 위에 있을 
	//else if (fY > m_tInfo.fY)
	//{
	//	// 플레이어가 선보다 위거나 같을때 까지
	//	if (m_tInfo.fY <= fY)
	//	{
	//		// 플레이어를 내린다
	//		m_tInfo.fY += 5.f;
	//	}
	//}
	// 플레이어가 선보다 아래 있을 때 ( 선보다 좀더 아래 기준 )
	//else if (fY < m_tInfo.fY)
	//{
		// 플레이어가 바닥에 닿을때 까지 내린다
		//if (m_tInfo.fY <= WINCY)
		//{
		//	m_tInfo.fY += 5.f;
		//}
	//}
}

void CPlayer::OffSet(void)
{
	// 플레이어가 일정 범위 를 넘어야 화면이 움직이게
	float	fOffSetMin_X = 100.f;
	float	fOffSetMax_X = 700.f;

	float	fOffSetMin_Y = 100.f;
	float	fOffSetMax_Y = 700.f;

	int		iScroll_X = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int		iScroll_Y = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	if (fOffSetMin_X > m_tInfo.fX + iScroll_X)
		CScrollMgr::Get_Instance()->Set_Scroll_X(m_fSpeed);

	if (fOffSetMax_X < m_tInfo.fX + iScroll_X)
		CScrollMgr::Get_Instance()->Set_Scroll_X(-m_fSpeed);

	// 왜 반대로 되지
	// 위로 올라가면
	if (fOffSetMin_Y > m_tInfo.fY + iScroll_Y)
		CScrollMgr::Get_Instance()->Set_Scroll_Y(m_fSpeed);

	// 아래로 내려가면
	if (fOffSetMax_Y < m_tInfo.fY + iScroll_Y)
		CScrollMgr::Get_Instance()->Set_Scroll_Y(-m_fSpeed);
}

void CPlayer::State_Change(void)
{
	// 플레이어의 행동(이미지) 업데이트

	if (m_ePreState != m_eCurState)
	{ 
		// 현재와 과거 씬이 다를 때

		// fsm 형태
		// 이미지 bmp 파일 첨부하면 수치 조정
		switch (m_eCurState)
		{
		case LEFTIDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case LEFTWALK:
			m_tFrame.iStart = 1;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case RIGHTIDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case RIGHTWALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}
