#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

private:
	enum MONSTER_STATE {
		MONSTER_STATE_NONE = -1,
		MONSTER_STATE_WALK,
		MONSTER_STATE_END
	};

public:
	MONSTER_ID Get_MonsterID() { return m_eMobID; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	//virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget) override;
	virtual void OnCollisionEnter(CObj* _pTarget) override;

protected:
	MONSTER_ID m_eMobID;

protected:
	virtual void Act();

private:
	float m_fAirTime;
	MONSTER_STATE m_eCurState;

private:
	void ChangeState(MONSTER_STATE _eState);

};

