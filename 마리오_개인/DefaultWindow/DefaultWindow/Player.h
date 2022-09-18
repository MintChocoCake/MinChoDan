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

	enum PLAYER_BULLET {
		PLAYER_BULLET_NONE,
		PLAYER_BULLET_FIRST,
		PLAYER_BULLET_SECOND,
		PLAYER_BULLET_THIRD,
		PLAYER_BULLET_END
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
	int Get_Bullet() { return m_eGunUpgrade; }
	void Set_Bullet(int _iBullet) { m_eGunUpgrade = (PLAYER_BULLET)_iBullet; }

private:
	bool m_bGoTunnel;
	bool m_bOutTunnel;
	POINT TunnelDest;
	DWORD m_dwJumping;
	float m_fCurJumpDir;
	float m_fAirTime;
	list<CObj*>* m_pBullets;
	DIRECTION m_eCurDir;
	PLAYER_BULLET m_eGunUpgrade;

	float m_AfterImgDelay = 4.f;

private:
	void Key_Input(void);
	void Jump();
	void Scroll();
	void StopJump();
	void ChangeDir(DIRECTION _eDir);
	void InTunnel();
	void OutTunnel();
	void Shot();
	void ShowAfterImage();
	void MakeDamageFont(DWORD _dwDamage);
	MONSTER_ID m_Monter_ID;
};

