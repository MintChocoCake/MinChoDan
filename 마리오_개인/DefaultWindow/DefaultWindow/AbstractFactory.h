#pragma once
#include "Obj.h"

class CAbstractFactory
{
public:
	CAbstractFactory()
	{
	}

	~CAbstractFactory()
	{
	}

public:
	template <typename T>
	static CObj* Create(float _fX = 0.f, float _fY = 0.f) {
		CObj* pNew = new T;
		pNew->Initialize();

		if (_fX != 0.f || _fY != 0.f)
			pNew->Set_Pos(_fX, _fY);

		return pNew;
	}

};

