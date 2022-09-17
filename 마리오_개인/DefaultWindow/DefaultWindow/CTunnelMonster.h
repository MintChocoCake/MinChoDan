#pragma once
#include "Monster.h"
class CTunnelMonster : public CMonster
{
public:
	CTunnelMonster();
	virtual ~CTunnelMonster();

public:
	virtual void Initialize(void) override;
	virtual void OnCollision(CObj* _pTarget);

protected:
	virtual void Act() override;
	virtual FRAME SetFrame(int _iState) override;
private:
	bool isUP = true;
	float m_DestY = 0.f;
	float m_BaseY = 0.f;
};

