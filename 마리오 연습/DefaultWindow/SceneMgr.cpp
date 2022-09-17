#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_LOGO), m_ePreScene(SC_END) 
	// 현재 씬과 과거 씬을 표현하는 씬을 둘다 END 초기화 하면 안된다.
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scen_Change(SCENID _eScene)
{
	// 받은 씬을 컷신에 저장
	m_eCurScene = _eScene;

	if (m_ePreScene != m_eCurScene)
	{
		// 씬이 넘어갈때 이전 씬을 삭제 - 방법은 이것 말고도 여러가지
		Safe_Delete(m_pScene);

		// fsm 형태 
		switch (m_eCurScene)
		{
			// 열거체에 맞는 씬들을 메모리로 가져온다
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			break;
		}
		m_pScene->Initialize();

		// 과거의 씬을 현재의 씬으로 맞춰준다
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
