#pragma once

#define		WINCX		800
#define		WINCY		600
#define		TILEC		35
#define		TILEX		130
#define		TILEY		20
#define		PURE		= 0
#define		VK_MAX		0xff
#define     OBJ_DEAD	-1
#define		OBJ_NOEVENT 0
#define		PI			3.141592f

typedef struct tagInfo
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;

}INFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagPoint {
	float fX;
	float fY;

	tagPoint(float _fX, float _fY) {
		fX = _fX;
		fY = _fY;
	}

	tagPoint() {}

} MYPOINT;

typedef struct tagLineInfo {
	MYPOINT tLeft;
	MYPOINT tRight;

} LINE;

typedef struct tagFrame {
	DWORD dwStart;
	DWORD dwEnd;
	DWORD dwMotion;
	DWORD dwSpeed;
	DWORD dwTimer;

} FRAME;

extern HWND		g_hWnd;

static const float fCOLLISION_RANGE = 35.f;
static const float fOFFSET_X_MIN = 400.f;
static const float fOFFSET_X_MAX = WINCX - fOFFSET_X_MIN;
static const float fOFFSET_Y_MIN = 100.f;
static const float fOFFSET_Y_MAX = WINCY - fOFFSET_Y_MIN;
static const DWORD dwSPLASH_TIME = 1000;

enum OBJ_TYPE {
	OBJ_TYPE_NONE = -1,
	OBJ_TYPE_PLAYER,
	OBJ_TYPE_MONSTER,
	OBJ_TYPE_BLOCK,
	OBJ_TYPE_HILL,
	OBJ_TYPE_BULLET_PLAYER,
	OBJ_TYPE_BULLET_MONSTER,
	OBJ_TYPE_ITEM,
	OBJ_TYPE_UI,
	OBJ_TYPE_END
};

enum BMP_KEY {
	BMP_KEY_NONE = -1,
	BMP_KEY_PLAYER_LEFT,
	BMP_KEY_PLAYER_RIGHT,

	BMP_KEY_GROUND,
	BMP_KEY_BACK,
	BMP_KEY_LOGO,

	BMP_KEY_MONSTER_MUSHROOM,
	BMP_KEY_MONSTER_GUNNER,

	BMP_KEY_BLOCK_TILE,
	BMP_KEY_BLOCK_BOX,
	BMP_KEY_BLOCK_ITEM_BOX,
	BMP_KEY_BLOCK_INVISIBLE,
	BMP_KEY_BLOCK_ROTATE_FIRE,
	BMP_KEY_BLOCK_ID_TUNNEL_IN,
	BMP_KEY_BLOCK_ID_TUNNEL_OUT,

	BMP_KEY_ITEM_COIN,
	BMP_KEY_ITEM_GUN,

	BMP_KEY_CURSOR,
	BMP_KEY_LOBBYBG,
	BMP_KEY_START_BTN,
	BMP_KEY_EDIT_BTN,
	BMP_KEY_EXIT_BTN,
	BMP_KEY_BULLET,
	BMP_KEY_END
};

enum BLOCK_ID {
	BLOCK_ID_NONE = -1,
	BLOCK_ID_TILE, // 파괴 불가
	BLOCK_ID_BOX,
	BLOCK_ID_ITEM_BOX,   
	BLOCK_ID_INVISIBLE,
	BLOCK_ID_ROTATE_FIRE,
	BLOCK_ID_TUNNEL_IN,
	BLOCK_ID_TUNNEL_OUT,
	BLOCK_ID_TUNNEL_MOB,
	BLOCK_ID_END
};

enum ITEM_ID {
	ITEM_ID_NONE = -1,
	ITEM_ID_COIN,
	ITEM_ID_GUN,
	ITEM_ID_END
};

typedef struct tagBlock {
	// -1이면 파괴 불가 블록
	DWORD dwHP;
	BMP_KEY eBmp;
	ITEM_ID eDropItem;
} BLOCK;

static const tagBlock arrBlockTable[BLOCK_ID_END] = {
	{ (DWORD)-1, BMP_KEY_BLOCK_TILE, ITEM_ID_NONE },
	{ (DWORD)-1, BMP_KEY_BLOCK_BOX, ITEM_ID_NONE },
	{ (DWORD)1, BMP_KEY_BLOCK_ITEM_BOX, ITEM_ID_GUN },
	{ (DWORD)5, BMP_KEY_BLOCK_INVISIBLE, ITEM_ID_COIN },
	{ (DWORD)-1, BMP_KEY_BLOCK_ROTATE_FIRE, ITEM_ID_NONE },
	{ (DWORD)-1, BMP_KEY_BLOCK_ID_TUNNEL_IN, ITEM_ID_NONE },
	{ (DWORD)-1, BMP_KEY_BLOCK_ID_TUNNEL_OUT, ITEM_ID_NONE },
	{ (DWORD)-1, BMP_KEY_BLOCK_ID_TUNNEL_IN, ITEM_ID_NONE }
};

static const BMP_KEY arrItemBmpTable[ITEM_ID_END] = {
	BMP_KEY_ITEM_COIN,
	BMP_KEY_ITEM_GUN
};

enum MONSTER_ID {
	MONSTER_ID_NONE = -1,
	MONSTER_ID_MUSHROOM,
	MONSTER_ID_GUNNER,
	MONSTER_ID_END
};

typedef struct tagMonster {
	// -1이면 파괴 불가 블록
	DWORD dwHP;
	BMP_KEY eBmp;
	ITEM_ID eDropItem;
} MOB;

static const tagMonster arrMobTable[MONSTER_ID_END] = {
	{ (DWORD)1, BMP_KEY_MONSTER_MUSHROOM, ITEM_ID_NONE },
	{ (DWORD)3, BMP_KEY_MONSTER_GUNNER, ITEM_ID_COIN },
};

enum DIRECTION {
	DIRECTION_NONE = -1,
	DIRECTION_LEFT,
	DIRECTION_TOP,
	DIRECTION_RIGHT,
	DIRECTION_BOTTOM,
	DIRECTION_END
};