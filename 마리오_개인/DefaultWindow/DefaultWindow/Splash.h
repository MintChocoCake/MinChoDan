#pragma once
#include "Scene.h"
class CSplash :
	public CScene
{
public:
	CSplash();
	virtual ~CSplash();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

