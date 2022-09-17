#pragma once
#include "Obj.h"
#include "Hill.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void Collision_Rect(list<CObj*>* _pLeftList, list<CObj*>* _pRightList);
	static void Collision_Line(list<CObj*>* _pHillList, list<CObj*>* _pRightList);

private:
	static bool Check_Rect(CObj* _pLeft, CObj* _pRight);
	static bool Check_Line(CHill* _pLeft, CObj* _pRight);
};

