#pragma once
#include "Obj.h"

class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	ITEM_ID Get_ItemID(void) { return m_eItemID; }

public:
	void Set_ItemID(ITEM_ID _eID);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	//virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

private:
	ITEM_ID m_eItemID;
	DWORD m_dwTimer;
};

