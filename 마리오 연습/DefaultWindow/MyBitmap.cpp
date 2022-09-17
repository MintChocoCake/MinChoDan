#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::Load_Bmp(const TCHAR * _pFilePath)
{
	HDC			hDC = GetDC(g_hWnd);


	m_hMemDC = CreateCompatibleDC(hDC);
	// 레퍼런스 카운터를 감소시킨다 ( 같은 주소값을 지니고 있어 메모리를 지우면 다른곳에서 몰라서 )
	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,
								_pFilePath,
								IMAGE_BITMAP,
								0,
								0,
								LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
