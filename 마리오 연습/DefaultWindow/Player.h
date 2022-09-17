#pragma once
#include "Obj.h"

#include "LineMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BitmapMgr.h"

class CPlayer : public CObj
{
	// enum STATE { IDLE, WALK, ATTACK, HIT, DEAD, STATE_END };

	enum STATE { LEFTIDLE, LEFTWALK, RIGHTIDLE, RIGHTWALK, STATE_END
	};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

private:
	void				Key_Input(void);
	void				Jump(void);
	void				OffSet(void);

	void				State_Change(void);

private:
	POINT				m_tBarrel;
	float				m_fDistance;
	float				m_fPI;

	// Y = 힘의크기 * 밑변 * 시간 - (1 / 2) 중력가속 * 시간(제곱2)
	// Y = v0 * sin(@) * t - (1 / 2)gt^2

	bool				m_bJump;	// 점프 상태 확인
	float				m_fPower;	// 점프 힘의 크기
	float				m_fTime;	// 시간값

	// 씬 관련
	STATE				m_ePreState;
	STATE				m_eCurState;

};

