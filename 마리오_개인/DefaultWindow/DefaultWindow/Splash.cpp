#include "stdafx.h"
#include "Splash.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CSplash::CSplash()
{
}


CSplash::~CSplash()
{
}

void CSplash::Initialize(void)
{
}

void CSplash::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::SCENE_ID_LOBBY);
}

void CSplash::LateUpdate(void)
{
}

void CSplash::Render(HDC hDC)
{
	HDC hBack = CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_LOGO)->Get_BmpDC();
	GdiTransparentBlt(hDC, (int)(WINCX * 0.25f), (int)(WINCY * 0.3f), 256, 224, hBack, 0, 0, 256, 224, RGB(248, 7, 220));
}

void CSplash::Release(void)
{
}
