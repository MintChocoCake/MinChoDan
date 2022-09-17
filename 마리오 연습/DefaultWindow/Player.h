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

	// Y = ����ũ�� * �غ� * �ð� - (1 / 2) �߷°��� * �ð�(����2)
	// Y = v0 * sin(@) * t - (1 / 2)gt^2

	bool				m_bJump;	// ���� ���� Ȯ��
	float				m_fPower;	// ���� ���� ũ��
	float				m_fTime;	// �ð���

	// �� ����
	STATE				m_ePreState;
	STATE				m_eCurState;

};

