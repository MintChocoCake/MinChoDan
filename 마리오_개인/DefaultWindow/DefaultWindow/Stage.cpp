#include "stdafx.h"
#include "Stage.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "MapMgr.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"

CStage::CStage() : m_dwScore(0), m_iStage(0)
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	Stage_Up();
}

void CStage::Update(void)
{
	CMapMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CStage::LateUpdate(void)
{
	CObjMgr::Get_Instance()->LateUpdate();

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BLOCK)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_ITEM)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_MONSTER)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BLOCK),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_MONSTER)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BLOCK),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_PLAYER)
	);
	
	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BLOCK)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_PLAYER)
	);

	CCollisionMgr::Collision_Line(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_HILL),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER),
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER)
	);
}

void CStage::Render(HDC hDC)
{
	HDC hBack = CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BACK)->Get_BmpDC();
	HDC hGround = CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_GROUND)->Get_BmpDC();

	BitBlt(hBack, (int)CScrollMgr::Get_Instance()->Get_X(), (int)CScrollMgr::Get_Instance()->Get_Y(), TILEC * TILEX, TILEC * TILEY, hGround, 0, 0, SRCCOPY);

	CMapMgr::Get_Instance()->Render(hBack);
	CObjMgr::Get_Instance()->Render(hBack);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);

	TCHAR szBuffer[50];
	wsprintf(szBuffer, L"SCORE: %d", m_dwScore);
	TextOut(hDC, 0, 0, szBuffer, wcslen(szBuffer));

	wsprintf(szBuffer, L"HP: %d / %d", CObjMgr::Get_Instance()->Get_Player()->Get_HP(), dwPLAYER_HP);
	TextOut(hDC, 0, 20, szBuffer, wcslen(szBuffer));
}

void CStage::Release(void)
{
	CObjMgr::Get_Instance()->Release();
}

void CStage::Stage_Up(void)
{
	int iPlrBullet = 0;
	if (m_iStage != 0) {
		iPlrBullet = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Bullet();
	}

	if(m_iStage == 3)
		CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::SCENE_ID_LOBBY);
	else {
		CMapMgr::Get_Instance()->Load_Map(STAGE_MAP_FILE[m_iStage]);
		CScrollMgr::Get_Instance()->Initialize();
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_PLAYER)->push_back(
			CAbstractFactory::Create<CPlayer>()
		);

		if(iPlrBullet != 0)
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Bullet(iPlrBullet);
		++m_iStage;
	}
}
