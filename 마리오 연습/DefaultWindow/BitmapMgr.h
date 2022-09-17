#pragma once

#include "MyBitmap.h"

class CBitmapMgr
{
public:
	CBitmapMgr();
	~CBitmapMgr();

public:
	void			Insert_Bmp(const TCHAR* _pFilePath, const TCHAR* _pImgKey);
	HDC				Find_Bmp(const TCHAR* _pImgKey);
	void			Release(void);

public:
	static CBitmapMgr*	Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CBitmapMgr;

		return m_pInstance;
	}
	
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBitmapMgr*				m_pInstance;

	map<const TCHAR*, CMyBitmap*>	m_mapBit;
};

