#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
}

void CMyBitmap::Load_Bmp(const TCHAR * _chFilePath)
{
	m_hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	m_hBmp = (HBITMAP)LoadImage(NULL, _chFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteDC(m_hMemDC);
	ReleaseDC(g_hWnd, m_hDC);
}
