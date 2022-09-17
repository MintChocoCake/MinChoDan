#pragma once

#include "Obj.h"
// Obj �Ŵ����ϱ� �翬�� Obj �� �˾ƾ� ���ݾ� ?

class CObjMgr
{
public:
	CObjMgr();
	CObjMgr(const CObjMgr& _rhs) = delete;
	~CObjMgr();

public:
	// Obj �Ŵ����� Obj �� ���°� �����
	void				Add_Object(OBJID _eID, CObj* _pObj);
	int					Update(void);
	void				Late_Update(void);
	void				Render(HDC hDC);
	void				Release(void);
	void				Delete_ID(OBJID _eID);

private:
	// Obj list �� �Ŵ����� ����
	list<CObj*>			m_ObjList[OBJ_END];

public:
	// Obj list �� ���õ� ��ɵ� Obj �Ŵ������� ����
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

