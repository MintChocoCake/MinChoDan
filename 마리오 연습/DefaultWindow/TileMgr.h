#pragma once

#include "Tile.h"

#include "AbstractFactory.h"
#include "ScrollMgr.h"


class CTileMgr
{
private:
	CTileMgr();
	CTileMgr(const CTileMgr& rhs) = delete;
	CTileMgr& operator =(const CTileMgr& rhs) = delete;
	CTileMgr(CTileMgr&& rhs) = delete;
	CTileMgr& operator=(CTileMgr&& rhs) = delete;
	~CTileMgr();


public:
	void			Initialize(void);
	void			Update(void);
	void			Late_Update(void);
	void			Render(HDC hDC);
	void			Release(void);

	void			Picking_Tile(POINT _pt, const int& _iDrawID, const int& _iOption);

	void			Save_Tile(void);
	void			Load_Tile(void);

public:
	static CTileMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;

		return m_pInstance;
	}
	
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CTileMgr*		m_pInstance;
	vector<CObj*>			m_vecTile;

};

