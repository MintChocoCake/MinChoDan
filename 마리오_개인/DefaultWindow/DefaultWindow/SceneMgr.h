#pragma once
#include "Scene.h"

class CSceneMgr
{
#pragma region Singleton
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr* Get_Instance() {
		if (!m_pInstance) {
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static void Delete_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;
#pragma endregion

public:
	enum SCENE_ID {
		SCENE_ID_NONE = -1,
		SCENE_ID_SPLASH,
		SCENE_ID_LOBBY,
		SCENE_ID_STAGE,
		SCENE_ID_EDIT,
		SCENE_ID_END
	};

public:
	CScene* Get_CurScene() { return m_pScene; }

public:
	void Initialize(void);
	void Update(void);
	void LateUpdate(void);
	void Render(HDC hDC);
	void Release(void);
	void Change_Scene(SCENE_ID _eID);

private:
	SCENE_ID m_ePrevScene;
	SCENE_ID m_eCurScene;
	CScene* m_pScene;
};

