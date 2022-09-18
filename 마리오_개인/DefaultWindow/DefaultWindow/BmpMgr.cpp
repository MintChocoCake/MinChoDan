#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Initialize()
{
	Insert_Bmp(_T("../MyImage/PlayerLeft.bmp"), BMP_KEY_PLAYER_LEFT);
	Insert_Bmp(_T("../MyImage/PlayerLeft_01.bmp"), BMP_KEY_PLAYER_LEFT_01);
	Insert_Bmp(_T("../MyImage/PlayerLeft_02.bmp"), BMP_KEY_PLAYER_LEFT_02);	
	Insert_Bmp(_T("../MyImage/PlayerLeft_03.bmp"), BMP_KEY_PLAYER_LEFT_03);
	Insert_Bmp(_T("../MyImage/PlayerRight.bmp"), BMP_KEY_PLAYER_RIGHT);
	Insert_Bmp(_T("../MyImage/PlayerRight_01.bmp"), BMP_KEY_PLAYER_RIGHT_01);
	Insert_Bmp(_T("../MyImage/PlayerRight_02.bmp"), BMP_KEY_PLAYER_RIGHT_02);
	Insert_Bmp(_T("../MyImage/PlayerRight_03.bmp"), BMP_KEY_PLAYER_RIGHT_03);
	Insert_Bmp(_T("../MyImage/Ground.bmp"), BMP_KEY_GROUND);
	Insert_Bmp(_T("../Image/Back.bmp"), BMP_KEY_BACK);
	Insert_Bmp(_T("../Image/Logo/Logo.bmp"), BMP_KEY_LOGO);

	Insert_Bmp(_T("../MyImage/Tile.bmp"), BMP_KEY_BLOCK_TILE);
	Insert_Bmp(_T("../MyImage/Box.bmp"), BMP_KEY_BLOCK_BOX);
	Insert_Bmp(_T("../MyImage/ItemBox.bmp"), BMP_KEY_BLOCK_ITEM_BOX);
	Insert_Bmp(_T("../MyImage/Invisible.bmp"), BMP_KEY_BLOCK_INVISIBLE);
	Insert_Bmp(_T("../MyImage/RotateFire.bmp"), BMP_KEY_BLOCK_ROTATE_FIRE);

	Insert_Bmp(_T("../MyImage/Monster.bmp"), BMP_KEY_MONSTER_MUSHROOM);  // ���� �̹����� ��ü 
	Insert_Bmp(_T("../MyImage/Monster.bmp"), BMP_KEY_MONSTER_GUNNER);
	Insert_Bmp(_T("../MyImage/Tutle.bmp"), BMP_KEY_MONSTER_TUTLE); // �ź��� �̹��� �߰�
	Insert_Bmp(_T("../MyImage/CoCoMo2.bmp"), BMP_KEY_MONSTER_MOCOCO);   // ������ �̹��� �߰�
	Insert_Bmp(_T("../MyImage//Monster_00.bmp"), BMP_KEY_MONSTER_TUNNEL);

	Insert_Bmp(_T("../MyImage/Cursor.bmp"), BMP_KEY_CURSOR);
	Insert_Bmp(_T("../MyImage/LobbyBG.bmp"), BMP_KEY_LOBBYBG);
	Insert_Bmp(_T("../MyImage/Start.bmp"), BMP_KEY_START_BTN);
	Insert_Bmp(_T("../MyImage/Edit.bmp"), BMP_KEY_EDIT_BTN);
	Insert_Bmp(_T("../MyImage/Exit.bmp"), BMP_KEY_EXIT_BTN);
	Insert_Bmp(_T("../MyImage/FireBall.bmp"), BMP_KEY_BULLET);

	Insert_Bmp(_T("../MyImage/Coin.bmp"), BMP_KEY_ITEM_COIN);
	Insert_Bmp(_T("../MyImage/Gun.bmp"), BMP_KEY_ITEM_GUN);
	
	
}

void CBmpMgr::Insert_Bmp(const TCHAR * _chFilePath, BMP_KEY _eKey)
{
	auto iter = m_BmpMap.find(_eKey);

	if (iter == m_BmpMap.end()) {
		CMyBitmap* bmp = new CMyBitmap;
		bmp->Load_Bmp(_chFilePath);

		m_BmpMap.insert({_eKey, bmp});
	}
}

CMyBitmap * CBmpMgr::Find_Bmp(BMP_KEY _eKey)
{
	auto iter = m_BmpMap.find(_eKey);

	if (iter == m_BmpMap.end())
		return nullptr;

	return (*iter).second;
}

void CBmpMgr::Release()
{
	for_each(m_BmpMap.begin(), m_BmpMap.end(), [](map<BMP_KEY, CMyBitmap*>::value_type Pair) {
		if (Pair.second) {
			delete Pair.second;
			Pair.second = nullptr;
		}
	});
}
