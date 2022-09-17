#pragma once
#include "Scene.h"
class CMapEdit :
	public CScene
{
public:
	CMapEdit();
	virtual ~CMapEdit();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

