#pragma once
#include "Scene.h"
#include "BitmapMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "MyButton.h"

class CMyMenu :
	public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void		Initialize(void)override;
	virtual int			Update(void)	override;
	virtual void		Late_Update(void)override;
	virtual void		Render(HDC hDC)	override;
	virtual void		Release(void)	override;

};

