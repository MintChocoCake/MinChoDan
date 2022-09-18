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
	// Player
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
	Insert_Bmp(_T("../MyImage/Logo.bmp"), BMP_KEY_LOGO);

	// Block
	Insert_Bmp(_T("../MyImage/Tile.bmp"), BMP_KEY_BLOCK_TILE);
	Insert_Bmp(_T("../MyImage/Box.bmp"), BMP_KEY_BLOCK_BOX);
	Insert_Bmp(_T("../MyImage/ItemBox.bmp"), BMP_KEY_BLOCK_ITEM_BOX);
	Insert_Bmp(_T("../MyImage/Invisible.bmp"), BMP_KEY_BLOCK_INVISIBLE);
	Insert_Bmp(_T("../MyImage/RotateFire.bmp"), BMP_KEY_BLOCK_ROTATE_FIRE);
	Insert_Bmp(_T("../MyImage/Tunnel.bmp"), BMP_KEY_BLOCK_ID_TUNNEL_IN);
	Insert_Bmp(_T("../MyImage/Tunnel_Out.bmp"), BMP_KEY_BLOCK_ID_TUNNEL_OUT);
	Insert_Bmp(_T("../MyImage/GoldTile.bmp"), BMP_KEY_BLOCK_ID_GOLDE_TILE);


	// Monster
	Insert_Bmp(_T("../MyImage/GoomBa.bmp"), BMP_KEY_MONSTER_MUSHROOM);
	Insert_Bmp(_T("../MyImage/Monster.bmp"), BMP_KEY_MONSTER_GUNNER);
	Insert_Bmp(_T("../MyImage/Monster_00.bmp"), BMP_KEY_MONSTER_TUNNEL);
	
	Insert_Bmp(_T("../MyImage/Boss/Head/CenterHead/stand.bmp"), BMP_KEY_BOSS_CENTER_HEAD);
	Insert_Bmp(_T("../MyImage/Boss/Head/CenterHead/die.bmp"), BMP_KEY_BOSS_CENTER_HEAD_DIE);
	Insert_Bmp(_T("../MyImage/Boss/Head/CenterHead/attack1.bmp"), BMP_KEY_BOSS_CENTER_HEAD_ATTACK_01);
	Insert_Bmp(_T("../MyImage/Boss/Head/LeftHead/stand.bmp"), BMP_KEY_BOSS_LEFT_HEAD);
	Insert_Bmp(_T("../MyImage/Boss/Head/LeftHead/die.bmp"), BMP_KEY_BOSS_LEFT_HEAD_DIE);
	Insert_Bmp(_T("../MyImage/Boss/Head/LeftHead/attack1.bmp"), BMP_KEY_BOSS_LEFT_HEAD_ATTACK_01);
	Insert_Bmp(_T("../MyImage/Boss/Head/RightHead/stand.bmp"), BMP_KEY_BOSS_RIGHT_HEAD);
	Insert_Bmp(_T("../MyImage/Boss/Head/RightHead/die.bmp"), BMP_KEY_BOSS_RIGHT_HEAD_DIE);
	Insert_Bmp(_T("../MyImage/Boss/Head/RightHead/attack3.bmp"), BMP_KEY_BOSS_RIGHT_HEAD_ATTACK_01);
	Insert_Bmp(_T("../MyImage/Boss/Head/RightHead/attack3_Effect.bmp"), BMP_KEY_BOSS_RIGHT_HEAD_EFFECT_01);
	Insert_Bmp(_T("../MyImage/Boss/Body/RightBody/stand.bmp"), BMP_KEY_BOSS_RIGHT_BODY);
	Insert_Bmp(_T("../MyImage/Boss/Body/RightBody/die.bmp"), BMP_KEY_BOSS_RIGHT_BODY_DIE);
	Insert_Bmp(_T("../MyImage/Boss/Body/LeftBody/stand.bmp"), BMP_KEY_BOSS_LEFT_BODY);
	Insert_Bmp(_T("../MyImage/Boss/Body/LeftBody/die.bmp"), BMP_KEY_BOSS_LEFT_BODY_DIE);
	Insert_Bmp(_T("../MyImage/Boss/Body/DownBody/stand.bmp"), BMP_KEY_BOSS_BOTTOM_BODY);
	Insert_Bmp(_T("../MyImage/Boss/Body/DownBody/die.bmp"), BMP_KEY_BOSS_BOTTOM_BODY_DIE);
	Insert_Bmp(_T("../MyImage/Boss/Body/DownBody/attack2.bmp"), BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_01);
	Insert_Bmp(_T("../MyImage/Boss/Body/DownBody/attack4.bmp"), BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_02);
	Insert_Bmp(_T("../MyImage/Boss/Wing/stand.bmp"), BMP_KEY_BOSS_WING);
	Insert_Bmp(_T("../MyImage/Boss/Wing/die.bmp"), BMP_KEY_BOSS_WING_DIE);
	Insert_Bmp(_T("../MyImage/Boss/Tail/stand.bmp"), BMP_KEY_BOSS_TAIL);
	Insert_Bmp(_T("../MyImage/Boss/Tail/die.bmp"), BMP_KEY_BOSS_TAIL_DIE);

	Insert_Bmp(_T("../MyImage/Tutle.bmp"), BMP_KEY_MONSTER_TUTLE); 
	Insert_Bmp(_T("../MyImage/CoCoMo2.bmp"), BMP_KEY_MONSTER_MOCOCO); 
	Insert_Bmp(_T("../MyImage/Monster_00.bmp"), BMP_KEY_MONSTER_TUNNEL);
	Insert_Bmp(_T("../MyImage/FireMob.bmp"), BMP_KEY_FIREMOB);
	Insert_Bmp(_T("../MyImage/BombMob.bmp"), BMP_KEY_BOMBMOB);

	// UI
	Insert_Bmp(_T("../MyImage/Cursor.bmp"), BMP_KEY_CURSOR);
	Insert_Bmp(_T("../MyImage/LobbyBG.bmp"), BMP_KEY_LOBBYBG);
	Insert_Bmp(_T("../MyImage/Start.bmp"), BMP_KEY_START_BTN);
	Insert_Bmp(_T("../MyImage/Edit.bmp"), BMP_KEY_EDIT_BTN);
	Insert_Bmp(_T("../MyImage/Exit.bmp"), BMP_KEY_EXIT_BTN);
	Insert_Bmp(_T("../MyImage/Ground.bmp"), BMP_KEY_GROUND);
	Insert_Bmp(_T("../Image/Back.bmp"), BMP_KEY_BACK);
	Insert_Bmp(_T("../Image/Logo/Logo.bmp"), BMP_KEY_LOGO);

	// Item
	Insert_Bmp(_T("../MyImage/Coin.bmp"), BMP_KEY_ITEM_COIN);
	Insert_Bmp(_T("../MyImage/Gun.bmp"), BMP_KEY_ITEM_GUN);

	// Bullet
	Insert_Bmp(_T("../MyImage/FireBall.bmp"), BMP_KEY_BULLET);
	Insert_Bmp(_T("../MyImage/Bullet_Left.bmp"), BMP_KEY_BULLET_SECOND_LEFT);
	Insert_Bmp(_T("../MyImage/Bullet_Right.bmp"), BMP_KEY_BULLET_SECOND_RIGHT);
	Insert_Bmp(_T("../MyImage/Arrow_left.bmp"), BMP_KEY_BULLET_THIRD_LEFT);
	Insert_Bmp(_T("../MyImage/Arrow_Right.bmp"), BMP_KEY_BULLET_THIRD_RIGHT);

	// Effect
	Insert_Bmp(_T("../MyImage/BulletEffect_Left.bmp"), BMP_KEY_BULLET_EFFECT_LEFT);
	Insert_Bmp(_T("../MyImage/BulletEffect_Right.bmp"), BMP_KEY_BULLET_EFFECT_RIGHT);
	Insert_Bmp(_T("../MyImage/DoubleJump_left.bmp"), BMP_KEY_DOUBLE_JUMP_LEFT);
	Insert_Bmp(_T("../MyImage/DoubleJump_right.bmp"), BMP_KEY_DOUBLE_JUMP_RIGHT);
	Insert_Bmp(_T("../MyImage/Damage.bmp"), BMP_KEY_DAMAGE);
	Insert_Bmp(_T("../MyImage/DamageTemp.bmp"), BMP_KEY_MONSTER_DAMAGE);
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
