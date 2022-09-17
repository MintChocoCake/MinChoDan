#pragma once
#include "Obj.h"
#include "Define.h"

class CObjMgr
{
#pragma region Singleton
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr* Get_Instance() {
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static void	Delete_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr* m_pInstance;
#pragma endregion

public:
	list<CObj*>* Get_ObjList(OBJ_TYPE _eType) { return &(m_ObjList[_eType]); }
	CObj* Get_Player() { return m_ObjList[OBJ_TYPE_PLAYER].front(); }

public:
	void Update();
	void LateUpdate();
	void Render(HDC _HDC);
	void Release();
	void Delete_Group(OBJ_TYPE _eType);

private:
	list<CObj*> m_ObjList[OBJ_TYPE_END];
};

