#pragma once

#include "Define.h"

#include "Obj.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "BitmapMgr.h"
#include "ObjMgr.h"


class CMonster :
	public CObj
{
	enum STATE { LEFTIDLE, LEFTWALK, RIGHTIDLE, RIGHTWALK, STATE_END };
	
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;


public:
	void				Moster_Move(void);
	void				State_Change(void);

private:

	STATE				m_ePreState;
	STATE				m_eCurState;


};

