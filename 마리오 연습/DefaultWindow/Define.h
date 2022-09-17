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
	// ���� �߱��� �� ���� ���� ������ ������ ���� ����ü MYPOINT
	float	fX;
	float	fY;

	tagLinePoint(void) { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}
}MYPOINT;

typedef		struct tagLine
{
	// MYPOINT ����ü Ÿ�� ��, �� ��ǥ�� ���� ����ü
	MYPOINT		tL_Point;
	MYPOINT		tR_Point;

	// �����ڸ� ���� ����ü �ɹ� �ʱ�ȭ, �ŰԺ����� ���� �������� �̴ϼ� �������� ����ü�� ����
	tagLine(void) { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(MYPOINT& _tLeft, MYPOINT& _tRight) : tL_Point(_tLeft), tR_Point(_tRight) {}
	// 1. �� ���۷����� �� ����?

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
	int			iStart;		// �� �� �ε��� ���� ����� ���ΰ�
	int			iEnd;		// �� �� �ε��� ���� ����� ���ΰ�
	int			iMotion;	// �� �� ����� ����� ���̰�
	DWORD		dwSpeed;	// � �ӵ��� �ִϸ��̼��� ����� ���ΰ�
	DWORD		dwTime;		// �ð� ���� ���� �ִϸ��̼� ��� �ӵ� ����
}FRAME;

extern HWND		g_hWnd;

// extern ������ �ϸ� ���������� ũ�⸦ ��𼭵� �˼��ִ� ? �ƴϸ� static ?  ���� -> �׳� ��ũ�� ��


// ������ ���� �̳� ����ü
enum DIRECTION { LEFT, RIGHT, END };

// Obj ����Ʈ�� ���� �̳�
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_UI, OBJ_END };

enum MONSTERTYPE { GOOMBA, TUTLE, TYPE_END };