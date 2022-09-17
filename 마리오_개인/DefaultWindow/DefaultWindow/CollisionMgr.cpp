#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*>* _pLeftList, list<CObj*>* _pRightList)
{
	for(auto left : *_pLeftList) {
		for (auto right : *_pRightList) {
			if (!left->Get_Active() || !right->Get_Active())
				continue;

			if (Check_Rect(left, right)) {
				left->OnCollision(right);
				right->OnCollision(left);

				if (left->Col_Before(right->Get_InstanceID()) == false) {
					left->OnCollisionEnter(right);
					right->OnCollisionEnter(left);

					left->Add_Col(right->Get_InstanceID());
					right->Add_Col(left->Get_InstanceID());
				}
			}
			else {
				if (left->Col_Before(right->Get_InstanceID())) {
					left->Delete_Col(right->Get_InstanceID());
					right->Delete_Col(left->Get_InstanceID());
				}
			}

			if (_pRightList->empty())
				return;
		}
	}
}

void CCollisionMgr::Collision_Line(list<CObj*>* _pHillList, list<CObj*>* _pRightList)
{
	for (auto left : *_pHillList) {
		for (auto right : *_pRightList) {
			if (Check_Line(dynamic_cast<CHill*>(left), right)) {
				left->OnCollision(right);
				right->OnCollision(left);
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj * _pLeft, CObj * _pRight)
{
	float fDistance = abs(_pLeft->Get_Info().fX - _pRight->Get_Info().fX);
	float fRadiusSum = (_pLeft->Get_Info().fCX + _pRight->Get_Info().fCX) * 0.5f;

	if (fDistance > fRadiusSum)
		return false;

	fDistance = abs(_pLeft->Get_Info().fY - _pRight->Get_Info().fY);
	fRadiusSum = (_pLeft->Get_Info().fCY + _pRight->Get_Info().fCY) * 0.5f;

	if (fDistance > fRadiusSum)
		return false;

	return true;
}

bool CCollisionMgr::Check_Line(CHill * _pLeft, CObj * _pRight)
{
	INFO& tTargetPos = _pRight->Get_Info();
	LINE tLinePos = _pLeft->Get_LineInfo();
	float fGoalY;

	if (tLinePos.tLeft.fX <= tTargetPos.fX && tLinePos.tRight.fX >= tTargetPos.fX) {
		fGoalY = _pLeft->Get_Y(tTargetPos.fX);

		if (fGoalY - fCOLLISION_RANGE <= tTargetPos.fY && fGoalY + fCOLLISION_RANGE >= tTargetPos.fY) {
				return true;
		}
	}

	return false;
}
