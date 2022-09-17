#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float			Get_Scroll_X(void) { return m_fScroll_X; }
	void			Set_Scroll_X(float _fX) { m_fScroll_X += _fX; }

	float			Get_Scroll_Y(void) { return m_fScroll_Y; }
	void			Set_Scroll_Y(float _fY) { m_fScroll_Y += _fY; }

	void			Scroll_Lock(void);

public:
	static	CScrollMgr*	Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}
	static	void		Destroy_Instance()
	{
		/*if (m_pInstance)
			Safe_Delete(m_pInstance);*/
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr*		m_pInstance;
	float					m_fScroll_X;
	float					m_fScroll_Y;

};

