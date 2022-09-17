#pragma once
#include "stdafx.h"
#include "Line.h"
#include "Define.h"
#include "Obj.h"
#include "Block.h"

class CMapMgr
{
#pragma region Singleton
private:
	CMapMgr();
	~CMapMgr();

public:
	static CMapMgr* Get_Instance() {
		if (!m_pInstance)
			m_pInstance = new CMapMgr;

		return m_pInstance;
	}

	static void	Delete_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CMapMgr* m_pInstance;
#pragma endregion

public:
	void SetActive(bool _bValue) { m_bActive = _bValue; }

public:
	void Initialize();
	void Update();
	void Render(HDC _HDC);
	void Load_Map();

private:
	list<CLine> m_LineList;
	CLine	m_LineTemp;
	bool	m_bDrawing;
	bool	m_bActive;
	wchar_t m_szBuffer[100];

private:
	void Key_Input();
	void Get_Cursor(MYPOINT* _tResult);
	void Save_Map();
	void Create_Block(BLOCK_ID _eID, MYPOINT _tPos = MYPOINT{-1, -1});
	void Create_Monster(MONSTER_ID _eID, MYPOINT _tPos = MYPOINT{ -1, -1 });
};

