#pragma once
#include "CBox.h"

class CItemBlock : public CBox
{
public:
	CItemBlock();
	virtual ~CItemBlock();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	void CollisonEffect();
	void DropRandomItem();
private:
	float UPDest;
	float DownDest;
	bool isUP = false;
	bool isDown = false;
	bool isStart = false;
};

