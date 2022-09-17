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

	// �ý�ó
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/ui_item_star.bmp", L"Player");

	// �÷��̾� ��������Ʈ
	
	m_ePreState = STATE_END;
	m_eCurState = LEFTIDLE;

	m_pFrame_Key = L"Player_LEFT";
	
	// �÷��̾��� ������ ���� �̹��� ���
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Player/Mario.bmp", L"Player_LEFT");

	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Player/SmallMarioLeft.bmp", L"Player_LEFT");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Player/SmallMarioRight.bmp", L"Player_RIGHT");


	// ���� ���� ��� ����
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
	// ���� ��ũ�� x �� ���������� �Լ��� ȣ���ؾ������� ���귮�� ������� ����
	int	iScroll_X = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int	iScroll_Y = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	// �������
	/*
	Rectangle(hDC,
		m_tRect.left + iScroll_X,
		m_tRect.top - iScroll_Y,
		m_tRect.right + iScroll_X,
		m_tRect.bottom - iScroll_Y);

	MoveToEx(hDC, (int)m_tInfo.fX + iScroll_X, (int)m_tInfo.fY - iScroll_Y, nullptr);
	
	LineTo(hDC, m_tBarrel.x + iScroll_X, m_tBarrel.y - iScroll_Y);
	*/

	// �ؽ�ó ���� �÷��̾� 
	// �� �Ŵ��� ��� ��
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

	// �� �Ŵ��� ��� �� 

	HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(m_pFrame_Key);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScroll_X,
		(int)m_tRect.top + iScroll_Y,  // �� �÷�����
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
	// �� �Ŵ��� ���� ��
	
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

	// �� �Ŵ��� ������ 
	// Ű ������ �´� �̹�����ã�� ������� �ൿ�� �˸°� �����δ�
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
	// ������ �Ǵµ� ������ �����鵿�۾���..
	float	fY = 0;

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);
	//bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &m_tInfo.fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		// ���� x ���� ���̸� , ���� �÷��̾� ���� �������� (����)
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

	//// ���� �÷��̾� ���� ���� ���� 
	//else if (fY > m_tInfo.fY)
	//{
	//	// �÷��̾ ������ ���ų� ������ ����
	//	if (m_tInfo.fY <= fY)
	//	{
	//		// �÷��̾ ������
	//		m_tInfo.fY += 5.f;
	//	}
	//}
	// �÷��̾ ������ �Ʒ� ���� �� ( ������ ���� �Ʒ� ���� )
	//else if (fY < m_tInfo.fY)
	//{
		// �÷��̾ �ٴڿ� ������ ���� ������
		//if (m_tInfo.fY <= WINCY)
		//{
		//	m_tInfo.fY += 5.f;
		//}
	//}
}

void CPlayer::OffSet(void)
{
	// �÷��̾ ���� ���� �� �Ѿ�� ȭ���� �����̰�
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

	// �� �ݴ�� ����
	// ���� �ö󰡸�
	if (fOffSetMin_Y > m_tInfo.fY + iScroll_Y)
		CScrollMgr::Get_Instance()->Set_Scroll_Y(m_fSpeed);

	// �Ʒ��� ��������
	if (fOffSetMax_Y < m_tInfo.fY + iScroll_Y)
		CScrollMgr::Get_Instance()->Set_Scroll_Y(-m_fSpeed);
}

void CPlayer::State_Change(void)
{
	// �÷��̾��� �ൿ(�̹���) ������Ʈ

	if (m_ePreState != m_eCurState)
	{ 
		// ����� ���� ���� �ٸ� ��

		// fsm ����
		// �̹��� bmp ���� ÷���ϸ� ��ġ ����
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
