#include "stdafx.h"
#include "Invisible.h"
#include "BmpMgr.h"

CInvisible::CInvisible() : m_bReveal(false)
{
}


CInvisible::~CInvisible()
{
}

void CInvisible::Reveal()
{
	if (!m_bReveal) {
		m_bReveal = true;
		m_hBmpDC = &(CBmpMgr::Get_Instance()->Find_Bmp(BMP_KEY_BLOCK_ITEM_BOX)->Get_BmpDC());

	}

}

void CInvisible::LateUpdate(void)
{
	Update_Active();
	Update_Rect();
}
