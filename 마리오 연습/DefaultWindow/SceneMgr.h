#pragma once

#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "MyEdit.h"

class CSceneMgr
{
public:
	enum SCENID { SC_LOGO, SC_MENU, SC_STAGE, SC_EDIT, SC_END };
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void				Scen_Change(SCENID _eScene);
	void				Update(void);
	void				Late_Update(void);
	void				Render(HDC hDC);
	void				Release(void);

public:
	static CSceneMgr*	Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static void			Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;

	// °ú°Å ¾À , ÇöÀç ¾À
	SCENID				m_ePreScene;
	SCENID				m_eCurScene;


};

