#pragma once
#include "MyBitmap.h"

class CBmpMgr
{
#pragma region Singleton
private:
	CBmpMgr();
	~CBmpMgr();

public:
	static CBmpMgr* Get_Instance() {
		if (!m_pInstance)
			m_pInstance = new CBmpMgr;

		return m_pInstance;
	}

	static void	Delete_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBmpMgr* m_pInstance;
#pragma endregion

public:
	void Initialize();
	void Insert_Bmp(const TCHAR* _chFilePath, BMP_KEY _eKey);
	CMyBitmap* Find_Bmp(BMP_KEY _eKey);

private:
	map<BMP_KEY, CMyBitmap*> m_BmpMap;

private:
	void Release();
};

