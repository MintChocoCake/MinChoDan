#include "stdafx.h"
#include "UIButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CUIButton::CUIButton() : m_eBtnID(BUTTON_ID_NONE)
{
	m_bActive = true;
}


CUIButton::~CUIButton()
{
}

void CUIButton::SetButtonID(BUTTON_ID _eID)
{
	m_eBtnID = _eID;
	m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp((BMP_KEY)((int)m_eBtnID + BMP_KEY_START_BTN))->Get_BmpDC());
}

void CUIButton::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_eType = OBJ_TYPE_UI;
}

int CUIButton::Update(void)
{
	m_tFrame.dwStart = 0;
	Update_Rect();

	return 0;
}

void CUIButton::OnCollision(CObj * _pTarget)
{
	if (_pTarget->Get_Type() == OBJ_TYPE_PLAYER) {
		m_tFrame.dwStart = 1;
		
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {

			switch (m_eBtnID)
			{
			case CUIButton::BUTTON_ID_START:
				CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::SCENE_ID_STAGE);
				break;
			case CUIButton::BUTTON_ID_EDIT:
				CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::SCENE_ID_EDIT);
				break;
			}			
		}
	}
}

void CUIButton::OnCollisionEnter(CObj * _pTarget)
{
}
