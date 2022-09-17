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

	// �� ���ϴ°� ��� ����
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
	// ���� ����� �ڵ��� �������
	HDC hGroundDC = CBitmapMgr::Get_Instance()->Find_Bmp(L"Ground");

	// ū ����� �׷����� ��ũ�� ���� �ָ� ū��������� �����̴� ȿ��
	int iScroll_X = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScroll_Y = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	// ������ ���������� �� ũ�⸦ �ҷ�����  / �� ���ʿ� �ѰŰ��⵵ ����..


	// BitBlt : iScroll_X , iScroll_Y ���� �޾Ƽ� ������ġ�� �����ϸ� ȭ���� �����̴µ��� ȿ��
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
