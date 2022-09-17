#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)	PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release(void)	PURE;

protected:
	void				Update_Rect(void);

public:
	const RECT&			Get_Rect(void) const { return m_tRect; }
	const INFO&			Get_Info(void) const { return m_tInfo; }

	void				Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void				Set_PosX(float _fX) { m_tInfo.fX = _fX; }
	void				Set_PosY(float _fY) { m_tInfo.fY = _fY; }

	void				Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

	void				Set_Dead() { m_bDead = true; }
	bool				Get_Dead() { return m_bDead; }

	// 몬스터 타입
	void				Set_Mos_Type(MONSTERTYPE _eType) { m_eMos_Type = _eType; }

	// 프레임 관련 ( 씬 )
	void				Set_Frame_Key(TCHAR* _pFrame_Key) { m_pFrame_Key = _pFrame_Key; }

protected:
	void				Move_Frame(void);

protected:
	INFO			m_tInfo;
	RECT			m_tRect;

	float			m_fSpeed;
	float			m_fAngle;
	bool			m_bDead;

	CObj*			m_pTarget;
	// 텍스트 출력 관련
	FRAME			m_tFrame;
	TCHAR*			m_pFrame_Key;

	// 몬스터 타입
	MONSTERTYPE		m_eMos_Type;
};

