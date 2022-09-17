#pragma once

#include "Obj.h"
// Obj 매니저니깐 당연히 Obj 를 알아야 하잖아 ?

class CObjMgr
{
public:
	CObjMgr();
	CObjMgr(const CObjMgr& _rhs) = delete;
	~CObjMgr();

public:
	// Obj 매니저라 Obj 와 형태가 비슷함
	void				Add_Object(OBJID _eID, CObj* _pObj);
	int					Update(void);
	void				Late_Update(void);
	void				Render(HDC hDC);
	void				Release(void);
	void				Delete_ID(OBJID _eID);

private:
	// Obj list 도 매니저가 관리
	list<CObj*>			m_ObjList[OBJ_END];

public:
	// Obj list 에 관련된 기능도 Obj 매니저에서 관리
	CObj*				Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	//CObj*				Get_Target(OBJID _eID, CObj* _pDest);

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void			Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*		m_pInstance;
};

