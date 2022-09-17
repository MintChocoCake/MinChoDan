#pragma once
#include "CAbstractFactory.h"
#include "CLine.h"

class CBoxMgr
{
private:
	CBoxMgr();
	CBoxMgr(const CBoxMgr& _Copy) = delete;
	~CBoxMgr();
public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Render(HDC hDC);
	void		Release(void);
public:
	list<CObj*> GetBoxList() { return BoxList; }
	void SaveBox();
	void LoadBox();
	void SaveTunnel();
	void LoadTunnel();
public:
	static CBoxMgr* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CBoxMgr;

		return m_pInstance;
	}
	static void DestroyInstace()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CBoxMgr* m_pInstance;
	list<CObj*> BoxList;
	bool isEdit = false;
};

