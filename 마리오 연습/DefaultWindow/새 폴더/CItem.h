#pragma once
#include "Obj.h"

class CItem : public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

