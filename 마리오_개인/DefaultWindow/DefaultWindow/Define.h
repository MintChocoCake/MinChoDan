#pragma once

#define		WINCX		800
#define		WINCY		600
#define		TILEC		35
#define		TILEY		26.2
#define		TILEX		99
#define		PURE		= 0
#define		VK_MAX		0xff
#define     OBJ_DEAD	-1
#define		OBJ_NOEVENT 0
#define		PI			3.141592f
#define		new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define		malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)

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
static const float fOFFSET_X_MIN = 300.f;
static const float fOFFSET_X_MAX = WINCX - fOFFSET_X_MIN;
static const float fOFFSET_Y_MIN = 100.f;
static const float fOFFSET_Y_MAX = WINCY - fOFFSET_Y_MIN;
static const DWORD dwSPLASH_TIME = 1000;

enum OBJ_TYPE {
	OBJ_TYPE_NONE = -1,
	OBJ_TYPE_AFTERIMAGE,
	OBJ_TYPE_MONSTER,
	OBJ_TYPE_PLAYER,
	OBJ_TYPE_BLOCK,
	OBJ_TYPE_HILL,
	OBJ_TYPE_ITEM,
	OBJ_TYPE_EFFECT,
	OBJ_TYPE_BULLET_PLAYER,
	OBJ_TYPE_BULLET_MONSTER,
	OBJ_TYPE_UI,
	OBJ_TYPE_END
};

enum BMP_KEY {
	BMP_KEY_NONE = -1,
	
	// Player 
	BMP_KEY_PLAYER_LEFT,
	BMP_KEY_PLAYER_LEFT_01,
	BMP_KEY_PLAYER_LEFT_02,
	BMP_KEY_PLAYER_LEFT_03,
	BMP_KEY_PLAYER_RIGHT,
	BMP_KEY_PLAYER_RIGHT_01,
	BMP_KEY_PLAYER_RIGHT_02,
	BMP_KEY_PLAYER_RIGHT_03,

	// UI
	BMP_KEY_GROUND,
	BMP_KEY_BACK,
	BMP_KEY_LOGO,
	BMP_KEY_CURSOR,
	BMP_KEY_LOBBYBG,
	BMP_KEY_START_BTN,
	BMP_KEY_EDIT_BTN,
	BMP_KEY_EXIT_BTN,

	// Monster
	BMP_KEY_MONSTER_MUSHROOM,
	BMP_KEY_MONSTER_GUNNER,
	BMP_KEY_MONSTER_TUTLE, 
	BMP_KEY_MONSTER_MOCOCO,
	BMP_KEY_MONSTER_TUNNEL,

	BMP_KEY_BOSS_CENTER_HEAD,
	BMP_KEY_BOSS_CENTER_HEAD_DIE,
	BMP_KEY_BOSS_CENTER_HEAD_ATTACK_01,
	BMP_KEY_BOSS_LEFT_HEAD,
	BMP_KEY_BOSS_LEFT_HEAD_DIE,
	BMP_KEY_BOSS_LEFT_HEAD_ATTACK_01,
	BMP_KEY_BOSS_RIGHT_HEAD,
	BMP_KEY_BOSS_RIGHT_HEAD_DIE,
	BMP_KEY_BOSS_RIGHT_HEAD_ATTACK_01,
	BMP_KEY_BOSS_RIGHT_HEAD_EFFECT_01,
	BMP_KEY_BOSS_RIGHT_BODY,
	BMP_KEY_BOSS_RIGHT_BODY_DIE,
	BMP_KEY_BOSS_LEFT_BODY,
	BMP_KEY_BOSS_LEFT_BODY_DIE,
	BMP_KEY_BOSS_BOTTOM_BODY,
	BMP_KEY_BOSS_BOTTOM_BODY_DIE,
	BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_01,
	BMP_KEY_BOSS_BOTTOM_BODY_ATTACK_02,
	BMP_KEY_BOSS_WING,
	BMP_KEY_BOSS_WING_DIE,
	BMP_KEY_BOSS_TAIL,
	BMP_KEY_BOSS_TAIL_DIE,

	BMP_KEY_FIREMOB,
	BMP_KEY_BOMBMOB,
	
	BMP_KEY_BLOCK_TILE,
	BMP_KEY_BLOCK_BOX,
	BMP_KEY_BLOCK_ITEM_BOX,
	BMP_KEY_BLOCK_INVISIBLE,
	BMP_KEY_BLOCK_ROTATE_FIRE,
	BMP_KEY_BLOCK_ID_TUNNEL_IN,
	BMP_KEY_BLOCK_ID_TUNNEL_OUT,
	BMP_KEY_BLOCK_ID_GOLDE_TILE,

	// Item
	BMP_KEY_ITEM_COIN,
	BMP_KEY_ITEM_GUN,

	BMP_KEY_BULLET,
	BMP_KEY_BULLET_SECOND_LEFT,
	BMP_KEY_BULLET_SECOND_RIGHT,
	BMP_KEY_BULLET_THIRD_LEFT,
	BMP_KEY_BULLET_THIRD_RIGHT,

	//Effect
	BMP_KEY_BULLET_EFFECT_LEFT,
	BMP_KEY_BULLET_EFFECT_RIGHT,
	BMP_KEY_DOUBLE_JUMP_LEFT,
	BMP_KEY_DOUBLE_JUMP_RIGHT,
	BMP_KEY_DAMAGE,
	BMP_KEY_MONSTER_DAMAGE,

	BMP_KEY_END
};

enum BLOCK_ID {
	BLOCK_ID_NONE = -1,
	BLOCK_ID_TILE, 
	BLOCK_ID_BOX,
	BLOCK_ID_ITEM_BOX,   
	BLOCK_ID_INVISIBLE,
	BLOCK_ID_ROTATE_FIRE,
	BLOCK_ID_TUNNEL_IN,
	BLOCK_ID_TUNNEL_OUT,
	BLOCK_ID_TUNNEL_MOB,
	BLOCK_ID_GOLDE_TILE,
	BLOCK_ID_END
};

enum ITEM_ID {
	ITEM_ID_NONE = -1,
	ITEM_ID_COIN,
	ITEM_ID_GUN,
	ITEM_ID_END
};

typedef struct tagBlock {
	DWORD dwHP;
	BMP_KEY eBmp;
	ITEM_ID eDropItem;
	float m_fCX;
	float m_fCY;

	tagBlock(int _dwHP, BMP_KEY _eKey, ITEM_ID _eDrop, float _fCX = TILEC, float _fCY = TILEC) {
		dwHP = (DWORD)_dwHP;
		eBmp = _eKey;
		eDropItem = _eDrop;
		m_fCX = _fCX;
		m_fCY = _fCY;
	}

} BLOCK;

static const tagBlock arrBlockTable[BLOCK_ID_END] = {
	{ -1, BMP_KEY_BLOCK_TILE, ITEM_ID_NONE },
	{ -1, BMP_KEY_BLOCK_BOX, ITEM_ID_NONE },
	{ 1, BMP_KEY_BLOCK_ITEM_BOX, ITEM_ID_GUN },
	{ 5, BMP_KEY_BLOCK_INVISIBLE, ITEM_ID_COIN },
	{ -1, BMP_KEY_BLOCK_ROTATE_FIRE, ITEM_ID_NONE },
	{ -1, BMP_KEY_BLOCK_ID_TUNNEL_IN, ITEM_ID_NONE, 70.f, 105.f },
	{ -1, BMP_KEY_BLOCK_ID_TUNNEL_OUT, ITEM_ID_NONE, 105.f, 70.f},
	{ -1, BMP_KEY_BLOCK_ID_TUNNEL_IN, ITEM_ID_NONE, 70.f, 105.f },
	{ 10, BMP_KEY_BLOCK_ID_GOLDE_TILE, ITEM_ID_COIN }
};

static const BMP_KEY arrItemBmpTable[ITEM_ID_END] = {
	BMP_KEY_ITEM_COIN,
	BMP_KEY_ITEM_GUN
};

enum MONSTER_ID {
	MONSTER_ID_NONE = -1,
	MONSTER_ID_MUSHROOM,
	MONSTER_ID_GUNNER,
	MONSTER_ID_TUTLE,  
	MONSTER_ID_MOCOCO,
	MONSTER_ID_TUNNEL,
	MONSTER_ID_BOSS,
	MONSTER_ID_BOSS_HEAD_LEFT,
	MONSTER_ID_BOSS_HEAD_RIGHT,
	MONSTER_ID_BOSS_BODY_RIGHT,
	MONSTER_ID_BOSS_BODY_LEFT,
	MONSTER_ID_BOSS_BODY_BOTTOM,
	MONSTER_ID_BOSS_WING,
	MONSTER_ID_BOSS_TAIL,
	MONSTER_ID_BOMB,
	MONSTER_ID_FIRE,
	MONSTER_ID_END
};

typedef struct tagMonster {
	DWORD dwHP;
	DWORD dwStr;
	BMP_KEY eBmp;
	ITEM_ID eDropItem;
	float m_fCX;
	float m_fCY;

	tagMonster(int _dwHP, int _dwStr, BMP_KEY _eBmp, ITEM_ID _eDrop, float _fCX = 53.f, float _fCY = 70.f) {
		dwHP = (DWORD)_dwHP;
		dwStr = (DWORD)_dwStr;
		eBmp = _eBmp;
		eDropItem = _eDrop;
		m_fCX = _fCX;
		m_fCY = _fCY;
	}
} MOB;

static const DWORD dwMONSTER_BULLET_STR = 1000;
static const DWORD dwPLAYER_HP = 500000;
static const DWORD dwPLAYER_STR = 3000;
static const tagMonster arrMobTable[MONSTER_ID_END] = {
	{ 10000,10000, BMP_KEY_MONSTER_MUSHROOM, ITEM_ID_COIN },
	{ 10000,10000, BMP_KEY_MONSTER_GUNNER, ITEM_ID_COIN },
	{ 10000,10000, BMP_KEY_MONSTER_TUTLE, ITEM_ID_COIN },
	{ 10000,10000, BMP_KEY_MONSTER_MOCOCO, ITEM_ID_COIN },
	{ -1,10000, BMP_KEY_MONSTER_TUNNEL, ITEM_ID_NONE },
	{ 50000,10000, BMP_KEY_BOSS_CENTER_HEAD, ITEM_ID_NONE, 161.f, 332.f},
	{ 50000,10000, BMP_KEY_BOSS_RIGHT_HEAD, ITEM_ID_NONE, 261.f, 209.f},
	{ 50000,10000, BMP_KEY_BOSS_RIGHT_BODY, ITEM_ID_NONE, 215.f, 144.f},
	{ 50000,10000, BMP_KEY_BOSS_LEFT_HEAD, ITEM_ID_NONE, 261.f, 209.f},
	{ 50000,10000, BMP_KEY_BOSS_LEFT_BODY, ITEM_ID_NONE, 215.f, 144.f},
	{ 50000,10000, BMP_KEY_BOSS_BOTTOM_BODY, ITEM_ID_NONE, 514.f, 192.f},
	{ 50000,10000, BMP_KEY_BOSS_WING, ITEM_ID_NONE, 590.f, 296.f},
	{ 50000,10000, BMP_KEY_BOSS_TAIL, ITEM_ID_NONE, 406.f, 146.f },
	{ 10000, 10000, BMP_KEY_BOMBMOB, ITEM_ID_COIN, 53.f, 53.f },
	{ 10000, 10000, BMP_KEY_FIREMOB, ITEM_ID_COIN, 53.f, 60.f }
};

enum DIRECTION {
	DIRECTION_NONE = -1,
	DIRECTION_LEFT,
	DIRECTION_TOP,
	DIRECTION_RIGHT,
	DIRECTION_BOTTOM,
	DIRECTION_END
};

static const TCHAR* STAGE_MAP_FILE[3] = {
	_T("../Data/Map1.dat"),
	_T("../Data/Map2.dat"),
	_T("../Data/Map3.dat")
};