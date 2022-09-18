#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "MapMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Hill.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "Item.h"
#include "Invisible.h"
#include "BulletEffect.h"
#include "SecondBullet.h"
#include "ThirdBullet.h"
#include "AfterImage.h"
#include "Monster.h"
#include "DoubleJumpEffect.h"

const float fJUMP_POWER = 15.f;

CPlayer::CPlayer() : m_dwJumping(0), m_fCurJumpDir(-1.f), m_eGunUpgrade(PLAYER_BULLET_NONE), m_eCurDir(DIRECTION_NONE), m_bGoTunnel(false), m_bOutTunnel(false)
{
	m_bActive = true;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 200.f;

	m_tInfo.fCX = 53.f;
	m_tInfo.fCY = 70.f;

	m_fSpeed = 5.f;
	m_fAirTime = 0.f;

	m_dwHP = dwPLAYER_HP;
	m_eType = OBJ_TYPE_PLAYER;

	m_pBullets = CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_PLAYER);
	Change_State(PLAYER_STATE_IDLE);
	ChangeDir(DIRECTION_RIGHT);
}

int CPlayer::Update(void)
{
	ShowAfterImage();
	if (m_bDead) {
		//CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::SCENE_ID_LOBBY);
		//return OBJ_DEAD;
	}

	if (m_bGoTunnel)
	{
		if (m_tInfo.fY <= TunnelDest.y)
			InTunnel();
		else
			m_bGoTunnel = false;
	}
	if (m_bOutTunnel)
	{
		if (m_tInfo.fY >= TunnelDest.y)
			OutTunnel();

		else
			m_bOutTunnel = false;
	}

	if (!m_bGoTunnel && !m_bOutTunnel)
	{
		Key_Input();
		Jump();
	}

	Update_Rect();
	Update_Frame();

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate(void)
{
	Scroll();

	if (m_tInfo.fCX * 0.5f > m_tInfo.fX)
		m_tInfo.fX = m_tInfo.fCX * 0.5f;

	if (m_tInfo.fCY * 0.5f > m_tInfo.fY)
		m_tInfo.fY = m_tInfo.fCY * 0.5f;

	if (TILEC * TILEX - m_tInfo.fCX * 0.5f < m_tInfo.fX)
		m_tInfo.fX = TILEC * TILEX - m_tInfo.fCX * 0.5f;

	if (TILEC * TILEY - m_tInfo.fCY * 0.5f < m_tInfo.fY) {
		m_tInfo.fY = TILEC * TILEY - m_tInfo.fCY * 0.5f;
	}

}

void CPlayer::Release(void)
{
	
}

void CPlayer::OnCollision(CObj * _pTarget)
{
	float fTempY;
	//float fTempX;

	INFO* pInfo;
	CHill* hill;

	if (m_bGoTunnel || m_bOutTunnel)
		return;

	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_BLOCK:
		pInfo = &_pTarget->Get_Info();

		if (abs(pInfo->fY - m_tInfo.fY) < pInfo->fCY * 0.7f) {
			if (pInfo->fX > m_tInfo.fX) {
				m_tInfo.fX -= m_fSpeed;
			}
			else if (pInfo->fX < m_tInfo.fX) {
				m_tInfo.fX += m_fSpeed;
			}
		}

		if (pInfo->fX - pInfo->fCX * 0.7f <= m_tInfo.fX &&
			pInfo->fX + pInfo->fCX * 0.7f >= m_tInfo.fX) {
			if (pInfo->fY > m_tInfo.fY) {
				if (0 > m_fCurJumpDir) {
					StopJump();
					m_tInfo.fY = _pTarget->Get_Info().fY - (_pTarget->Get_Info().fCY + m_tInfo.fCY) * 0.5f;
				}
			}
		}

		if(dynamic_cast<CBlock*>(_pTarget)->m_eBlockID == BLOCK_ID_TUNNEL_IN)
		{
			if (CKeyMgr::Get_Instance()->Key_Down('S'))
			{
				if (m_dwJumping == 0)
				{
					m_bGoTunnel = true;
					TunnelDest.x = (LONG)_pTarget->Get_Info().fX + (TILEC * 0);
					TunnelDest.y = (LONG)_pTarget->Get_Info().fY + (TILEC * 8);
				}
			}
		}
		if (dynamic_cast<CBlock*>(_pTarget)->m_eBlockID == BLOCK_ID_TUNNEL_OUT)
		{
			if (m_dwJumping == 0)
			{
				m_bOutTunnel = true;
				TunnelDest.x = (LONG)_pTarget->Get_Info().fX + (TILEC * 5);
				TunnelDest.y = (LONG)_pTarget->Get_Info().fY - (TILEC * 10);
			}
		}
		break;

	case OBJ_TYPE_HILL:
		hill = dynamic_cast<CHill*>(_pTarget);
		fTempY = hill->Get_Y(m_tInfo.fX);

		if (0 > m_fCurJumpDir) {
			StopJump();
			m_tInfo.fY = fTempY - m_tInfo.fCY * 0.5f;
		}
		break;
	default:
		break;
	}
}

void CPlayer::OnCollisionEnter(CObj * _pTarget)
{
	INFO* pInfo;
	DWORD dwDamage;

	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_BLOCK:
		pInfo = &_pTarget->Get_Info();
		if (pInfo->fX - pInfo->fCX * 0.7f <= m_tInfo.fX &&
			pInfo->fX + pInfo->fCX * 0.7f >= m_tInfo.fX) {
			if (pInfo->fY < m_tInfo.fY) {
				StopJump();

				if (dynamic_cast<CBlock*>(_pTarget)->Get_BlockID() == BLOCK_ID_INVISIBLE) {
					dynamic_cast<CInvisible*>(_pTarget)->Reveal();
				}
			}
		}
		break;
	case OBJ_TYPE_ITEM:
		switch (dynamic_cast<CItem*>(_pTarget)->Get_ItemID()) {
		case ITEM_ID_COIN:
			dynamic_cast<CStage*>(CSceneMgr::Get_Instance()->Get_CurScene())->Add_Score(100);
			break;
		case ITEM_ID_GUN:
			if (m_eGunUpgrade != PLAYER_BULLET_THIRD) {
				m_eGunUpgrade = (PLAYER_BULLET)(m_eGunUpgrade + 1);
				m_dwDamage = dwPLAYER_STR * m_eGunUpgrade;
			}
			break;
		}
		break;

	case OBJ_TYPE_BULLET_MONSTER:
		dwDamage = dwMONSTER_BULLET_STR;
		dwDamage = dwDamage > m_dwHP ? m_dwHP : dwDamage;
		m_dwHP -= dwDamage;
		if (m_dwHP <= 0)
			Set_Dead();
		break;

	case OBJ_TYPE_MONSTER:
		dwDamage = _pTarget->Get_Damage();
		dwDamage = dwDamage > m_dwHP ? m_dwHP : dwDamage;
		m_dwHP -= dwDamage;
		if (m_dwHP <= 0)
			Set_Dead();
	

		/*for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)) {
			m_Monter_ID = dynamic_cast<CMonster*>(iter)->Get_MonsterID();
		}

	
		if (m_Monter_ID == MONSTER_ID_MOCOCO) {

			pInfo = &_pTarget->Get_Info();

			if (abs(pInfo->fY - m_tInfo.fY) < pInfo->fCY - 5.f && pInfo->fX - pInfo->fCX * 0.7f <= m_tInfo.fX &&
				pInfo->fX + pInfo->fCX * 0.7f >= m_tInfo.fX) {
				if (pInfo->fY > m_tInfo.fY) {
					m_dwJumping = 1;
					m_fAirTime = 0.f;
					Change_State(PLAYER_STATE_JUMP);
				}
				break;
			}
		}
		break;*/

	
		if (MONSTER_ID_BOSS > dynamic_cast<CMonster*>(_pTarget)->Get_MonsterID())
		{
			pInfo = &_pTarget->Get_Info();

			if (abs(pInfo->fY - m_tInfo.fY) < pInfo->fCY - 5.f && pInfo->fX - pInfo->fCX * 0.7f <= m_tInfo.fX &&
				pInfo->fX + pInfo->fCX * 0.7f >= m_tInfo.fX) {
				if (pInfo->fY > m_tInfo.fY) {
					m_dwJumping = 1;
					m_fAirTime = 0.f;
					Change_State(PLAYER_STATE_JUMP);
				}
				break;
			}
		}
			/*auto& iter = *CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER);

			m_Monter_ID = dynamic_cast<CMonster*>(iter)->Get_MonsterID();*/

		

	}
}

FRAME CPlayer::SetFrame(int _iState)
{
	switch (_iState)
	{
	case CPlayer::PLAYER_STATE_IDLE:
	default:
		return { 0, 0, PLAYER_STATE_IDLE, 100000 };
		break;
	case CPlayer::PLAYER_STATE_WALK:
		return{ 0, 3, PLAYER_STATE_WALK, 100 };
		break;
	case CPlayer::PLAYER_STATE_LINE:
		return{ 0, 2, PLAYER_STATE_LINE, 1000 };
		break;
	case CPlayer::PLAYER_STATE_JUMP:
		return{ 0, 0, PLAYER_STATE_JUMP, 100000 };
		break;
	case CPlayer::PLAYER_STATE_UP:
		return { 0, 0, PLAYER_STATE_UP, 100000 };
		break;
	}
}

void CPlayer::Key_Input(void)
{
	bool bMoving = false;

	if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {
		m_tInfo.fX -= m_fSpeed;
		if(m_iCurState == PLAYER_STATE_IDLE)
			Change_State(PLAYER_STATE_WALK);
		ChangeDir(DIRECTION_LEFT);
		bMoving = true;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {
		m_tInfo.fX += m_fSpeed;
		if (m_iCurState == PLAYER_STATE_IDLE)
			Change_State(PLAYER_STATE_WALK);
		ChangeDir(DIRECTION_RIGHT);
		bMoving = true;
	}

	CObj* pObj;
	float fOffset;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
		if (m_dwJumping == 0) {
			m_dwJumping = 1;
			m_fAirTime = 0.f;
			Change_State(PLAYER_STATE_JUMP);
			bMoving = true;
		}

		else if (m_dwJumping == 1 && bMoving && m_eGunUpgrade >= PLAYER_BULLET_THIRD) {
			m_dwJumping = 2;
			m_fAirTime = 0.f;
			fOffset = m_eCurDir == DIRECTION_LEFT ? 120.f : -120.f;
			pObj = CAbstractFactory::Create<CDoubleJumpEffect>(m_tInfo.fX + fOffset, m_tInfo.fY);
			dynamic_cast<CDoubleJumpEffect*>(pObj)->Set_Dir(m_eCurDir);
			CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_EFFECT)->push_back(pObj);
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LCONTROL) && 0 < m_eGunUpgrade) {
		Shot();
	}

	if (!bMoving && m_dwJumping == 0) {
		Change_State(PLAYER_STATE_IDLE);
	}
}

void CPlayer::Jump()
{
	if (0 < m_dwJumping) {
		m_fCurJumpDir = fJUMP_POWER * sinf(90) * m_fAirTime - (9.8f * pow(m_fAirTime, 2)) * 0.5f;
		m_tInfo.fY -= m_fCurJumpDir;
		m_fAirTime += 0.1f;
	}
	else {
		m_tInfo.fY += (9.8f * pow(m_fAirTime, 2)) * 0.5f;
		m_fAirTime += 0.1f;
	}
}

void CPlayer::Scroll()
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_X();
	float fScreenX = m_tInfo.fX + fScrollX;

	if (fOFFSET_X_MIN >= fScreenX) {
		CScrollMgr::Get_Instance()->Add_X(m_fSpeed);
	}
	if (fOFFSET_X_MAX <= fScreenX) {
		CScrollMgr::Get_Instance()->Add_X(-m_fSpeed);
	}

	float fScrollY = CScrollMgr::Get_Instance()->Get_Y();
	float fScreenY = m_tInfo.fY + fScrollY;

	if (fOFFSET_Y_MIN >= fScreenY) {
		CScrollMgr::Get_Instance()->Add_Y(m_fSpeed);
	}

	if (fOFFSET_Y_MAX <= fScreenY) {
		CScrollMgr::Get_Instance()->Add_Y(-m_fSpeed);
	}
}

void CPlayer::StopJump()
{
	m_dwJumping = 0;
	m_fCurJumpDir = -1.f;
	m_fAirTime = 0.0f;
	if(m_iCurState == PLAYER_STATE_JUMP)
		Change_State(PLAYER_STATE_IDLE);
}

void CPlayer::ChangeDir(DIRECTION _eDir)
{
	if (m_eCurDir == _eDir)
		return;

	m_eCurDir = _eDir;

	switch (m_eCurDir)
	{
	case DIRECTION_LEFT:
		m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_LEFT)->Get_BmpDC());
		break;
	case DIRECTION_RIGHT:
		m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_PLAYER_RIGHT)->Get_BmpDC());
		break;
	}
}

void CPlayer::InTunnel()
{
	m_tInfo.fY += m_fSpeed; 
	CScrollMgr::Get_Instance()->Add_Y(m_fSpeed); 
}

void CPlayer::OutTunnel()
{
	if (m_tInfo.fX <= TunnelDest.x)
	{
		m_tInfo.fX += m_fSpeed;
		CScrollMgr::Get_Instance()->Add_X(-(m_fSpeed));
	}
	else
	{
		m_tInfo.fY -= m_fSpeed;
		CScrollMgr::Get_Instance()->Add_Y(-m_fSpeed);
	}
}

void CPlayer::Shot()
{
	CObj* pObj = nullptr;
	CObj* pObj2 = nullptr;

	switch (m_eGunUpgrade)
	{
	case PLAYER_BULLET_FIRST:
		pObj = CAbstractFactory::Create<CBullet>(m_tInfo.fX, m_tInfo.fY);
		break;
	case PLAYER_BULLET_SECOND:
		pObj = CAbstractFactory::Create<CSecondBullet>();
		break;
	case PLAYER_BULLET_THIRD:
		pObj = CAbstractFactory::Create<CThirdBullet>();
		break;
	}

	float iOffset;
	pObj->Set_Type(OBJ_TYPE_BULLET_PLAYER);
	if (m_eCurDir == DIRECTION_RIGHT) {
		dynamic_cast<CBullet*>(pObj)->SetXDir(1.f);
		iOffset = 130.f;
	}
	else {
		dynamic_cast<CBullet*>(pObj)->SetXDir(-1.f);
		iOffset = -130.f;
	}
	m_pBullets->push_back(pObj);

	if (m_eGunUpgrade == PLAYER_BULLET_SECOND) {
		pObj2 = CAbstractFactory::Create<CBulletEffect>(m_tInfo.fX + iOffset, m_tInfo.fY);
		dynamic_cast<CBulletEffect*>(pObj2)->Set_Dir(m_eCurDir);
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_EFFECT)->push_back(pObj2);
	}

	if (m_eGunUpgrade >= PLAYER_BULLET_SECOND)
		pObj->Set_Pos(m_tInfo.fX + iOffset, m_tInfo.fY);
}

void CPlayer::ShowAfterImage()
{
	if (m_eGunUpgrade < PLAYER_BULLET_SECOND)
		return;

	if (m_AfterImgDelay <= 0.f) 
	{
		if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_AFTERIMAGE)->size() > 2)
		{
			CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_AFTERIMAGE)->front()->Set_Dead();

			auto& A = CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_AFTERIMAGE)->begin()++;
			auto& B = ++(A);
			auto& C = ++(B);

			dynamic_cast<CAfterImage*>(*A)->Set_Alpha(3);
			dynamic_cast<CAfterImage*>(*B)->Set_Alpha(3);
			dynamic_cast<CAfterImage*>(*C)->Set_Alpha(2);
		}

		CObj* _Obj = CAbstractFactory::Create<CAfterImage>(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CAfterImage*>(_Obj)->Set_Frame(m_tFrame);
		dynamic_cast<CAfterImage*>(_Obj)->Set_Dir(m_eCurDir);
		dynamic_cast<CAfterImage*>(_Obj)->Set_Alpha(1);
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_AFTERIMAGE)->push_back(_Obj);
		m_AfterImgDelay = 4.f;
	}
	else
		--m_AfterImgDelay;
}
