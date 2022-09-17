#include "stdafx.h"
#include "SceneMgr.h"
#include "Splash.h"
#include "Lobby.h"
#include "Stage.h"
#include "MapEdit.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_ePrevScene(SCENE_ID_NONE), m_eCurScene(SCENE_ID_END), m_pScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Change_Scene(SCENE_ID _eID)
{
	m_eCurScene = _eID;

	if (m_ePrevScene != m_eCurScene) {
		Safe_Delete(m_pScene);

		switch (_eID)
		{
		case SCENE_ID_SPLASH:
			m_pScene = new CSplash;
			break;

		case SCENE_ID_LOBBY:
			m_pScene = new CLobby;
			break;

		case SCENE_ID_STAGE:
			m_pScene = new CStage;
			break;

		case SCENE_ID_EDIT:
			m_pScene = new CMapEdit;
			break;
		}

		m_pScene->Initialize();
		m_ePrevScene = m_eCurScene;
	}
}


void CSceneMgr::Initialize(void)
{

}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate(void)
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}

