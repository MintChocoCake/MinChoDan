#pragma once

#include "Define.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {};
	~CAbstractFactory() {};

public:
	static CObj*		Create(void)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)  // BULLETSTATE _eDir = BULLET_END
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(_fX, _fY);

		// ÃÑ¾Ë °ü·Ã _eDir

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY , MONSTERTYPE _etype)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(_fX, _fY);

		pObj->Set_Mos_Type(_etype);

		return pObj;
	}
};

