#pragma once
#include "Obj.h"
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	enum PLAYER_STATE {
		PLAYER_STATE_NONE = -1,
		PLAYER_STATE_IDLE,
		PLAYER_STATE_WALK,
		PLAYER_STATE_LINE,
		PLAYER_STATE_JUMP,
		PLAYER_STATE_UP,
		PLAYER_STATE_END
	};

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	//virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;
	virtual FRAME SetFrame(int _iState);

private:
	bool m_bJumping;
	bool m_bGun;
	float m_fCurJumpDir;
	float m_fAirTime;
	list<CObj*>* m_pBullets;
	DIRECTION m_eCurDir;

private:
	void Key_Input(void);
	void Jump();
	void Scroll();
	void StopJump();
	void ChangeDir(DIRECTION _eDir);
};

