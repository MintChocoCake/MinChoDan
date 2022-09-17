#pragma once
#include "Define.h"

class CKeyMgr
{
#pragma region Singleton
private:
	CKeyMgr();
	~CKeyMgr();

public:
	static CKeyMgr* Get_Instance() {
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;

		return m_pInstance;
	}

	static void	Delete_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CKeyMgr* m_pInstance;
#pragma endregion

public:
	bool Key_Pressing(BYTE _BKey);
	bool Key_Down(BYTE _BKey);
	bool Key_Up(BYTE _BKey);

private:
	bool m_arrbKeyState[VK_MAX];
};

