#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	fGumX = 100.f;
	fTulX = 50.f;
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	
	for (int i = 0; i < 100; i++)
	{
		Create_Monster(fGumX*i, GOOMBA);
		Create_Monster(fGumX*i+ fTulX, TUTLE);
	}

	CLineMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile();

	// 맵 원하는거 골라 쓰기
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Map/1-1.bmp", L"Ground");
	// CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Map/Map1-1.bmp", L"Ground");
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Map/1-3.bmp", L"Ground");
	//CBitmapMgr::Get_Instance()->Insert_Bmp(L"../IsImage/Map/Map1-1.bmp", L"Ground");
	
}

int CStage::Update(void)
{
	CLineMgr::Get_Instance()->Update();
	//CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStage::Late_Update(void)
{
	CLineMgr::Get_Instance()->Late_Update();
	//CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	// 따로 사용할 핸들을 만들어줌
	HDC hGroundDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Ground");

	// 큰 배경을 그려놓고 스크롤 값을 주면 큰배경위에서 움직이는 효과
	int iScroll_X = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScroll_Y = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	// 저장한 스테이지의 씬 크기를 불러오기  / 좀 불필요 한거같기도 ㅋㅋ..


	// BitBlt : iScroll_X , iScroll_Y 값을 받아서 생성위치로 지정하면 화면이 움직이는듯한 효과
	BitBlt(hDC, iScroll_X, iScroll_Y, STAGE_SCENE_X, STAGE_SCENE_Y2, hGroundDC, 0, 0, SRCCOPY);

	
	CLineMgr::Get_Instance()->Render(hDC);
	//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}

void CStage::Create_Monster(float _fPosx, MONSTERTYPE _eType)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(600.f + _fPosx, 200.f, _eType));
}
