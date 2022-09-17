#pragma once
#include "Obj.h"
class CUIButton :
	public CObj
{
public:
	enum BUTTON_ID {
		BUTTON_ID_NONE = -1,
		BUTTON_ID_START,
		BUTTON_ID_EDIT,
		BUTTON_ID_EXIT,
		BUTTON_ID_END
	};

public:
	CUIButton();
	virtual ~CUIButton();

public:
	void SetButtonID(BUTTON_ID _eID);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override {};
	//virtual void Render(HDC hDC) override;
	virtual void Release(void) override {};
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

private:
	BUTTON_ID m_eBtnID;
};

