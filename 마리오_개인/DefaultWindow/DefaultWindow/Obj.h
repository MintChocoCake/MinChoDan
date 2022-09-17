#pragma once
#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	INFO& Get_Info() { return m_tInfo; }
	OBJ_TYPE Get_Type() { return m_eType; }
	DWORD Get_InstanceID() { return m_dwInstanceID; }
	bool Col_Before(DWORD _dwTarget);
	bool Get_Active() { return m_bActive; }
	DWORD Get_HP() { return m_dwHP; }

public:
	void Add_Col(DWORD _dwTarget);
	void Delete_Col(DWORD _dwTarget);
	void Add_HP(DWORD _dwValue) { m_dwHP += _dwValue; }
	void Set_Dead() { m_bDead = true; }
	void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_Type(OBJ_TYPE _eID) { m_eType = _eID; }

public:
	virtual void Initialize(void) PURE;
	virtual int  Update(void) PURE;
	virtual void LateUpdate(void) PURE;
	virtual void Render(HDC hDC);
	virtual void Release(void) PURE;
	virtual void OnCollision(CObj* _pTarget) PURE;
	virtual void OnCollisionEnter(CObj* _pTarget) PURE;

protected:
	void		Update_Rect(void);
	void		Update_Frame(void);
	void		Update_Active(void);

protected:
	INFO m_tInfo;
	RECT m_tRect;
	OBJ_TYPE m_eType;

	float m_fSpeed;
	DWORD m_dwHP;
	bool m_bDead;

	HDC* m_hBmpDC;
	FRAME m_tFrame;

	DWORD m_dwInstanceID;
	set<DWORD> m_ColSet;

	bool m_bActive;
};

