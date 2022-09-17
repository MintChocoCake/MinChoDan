#pragma once

#define		WINCX			800
#define		WINCY			600
#define		PURE			= 0

#define		VK_MAX			0xff

#define		OBJ_NO_EVENT	0
#define		OBJ_DEAD		1

#define		PI			3.141592f

#define		STAGE_SCENE_X  2800
#define		STAGE_SCENE_Y  800
#define		STAGE_SCENE_Y2  600

#define		TILE_CX			60
#define		TILE_CY			60

#define		TILE_X			30
#define		TILE_Y			20

			
typedef struct tagInfo
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;

}INFO;

template<typename T>
void Safe_Delete(T& _Temp)
{
	if (_Temp)
	{
		delete _Temp;
		_Temp = nullptr;
	}
}

typedef		struct tagLinePoint
{
	// 선을 긋기전 두 선을 이을 점들의 정보를 위한 구조체 MYPOINT
	float	fX;
	float	fY;

	tagLinePoint(void) { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}
}MYPOINT;

typedef		struct tagLine
{
	// MYPOINT 구조체 타입 좌, 우 좌표를 담을 구조체
	MYPOINT		tL_Point;
	MYPOINT		tR_Point;

	// 생성자를 통해 구조체 맴버 초기화, 매게변수를 통해 받은값을 이니셜 라이저로 구조체로 전달
	tagLine(void) { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(MYPOINT& _tLeft, MYPOINT& _tRight) : tL_Point(_tLeft), tR_Point(_tRight) {}
	// 1. 왜 레퍼런스로 값 전달?

}LINE;

class CDeleteObj
{
public:
	template<typename T>
	void	operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pKey): m_pKey(pKey) {}
public:
	template<typename T>
	bool		operator()(T& Pair)
	{
		if (!lstrcmp(m_pKey, Pair.first))
			return true;

		return false;
	}
private:
	const TCHAR*		m_pKey;
};

typedef struct tagFrame
{
	int			iStart;		// 몇 번 인덱스 부터 출력할 것인가
	int			iEnd;		// 몇 번 인덱스 까지 출력할 것인가
	int			iMotion;	// 몇 번 모션을 출력할 것이간
	DWORD		dwSpeed;	// 어떤 속도로 애니메이션을 재생할 것인가
	DWORD		dwTime;		// 시간 값에 따른 애니메이션 재생 속도 재어용
}FRAME;

extern HWND		g_hWnd;

// extern 선언을 하면 스테이지의 크기를 어디서든 알수있다 ? 아니면 static ?  실패 -> 그냥 매크로 ㄱ


// 라인의 방향 이넘 열거체
enum DIRECTION { LEFT, RIGHT, END };

// Obj 리스트를 위한 이넘
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_UI, OBJ_END };

enum MONSTERTYPE { GOOMBA, TUTLE, TYPE_END };