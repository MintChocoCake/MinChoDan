#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
// �浹ó���� Objlist �� �־ �Ѳ����� �ϴ� CollisionMgr ����

CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

// �� Ÿ��

void CObjMgr::Add_Object(OBJID _eID, CObj * _pObj)
{
	// ObjList �� ���� ���ų� ���� ����� �ʱ�ȭ�� �ȵǾ��ų� 
	if (OBJ_END <= _eID || nullptr == _pObj)
		return;
	
	m_ObjList[_eID].push_back(_pObj);
}

int CObjMgr::Update(void)
{
	int		iEvent = 0;

	for (size_t i = 0; i < OBJ_END; i++)
	{
		// �� �̷� ���°� ?
		auto&	iter = m_ObjList[i].begin();

		for (; iter != m_ObjList[i].end(); )
		{
			iEvent = (*iter)->Update();
			// �̺�Ʈ�� ������
			if (OBJ_DEAD == iEvent)
			{
				// �ش� Objlist �� ��Ҹ� ����
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
	// ��� Obj ����Ʈ�� 
	for (size_t i = 0; i < OBJ_END; i++)
	{
		// Obj ����Ʈ�� ��� ��Ҹ�
		for (auto& iter : m_ObjList[i]) {
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;
		}
	
	}
	// �ݸ��� �Ŵ��� - �浹ó��
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
	// ����ź 

	if (m_ObjList[_eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[_eID])
	{
		// continue : ����Ÿ�� ���� , break : ��������
		if (iter->Get_Dead())
			continue;

		float	fWidth = fabs(_pDest->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = fabs(_pDest->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		// ���� Ÿ���� ã�� ���� Ÿ���� ���� || ������ �浹 �������� Ŭ�� ?
		if (!pTarget || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
	return pTarget;
}
*/