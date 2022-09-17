#pragma once

#include "Define.h"
#include "Player.h"

class CMainGame
{
public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;
	CObj*		m_pPlayer = nullptr;
	DWORD		m_dwFPSTimer;
	DWORD		m_dwFPS;

public:
	CMainGame();
	~CMainGame();
};

