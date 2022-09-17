#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(BYTE _BKey)
{
	if(GetAsyncKeyState(_BKey) & 0x8000)
		return true;
	return false;
}

bool CKeyMgr::Key_Down(BYTE _BKey)
{
	if (!m_arrbKeyState[_BKey] && GetAsyncKeyState(_BKey) & 0x8000) {
		m_arrbKeyState[_BKey] = true;
		return true;
	}

	for (BYTE i = 0; i < VK_MAX; ++i) {
		if(m_arrbKeyState[_BKey] && !(GetAsyncKeyState(_BKey) & 0x8000))
			m_arrbKeyState[_BKey] = false;
	}

	return false;
}

bool CKeyMgr::Key_Up(BYTE _BKey)
{
	if (m_arrbKeyState[_BKey] && !(GetAsyncKeyState(_BKey) & 0x8000)) {
		m_arrbKeyState[_BKey] = false;
		return true;
	}

	for (BYTE i = 0; i < VK_MAX; ++i) {
		if (!m_arrbKeyState[_BKey] && GetAsyncKeyState(_BKey) & 0x8000)
			m_arrbKeyState[_BKey] = true;
	}

	return false;
}
