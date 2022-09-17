#pragma once
#include "Scene.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"

class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void		Initialize(void)override;
	virtual int			Update(void)	override;
	virtual void		Late_Update(void)override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release(void)	override;

private:
	void				Key_Check(void);
};

