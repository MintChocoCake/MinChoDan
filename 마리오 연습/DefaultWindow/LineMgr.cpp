#include "stdafx.h"
#include "LineMgr.h"


CLineMgr*	CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
	ZeroMemory(m_LinePoint, sizeof(m_LinePoint));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	// ���� ����� �ε带 ���� �Ŵ������� �ؼ� �ʱ�ȭ������ ������ �ҷ���
	Load_File();
}

int CLineMgr::Update(void)
{
	// ���� 
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LSHIFT))
		m_bDrowing = true;
	
	// �ӽ� - �׸��� false ������ ����..
	if (false == m_bDrowing)
	{

		POINT		pt{};

		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		// �����ο��� exturn �س��� �ڵ� g_hWnd

		pt.x -= (long)CScrollMgr::Get_Instance()->Get_Scroll_X();
		// �÷��̾ ���������� �����δ�. ->  �÷��̾��� x ��ǥ�� +  , ��ũ���� x ��ǥ�� - 
		// �� ���� ���Ǿ�� �÷��̾ �߾� / �߾� ������ ����( 100<=  ���� ����� ����

		pt.y -= (long)CScrollMgr::Get_Instance()->Get_Scroll_Y();


		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			// ���� ����Ʈ ���� ����
			// ���� ������ X �� ���̾��� && ���� ������ Y �� ���� ���ٸ�
			if (!m_LinePoint[LEFT].fX && !m_LinePoint[LEFT].fY)
			{
				// ù���콺 ��ǥ�� ����
				m_LinePoint[LEFT].fX = (float)pt.x;
				m_LinePoint[LEFT].fY = (float)pt.y;
			}
			// ���� ���� ����
			else
			{
				// �¿� �׸��� y ��ǥ ����
				if (CKeyMgr::Get_Instance()->Key_Down('Q'))
				{
					pt.y = m_LinePoint[LEFT].fY;
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				else
				{
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				// ���� �׸��� x ��ǥ ���� 
				if (CKeyMgr::Get_Instance()->Key_Down('E'))
				{
					pt.x = m_LinePoint[LEFT].fX;
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				else
				{
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				// ���콺 ��ǥ
				//m_LinePoint[RIGHT].fX = (float)pt.x;
				//m_LinePoint[RIGHT].fY = (float)pt.y;

				// ����, ������ ���� ��ǥ�� �Ѱ��� ( Line ���� �� ���� ������ �׸� )
				m_LineList.push_back(new CLine(m_LinePoint[LEFT], m_LinePoint[RIGHT]));

				// ���� ���� �׸���, ������ ���� ���� ���� �Ǿ� �ؼ� ������ ���� ��ǥ�� ���� ���� ��ǥ�� �ǰ� �ٲ��ֱ� 
				m_LinePoint[LEFT].fX = m_LinePoint[RIGHT].fX;
				m_LinePoint[LEFT].fY = m_LinePoint[RIGHT].fY;
			}
		}

		// ������ ������ Ŭ������ ������ǥ �ʱ�ȭ
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			m_LinePoint[LEFT].fX = (float)pt.x;
			m_LinePoint[LEFT].fY = (float)pt.y;
		}

	}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_File();
		return 0;
	}

	// Ŭ���̾�Ʈ �����̶� ���߿� ���ߵǴ� �κ�
	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		Load_File();
		return 0;
	}

	// ��ũ���� �÷��̾� ����� �ݴ�� �̵��Ͽ� ������ ����Ŵ ?
	// ���� Ű�� ������ ��ũ���� ���������� �̵�
	/*
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(5.f);
	// ������ Ű�� ������ ��ũ���� �������� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(-5.f);
		*/

	return 0;
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC _hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(_hDC);
}

void CLineMgr::Release(void)
{
	// ���� ����Ʈ�� ù���� ���� �� ���� Ž���ؼ� ������ ����Ʈ
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	// �ش� ����� ����Ʈ�� ����
	m_LineList.clear();
}

// ���� Ÿ�� ( x ��ǥ�� ���۷��� y ��ǥ�� ���������� ��� ���� ? )
bool CLineMgr::Collision_Line(float& _fX, float& _fY, float* _pfY)
{
	// TargetLine�� �����ϱ����� �÷��̾� ��ġ�� ���ؼ� ����������

	if (m_LineList.empty())
		return false;

	// ������ Ÿ���� Ÿ�� ����
	CLine*		pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tL_Point.fX &&
			_fX <= iter->Get_Info().tR_Point.fX &&
			_fY <= iter->Get_Info().tL_Point.fY &&
			_fY <= iter->Get_Info().tR_Point.fY) {
			pTargetLine = iter;
			/*if (*_pfY - iter->Get_Info().tL_Point.fY >
				*_pfY - iter->Get_Info().tR_Point.fY)
			{
				pTargetLine = iter;
			}
			else if (*_pfY - iter->Get_Info().tL_Point.fY <
				*_pfY - iter->Get_Info().tR_Point.fY)
			{
				pTargetLine = iter;
			}*/
		}
	}

	if (nullptr == pTargetLine)
		return false;

	// ����Ÿ�� ���� : ������ ������
	// Y = ( ���� / �غ� ) * [Y����]( X - x1 ) + y1  
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pTargetLine->Get_Info().tL_Point.fX;
	float	y1 = pTargetLine->Get_Info().tL_Point.fY;

	float	x2 = pTargetLine->Get_Info().tR_Point.fX;
	float	y2 = pTargetLine->Get_Info().tR_Point.fY;

	*_pfY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
	

	/*
	if (m_LineList.empty())
		return false;

	// ������ Ÿ���� Ÿ�� ����
	CLine*		pTargetLine = nullptr;

	float		fLine_PY = 0.f;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tL_Point.fX &&
			_fX <= iter->Get_Info().tR_Point.fX) {
			
			float	x1 = iter->Get_Info().tL_Point.fX;
			float	y1 = iter->Get_Info().tL_Point.fY;

			float	x2 = iter->Get_Info().tR_Point.fX;
			float	y2 = iter->Get_Info().tR_Point.fY;

			fLine_PY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			if (fLine_PY >= *_pfY && fLine_PY <= *_pfY )
			{
				*_pfY = fLine_PY;
				pTargetLine = iter;
				return true;
			}
		}
	}

	if (nullptr == pTargetLine)
		return false;
		*/

	// ����Ÿ�� ���� : ������ ������
	// Y = ( ���� / �غ� ) * [Y����]( X - x1 ) + y1  
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	/*float	x1 = pTargetLine->Get_Info().tL_Point.fX;
	float	y1 = pTargetLine->Get_Info().tL_Point.fY;

	float	x2 = pTargetLine->Get_Info().tR_Point.fX;
	float	y2 = pTargetLine->Get_Info().tR_Point.fY;

	fLine_PY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
	*/
}

void CLineMgr::Save_File(void)
{
	// ���� ����
	HANDLE		hFile = CreateFile(L"../IsData/Line.dat", // ���ϰ�� , ������ ���� �̸�
		GENERIC_WRITE,	// ���� ���� ��� (���� ����) GENERIC_READ(�б� ����)
		NULL,			
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// ���� ���н� ��ȯ�Ǵ� ��ũ�� ( -1 �� )
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		// ���� ����
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);
		// ( ������ ���� , ������ ������ �ּ� , ������ ������ ũ�� , ����ó�� �� ���� �ּ� , ��?��
	}

	// ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save ����"), L"����", MB_OK);

}

void CLineMgr::Load_File(void)
{
	HANDLE		hFile = CreateFile(L"../IsData/Line.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	// ���� �ε� �� ������ ������ �޾ƾ��� LINE Ÿ�� tIfno
	LINE		tInfo{}; 

	// ������ ������ �� �о� �������� while �� ���
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		// ���ܰ� 0 ( �� �о����� ) Ż��
		if (0 == dwByte)
			break;

		// Info ������ Line �������Ͽ� �����ϰ� ������ ��Ҹ� ����Ʈ�� ����
		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load ����"), L"����", MB_OK);
}
