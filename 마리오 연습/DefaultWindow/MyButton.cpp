#include "stdafx.h"
#include "MyButton.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	// ��ư ������ ����
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 50.f;
}

int CMyButton::Update(void)
{
	// ��ư�� �� �� �� �� ����
	Update_Rect();
	return OBJ_NO_EVENT;
}

void CMyButton::Late_Update(void)
{
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		// VK_LBUTTON ���α׸���� ���ļ� ���߿� ����
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrame_Key))
				CSceneMgr::Get_Instance()->Scen_Change(CSceneMgr::SC_STAGE);
			else if (!lstrcmp(L"Edit", m_pFrame_Key))
				CSceneMgr::Get_Instance()->Scen_Change(CSceneMgr::SC_EDIT);
			
			else
				DestroyWindow(g_hWnd);

			return;
		}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;

}

void CMyButton::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->Find_Bmp(m_pFrame_Key);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left,
		(int)m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_iDrawID,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));

}

void CMyButton::Release(void)
{
}
