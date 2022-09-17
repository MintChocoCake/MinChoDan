#pragma once
#include "Obj.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"

class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	void				Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void				Set_Option(int _iOption) { m_iOption = _iOption; }

	int					Get_DrawID() const { return m_iDrawID; }
	int					Get_Option() const { return m_iOption; }

private:
	int					m_iDrawID = 0;
	int					m_iOption = 0;
};

