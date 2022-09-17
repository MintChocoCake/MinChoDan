#pragma once

#include "Scene.h"
#include "Player.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BitmapMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "TileMgr.h"


class CStage : public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

public:
	void				Create_Monster(float _fPosx, MONSTERTYPE _eType);
	float				fGumX = 0.f;
	float				fTulX = 0.f;

private:
	
};

