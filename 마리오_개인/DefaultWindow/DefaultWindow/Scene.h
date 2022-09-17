#pragma once
#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize(void) PURE;
	virtual void  Update(void) PURE;
	virtual void LateUpdate(void) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;
};

