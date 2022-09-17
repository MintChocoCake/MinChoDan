#pragma once
#include "Define.h"

class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();

public:
	HDC& Get_BmpDC() { return m_hMemDC; }

public:
	void Load_Bmp(const TCHAR* _chFilePath);
	void Release();

private:
	HDC m_hDC;
	HDC m_hMemDC;

	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
};

