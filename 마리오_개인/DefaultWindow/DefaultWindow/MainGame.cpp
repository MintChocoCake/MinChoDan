#include "stdafx.h"
#include "MainGame.h"
#include "MapMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CMainGame::CMainGame() : m_dwFPSTimer(0)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Initialize();
	CMapMgr::Get_Instance()->Initialize();

	CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::SCENE_ID_SPLASH);
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();	
}

void CMainGame::LateUpdate(void)
{
	CScrollMgr::Get_Instance()->Scroll_Lock();
	CSceneMgr::Get_Instance()->LateUpdate();
}

void CMainGame::Render(void)
{
	CSceneMgr::Get_Instance()->Render(m_DC);

	++m_dwFPS;

	TCHAR szBuffer[30];
	if (m_dwFPSTimer + 1000 < GetTickCount()) {

		wsprintf(szBuffer, L"FPS: %d", m_dwFPS);
		SetWindowText(g_hWnd, szBuffer);

		m_dwFPS = 0;
		m_dwFPSTimer = GetTickCount();
	}
}

void CMainGame::Release(void)
{
	CObjMgr::Delete_Instance();
	CSceneMgr::Delete_Instance();
	CMapMgr::Delete_Instance();
	CBmpMgr::Delete_Instance();
	CScrollMgr::Delete_Instance();
	CKeyMgr::Delete_Instance();

	ReleaseDC(g_hWnd, m_DC);
}