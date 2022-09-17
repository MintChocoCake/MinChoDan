#pragma once
#include "Define.h"

class CScrollMgr
{
#pragma region Singleton
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static CScrollMgr* Get_Instance() {
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static void	Delete_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr* m_pInstance;
#pragma endregion

public:
	float Get_X() { return m_fScrollX; }
	float Get_Y() { return m_fScrollY; }

public:
	void Add_X(float _fValue) { m_fScrollX += _fValue; }
	void Add_Y(float _fValue) { m_fScrollY += _fValue; }

public:
	void Scroll_Lock();

private:
	float m_fScrollX;
	float m_fScrollY;
};

