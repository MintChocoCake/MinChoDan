#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
// 충돌처리도 Objlist 를 넣어서 한꺼번에 하니 CollisionMgr 포함

CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

// 겟 타겟

void CObjMgr::Add_Object(OBJID _eID, CObj * _pObj)
{
	// ObjList 에 값이 없거나 안의 요소의 초기화가 안되었거나 
	if (OBJ_END <= _eID || nullptr == _pObj)
		return;
	
	m_ObjList[_eID].push_back(_pObj);
}

int CObjMgr::Update(void)
{
	int		iEvent = 0;

	for (size_t i = 0; i < OBJ_END; i++)
	{
		// 왜 이런 형태가 ?
		auto&	iter = m_ObjList[i].begin();

		for (; iter != m_ObjList[i].end(); )
		{
			iEvent = (*iter)->Update();
			// 이벤트가 죽으면
			if (OBJ_DEAD == iEvent)
			{
				// 해당 Objlist 의 요소를 삭제
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return iEvent;
}

void CObjMgr::Late_Update(void)
{
	// 모든 Obj 리스트를 
	for (size_t i = 0; i < OBJ_END; i++)
	{
		// Obj 리스트의 모든 요소를
		for (auto& iter : m_ObjList[i]) {
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;
		}
	
	}
	// 콜리지 매니저 - 충돌처리
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
	
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}
void CObjMgr::Delete_ID(OBJID _eID)
{
	for (auto& iter : m_ObjList[_eID])
		Safe_Delete(iter);

	m_ObjList[_eID].clear();
}
/*
CObj * CObjMgr::Get_Target(OBJID _eID, CObj* _pDest)
{
	// 유도탄 

	if (m_ObjList[_eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[_eID])
	{
		// continue : 다음타깃 따라서 , break : 추적종료
		if (iter->Get_Dead())
			continue;

		float	fWidth = fabs(_pDest->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = fabs(_pDest->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		// 다음 타겟을 찾는 조건 타겟이 죽음 || 빗변이 충돌 지점보다 클때 ?
		if (!pTarget || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
	return pTarget;
}
*/