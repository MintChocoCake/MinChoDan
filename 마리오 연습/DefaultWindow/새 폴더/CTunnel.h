#pragma once
#include "CBox.h"

class CTunnel : public CBox
{
public:
	CTunnel();
	CTunnel(INFO _tInfo);
	virtual ~CTunnel();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};