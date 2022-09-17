#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_LOGO), m_ePreScene(SC_END) 
	// ���� ���� ���� ���� ǥ���ϴ� ���� �Ѵ� END �ʱ�ȭ �ϸ� �ȵȴ�.
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scen_Change(SCENID _eScene)
{
	// ���� ���� �ƽſ� ����
	m_eCurScene = _eScene;

	if (m_ePreScene != m_eCurScene)
	{
		// ���� �Ѿ�� ���� ���� ���� - ����� �̰� ���� ��������
		Safe_Delete(m_pScene);

		// fsm ���� 
		switch (m_eCurScene)
		{
			// ����ü�� �´� ������ �޸𸮷� �����´�
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

		// ������ ���� ������ ������ �����ش�
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
