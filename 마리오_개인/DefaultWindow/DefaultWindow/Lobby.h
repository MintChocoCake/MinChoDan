#pragma once
#include "Scene.h"
class CLobby :
	public CScene
{
public:
	CLobby();
	virtual ~CLobby();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

