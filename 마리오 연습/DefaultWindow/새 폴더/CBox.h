#pragma once
#include "Obj.h"
#include "Define.h"
class CMonster;

class CBox : public CObj
{
public:
	CBox();
	CBox(BOX _tInfo);
	virtual ~CBox();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	void SetType(BOXTYPE _Type) { m_tBoxInfo.eType = _Type; }
	BOXTYPE GetType() { return m_tBoxInfo.eType; }
	void	SetBoxInfo(float _fX, float _fY, float _fCX, float _fCY, BOXTYPE _Type)
	{
		m_tBoxInfo.fX = _fX;
		m_tBoxInfo.fY = _fY;
		m_tBoxInfo.fCX = _fCX;
		m_tBoxInfo.fCY = _fCY;
		m_tBoxInfo.eType = _Type;
	}
	BOX		GetBoxInfo() { return m_tBoxInfo; }
protected:
	BOX m_tBoxInfo;
};
