#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest,Src))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * _pDest, CObj * _pSrc)
{
	float	fWideth = fabs(_pDest->Get_Info().fX - _pSrc->Get_Info().fX);
	float	fHeight = fabs(_pDest->Get_Info().fY - _pSrc->Get_Info().fY);

	float	fDiagonal = sqrtf(fWideth * fWideth + fHeight * fHeight);

	float	fRadius = (_pDest->Get_Info().fCX + _pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		float	fX = 0.f, fY = 0.f;
		
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dest, Src, &fX, &fY))
			{
				// ���� �浹
				if (fX > fY)
				{
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						Dest->Set_PosY(-fY);
					}
					else
					{
						Dest->Set_PosX(fY);
					}
				}

				// �¿� �浹
				else
				{
					// �� �浹
					if (Dest->Get_Info().fX < Src->Get_Info().fX)
					{
						Dest->Set_PosX(-fX);
					}
					// �� �浹
					else
					{
						Dest->Set_PosX(fX);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj * _pDest, CObj * _pSrc, float * _pX, float * _pY)
{
	float	fWidth = fabs(_pDest->Get_Info().fX - _pSrc->Get_Info().fX);
	float	fHeight = fabs(_pDest->Get_Info().fY - _pSrc->Get_Info().fY);

	// x�� ���� ������ ����
	float	fRadiusX = (_pDest->Get_Info().fCX + _pSrc->Get_Info().fCX) * 0.5f;
	// y�� ���� ������ ����
	float	fRadiusY = (_pDest->Get_Info().fCY + _pSrc->Get_Info().fCY) * 0.5f;
	// x �� �� ������ && y �� �� ������
	if (fRadiusX >= fWidth && fRadiusY>= fHeight)
	{
		// x / y = �� ������ ������ �Ÿ� - ���������� �Ÿ�
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}
