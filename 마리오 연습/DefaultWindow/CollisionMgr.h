#pragma once

class CObj;
// 전방 선언 why?

// 싱글톤은 아니다.
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static	void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);
	
	static	void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);
	static	bool	Check_Sphere(CObj* _pDest, CObj* _pSrc);

	static	void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);
	static	bool	Check_Rect(CObj* _pDest, CObj* _pSrc, float* _pX, float* _pY);

};

