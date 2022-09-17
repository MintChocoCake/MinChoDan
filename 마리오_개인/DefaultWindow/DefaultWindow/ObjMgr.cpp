#include "stdafx.h"
#include "ObjMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	int iResult = 0;

	for (int i = 0; i < OBJ_TYPE_END; ++i) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {
			iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD) {
				iter = m_ObjList[i].erase(iter);
			}
			else {
				++iter;
			}
		}
	}
}

void CObjMgr::LateUpdate()
{
	for (list<CObj*>& list : m_ObjList) {
		for (CObj*& obj : list) {
			obj->LateUpdate();

			if (list.empty())
				break;
		}
	}
}

void CObjMgr::Render(HDC _HDC)
{
	for (list<CObj*>& list : m_ObjList) {
		for (CObj*& obj : list) {
			obj->Render(_HDC);
		}
	}

	TCHAR szBuffer[50];
	wsprintf(szBuffer, L"MOB BULLET COUNT : %d", m_ObjList[OBJ_TYPE_BULLET_MONSTER].size());
	TextOut(_HDC, 0, 100, szBuffer, lstrlen(szBuffer));
}

void CObjMgr::Release()
{
	for (list<CObj*>& list : m_ObjList) {
		for (CObj*& obj : list) {
			Safe_Delete(obj);
		}

		list.clear();
	}
}

void CObjMgr::Delete_Group(OBJ_TYPE _eType)
{
	for (auto& target : m_ObjList[_eType])
		target->Release();

	m_ObjList[_eType].clear();
}
