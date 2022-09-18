#pragma once
#include "Monster.h"

class CBoss : public CMonster
{
protected:
	enum BOSS_STATE {
		BOSS_STATE_NONE = -1,
		BOSS_STATE_IDLE,
		BOSS_STATE_ATTACK_01,
		BOSS_STATE_ATTACK_02,
		BOSS_STATE_SKILL,
	};
public:
	CBoss();
	virtual ~CBoss();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;
	virtual FRAME SetFrame(int _iState);
	virtual void SetIdle() { if (m_tFrame.dwStart == m_tFrame.dwEnd) { Change_State(BOSS_STATE_IDLE); } };
public:
	bool	Get_Cast() { return m_bCast; }
	void	Cast_On() { m_bCast = true; }
	void	Cast_Off() { m_bCast = false; }
protected:
	virtual void Set_Bmp(float _fCX, float _fCY, int _iState, BMP_KEY _eBmp);

private:
	void CreateChild();
	void Attack();
protected:
	POINT m_BasePos;
	bool	m_bCast;

	float m_Delay;

};

