#pragma once

#include "Define.h"
#include "Player.h"

#include "LineMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"

class CMainGame
{
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];


	CObj*		m_pPlayer = nullptr;

	bool		m_bLogo = false;

public:
	CMainGame();
	~CMainGame();
};

