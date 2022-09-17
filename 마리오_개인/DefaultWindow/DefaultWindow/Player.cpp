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

const float fJUMP_POWER = 15.f;

CPlayer::CPlayer() : m_bJumping(false), m_fCurJumpDir(-1.f), m_bGun(false), m_eCurDir(DIRECTION_NONE)
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
	m_tInfo.fY = 600.f;

	m_tInfo.fCX = 53.f;
	m_tInfo.fCY = 70.f;

	m_fSpeed = 5.f;
	m_fAirTime = 0.f;

	m_dwHP = 3;
	m_eType = OBJ_TYPE_PLAYER;

	m_pBullets = CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BULLET_PLAYER);
	Change_State(PLAYER_STATE_IDLE);
	ChangeDir(DIRECTION_RIGHT);
}

int CPlayer::Update(void)
{
	if (m_bDead) {
		//return OBJ_DEAD;
		//CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::SCENE_ID_LOBBY);
		//return OBJ_DEAD;
	}


	Key_Input();
	Jump();

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
	switch (_pTarget->Get_Type())
	{
	case OBJ_TYPE_BLOCK:
		pInfo = &_pTarget->Get_Info();

		if (abs(pInfo->fY - m_tInfo.fY) < pInfo->fCY) {
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
			m_bGun = true;
			break;
		}
		break;

	case OBJ_TYPE_BULLET_MONSTER:
		--m_dwHP;
		if (m_dwHP <= 0)
			Set_Dead();
		break;
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
	CObj* pObj;
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

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
		if (!m_bJumping) {
			m_bJumping = true;
			m_fAirTime = 0.f;
			Change_State(PLAYER_STATE_JUMP);
			bMoving = true;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LCONTROL) && m_bGun) {
		pObj = CAbstractFactory::Create<CBullet>(m_tInfo.fX, m_tInfo.fY);
		pObj->Set_Type(OBJ_TYPE_BULLET_PLAYER);
		if(m_eCurDir == DIRECTION_RIGHT)
			dynamic_cast<CBullet*>(pObj)->SetXDir(1.f);
		else 
			dynamic_cast<CBullet*>(pObj)->SetXDir(-1.f);
		m_pBullets->push_back(pObj);
	}

	if (!bMoving && !m_bJumping)
		Change_State(PLAYER_STATE_IDLE);
}

void CPlayer::Jump()
{
	if (m_bJumping) {
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
	m_bJumping = false;
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
