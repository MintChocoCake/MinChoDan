#pragma once
#include "Obj.h"

class CAfterImage : public CObj
{
public:
	CAfterImage();
	~CAfterImage();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	//virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollision(CObj* _pTarget);
	virtual void OnCollisionEnter(CObj* _pTarget);
public:
	void Set_Frame(FRAME _Frame) { m_tFrame = _Frame; }
	void Set_Dir(DIRECTION _Dir) { Dir = _Dir; }
	void Set_Alpha(int _Alpha);
private:
	DIRECTION Dir;
	int Alpha = 0;

};

// �ܻ� ���� ��Ÿ��
// �ܻ� ���� ��Ÿ�Ӹ��� �ܻ� �̹��� ����?
// �ܻ��� ������� ��Ÿ��
// �ܻ� ���� = �ܻ� ���� ��Ÿ�� / �ܻ��� ������� ��Ÿ��
