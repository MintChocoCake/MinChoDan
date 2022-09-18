#include "stdafx.h"
#include "MapMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Hill.h"
#include "Gunner.h"
#include "RotateFire.h"
#include "Invisible.h"
#include "Monster.h"
#include "Tutle.h"
#include "Mococo.h"
#include "CTunnelMonster.h"
#include "Boss.h"
#include "BombMob.h"
#include "FireMob.h"

CMapMgr* CMapMgr::m_pInstance = nullptr;

CMapMgr::CMapMgr() : m_bDrawing(false), m_bActive(false)
{
	ZeroMemory(m_szBuffer, sizeof(wchar_t) * 100);
}

CMapMgr::~CMapMgr()
{
}

void CMapMgr::Initialize()
{
	wsprintf(m_szBuffer, _T("<Map Edit>     LBUTTON: Draw Line     RBUTTON: End Draw     K: Save     L: Load"));
}

void CMapMgr::Update()
{
	Key_Input();
}

void CMapMgr::Render(HDC _HDC)
{
	if (!m_bActive)
		return;

	if (m_bDrawing) {
		m_LineTemp.Render(_HDC);
	}

	MYPOINT pt;
	Get_Cursor(&pt);
	float fTileCHalf = TILEC * 0.5f;
	float fX = floorf(pt.fX / TILEC) * TILEC + fTileCHalf;
	float fY = floorf(pt.fY / TILEC) * TILEC + fTileCHalf;

	float fScrollX = CScrollMgr::Get_Instance()->Get_X();
	float fScrollY = CScrollMgr::Get_Instance()->Get_Y();

	Rectangle(_HDC, 
		(int)(fX - fTileCHalf + fScrollX), 
		(int)(fY - fTileCHalf + fScrollY),
		(int)(fX + fTileCHalf + fScrollX), 
		(int)(fY + fTileCHalf + fScrollY));
	TextOut(_HDC, 0, WINCY - 20, m_szBuffer, wcslen(m_szBuffer));
}

void CMapMgr::Load_Map(const TCHAR * _szPath)
{
	HANDLE hFile = CreateFile(_szPath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MessageBox(g_hWnd, _T("Load Failed"), _T("Failed"), MB_OK);
		return;
	}

	CObjMgr::Get_Instance()->Release();

	DWORD dwByte = 0;
	LINE tLineBuffer;
	INFO tInfoBuffer;
	size_t iCountBuffer = 0;
	CObj* obj = nullptr;
	CHill* hill = nullptr;
	int eIDTemp;

	for (int i = 0; i < OBJ_TYPE_END; ++i) {
		list<CObj*>* pList = CObjMgr::Get_Instance()->Get_ObjList((OBJ_TYPE)i);

		switch (i)
		{
		case OBJ_TYPE_PLAYER:
		case OBJ_TYPE_EFFECT:
		case OBJ_TYPE_AFTERIMAGE:
			continue;
		}

		ReadFile(hFile, &iCountBuffer, sizeof(size_t), &dwByte, nullptr);

		for (size_t j = 0; j < iCountBuffer; ++j) {
			switch (i)
			{
			case OBJ_TYPE_BLOCK:
				ReadFile(hFile, &eIDTemp, sizeof(BLOCK_ID), &dwByte, nullptr);
				ReadFile(hFile, &tInfoBuffer, sizeof(INFO), &dwByte, nullptr);

				Create_Block((BLOCK_ID)eIDTemp, MYPOINT{ tInfoBuffer.fX, tInfoBuffer.fY });
				break;

			case OBJ_TYPE_HILL:
				ReadFile(hFile, &tLineBuffer, sizeof(LINE), &dwByte, nullptr);

				obj = CAbstractFactory::Create<CHill>();
				hill = dynamic_cast<CHill*>(obj);

				hill->Set_Left(tLineBuffer.tLeft);
				hill->Set_Right(tLineBuffer.tRight);

				pList->push_back(obj);
				break;
			case OBJ_TYPE_MONSTER:
				ReadFile(hFile, &eIDTemp, sizeof(MONSTER_ID), &dwByte, nullptr);
				ReadFile(hFile, &tInfoBuffer, sizeof(INFO), &dwByte, nullptr);

				Create_Monster((MONSTER_ID)eIDTemp, MYPOINT{ tInfoBuffer.fX, tInfoBuffer.fY });
				break;
			default:
				break;
			}
		}
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load Succeed"), _T("Succeed"), MB_OK);
}

void CMapMgr::Key_Input()
{
	if (!m_bActive)
		return;

	MYPOINT tCursor;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		Get_Cursor(&tCursor);

		if (m_bDrawing) {
			m_LineTemp.SetRight(tCursor);

			CObj* obj = CAbstractFactory::Create<CHill>();
			CHill* hill = dynamic_cast<CHill*>(obj);

			LINE& data = m_LineTemp.GetInfo();
			hill->Set_Left(data.tLeft);
			hill->Set_Right(data.tRight);

			CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_HILL)->push_back(obj);

			m_LineTemp.SetLeft(tCursor);
		}
		else {
			m_LineTemp.SetLeft(tCursor);
			m_bDrawing = true;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON)) {
		if (m_bDrawing)
			m_bDrawing = false;
	}

	if (m_bDrawing) {
		Get_Cursor(&tCursor);
		m_LineTemp.SetRight(tCursor);
	}

	if(CKeyMgr::Get_Instance()->Key_Down(0x31))
		Save_Map(STAGE_MAP_FILE[0]);

	if (CKeyMgr::Get_Instance()->Key_Down(0x32))
		Save_Map(STAGE_MAP_FILE[1]);

	if (CKeyMgr::Get_Instance()->Key_Down(0x33))
		Save_Map(STAGE_MAP_FILE[2]);

	if (CKeyMgr::Get_Instance()->Key_Down(0x34))
		Load_Map(STAGE_MAP_FILE[0]);

	if (CKeyMgr::Get_Instance()->Key_Down(0x35))
		Load_Map(STAGE_MAP_FILE[1]);

	if (CKeyMgr::Get_Instance()->Key_Down(0x36))
		Load_Map(STAGE_MAP_FILE[2]);

	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		CScrollMgr::Get_Instance()->Add_X(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		CScrollMgr::Get_Instance()->Add_X(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
		CScrollMgr::Get_Instance()->Add_Y(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
		CScrollMgr::Get_Instance()->Add_Y(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1)) {
		Create_Block(BLOCK_ID_TILE);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2)) {
		Create_Block(BLOCK_ID_BOX);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F3)) {
		Create_Block(BLOCK_ID_ITEM_BOX);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F4)) {
		Create_Block(BLOCK_ID_INVISIBLE);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F5)) {
		Create_Block(BLOCK_ID_ROTATE_FIRE);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F6)) {
		Create_Block(BLOCK_ID_TUNNEL_IN);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F7)) {
		Create_Block(BLOCK_ID_TUNNEL_OUT);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F8)) {
		Create_Block(BLOCK_ID_TUNNEL_MOB);
		Create_Monster(MONSTER_ID_TUNNEL);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F9)) {
		Create_Monster(MONSTER_ID_BOSS);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('Q')) {
		Create_Block(BLOCK_ID_GOLDE_TILE);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Z')) {
		Create_Monster(MONSTER_ID_MUSHROOM);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		Create_Monster(MONSTER_ID_GUNNER);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('C')) {
		Create_Monster(MONSTER_ID_TUTLE);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('V')) {
		Create_Monster(MONSTER_ID_MOCOCO);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('B')) {
		Create_Monster(MONSTER_ID_FIRE);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('N')) {
		Create_Monster(MONSTER_ID_BOMB);
	}
}

void CMapMgr::Get_Cursor(MYPOINT * _tResult)
{
	POINT pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	*_tResult = MYPOINT((float)(pt.x - CScrollMgr::Get_Instance()->Get_X()), (float)pt.y - CScrollMgr::Get_Instance()->Get_Y());
}

void CMapMgr::Save_Map(const TCHAR* _szPath)
{
	HANDLE hFile = CreateFile(_szPath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (INVALID_HANDLE_VALUE == hFile) {
		MessageBox(g_hWnd, _T("Save Failed"), _T("Failed"), MB_OK);
		return;
	}

	DWORD dwByte = 0;
	size_t iCountBuffer;
	int eIDTemp;

	for (int i = 0; i < OBJ_TYPE_END; ++i) {
		switch (i)
		{
		case OBJ_TYPE_PLAYER:
		case OBJ_TYPE_EFFECT:
		case OBJ_TYPE_AFTERIMAGE:
			continue;
		}
		list<CObj*>* pList = CObjMgr::Get_Instance()->Get_ObjList((OBJ_TYPE)i);

		iCountBuffer = (*pList).size();
		WriteFile(hFile, &iCountBuffer, sizeof(size_t), &dwByte, nullptr);

		for (auto& target : *pList) {
			switch (i)
			{
			case OBJ_TYPE_BLOCK:
				eIDTemp = dynamic_cast<CBlock*>(target)->Get_BlockID();
				WriteFile(hFile, &(eIDTemp), sizeof(BLOCK_ID), &dwByte, nullptr);
				WriteFile(hFile, &(target->Get_Info()), sizeof(INFO), &dwByte, nullptr);
				break;

			case OBJ_TYPE_HILL:
				WriteFile(hFile, &(dynamic_cast<CHill*>(target)->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);
				break;

			case OBJ_TYPE_MONSTER:
				eIDTemp = dynamic_cast<CMonster*>(target)->Get_MonsterID();
				WriteFile(hFile, &(eIDTemp), sizeof(MONSTER_ID), &dwByte, nullptr);
				WriteFile(hFile, &(target->Get_Info()), sizeof(INFO), &dwByte, nullptr);
				break;
			default:
				break;
			}
		}
	}
	
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save Succeed"), _T("Succeed"), MB_OK);
}

void CMapMgr::Create_Block(BLOCK_ID _eID, MYPOINT _tPos)
{
	if (_tPos.fY < 0) {
		Get_Cursor(&_tPos);

		_tPos.fX = floorf(_tPos.fX / TILEC) * TILEC + TILEC * 0.5f;
		_tPos.fY = floorf(_tPos.fY / TILEC) * TILEC + TILEC * 0.5f;
	}

	CObj* pObj;
	switch (_eID)
	{
	case BLOCK_ID_INVISIBLE:
		pObj = CAbstractFactory::Create<CInvisible>(_tPos.fX, _tPos.fY);
		break;
	case BLOCK_ID_ROTATE_FIRE:
		pObj = CAbstractFactory::Create<CRotateFire>(_tPos.fX, _tPos.fY);
		break;
	default:
		pObj = CAbstractFactory::Create<CBlock>(_tPos.fX, _tPos.fY);
		break;
	}
	
	dynamic_cast<CBlock*>(pObj)->Set_BlockID(_eID);
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_BLOCK)->push_back(pObj);
}

void CMapMgr::Create_Monster(MONSTER_ID _eID, MYPOINT _tPos)
{
	if (_tPos.fY < 0) {
		Get_Cursor(&_tPos);

		_tPos.fX = floorf(_tPos.fX / TILEC) * TILEC + TILEC * 0.5f;
		_tPos.fY = floorf(_tPos.fY / TILEC) * TILEC + TILEC * 0.5f;
	}

	CObj* pObj;
	switch (_eID)
	{
	case MONSTER_ID_MUSHROOM:
		pObj = CAbstractFactory::Create<CMonster>(_tPos.fX, _tPos.fY);
		break;
	case MONSTER_ID_GUNNER:
		pObj = CAbstractFactory::Create<CGunner>(_tPos.fX, _tPos.fY);
		break;
	case MONSTER_ID_TUTLE:
		pObj = CAbstractFactory::Create<CTutle>(_tPos.fX, _tPos.fY);
		break;
	case MONSTER_ID_MOCOCO:
		pObj = CAbstractFactory::Create<CMococo>(_tPos.fX, _tPos.fY);
		break;
	case MONSTER_ID_TUNNEL:
		pObj = CAbstractFactory::Create<CTunnelMonster>(_tPos.fX, _tPos.fY);
		break;
	case MONSTER_ID_BOSS:
		pObj = CAbstractFactory::Create<CBoss>(_tPos.fX, _tPos.fY);
		break;
	case MONSTER_ID_BOMB:
		pObj = CAbstractFactory::Create<CBombMob>(_tPos.fX, _tPos.fY);
		break;
	case MONSTER_ID_FIRE:
		pObj = CAbstractFactory::Create<CFireMob>(_tPos.fX, _tPos.fY);
		break;
	}

	CObjMgr::Get_Instance()->Get_ObjList(OBJ_TYPE_MONSTER)->push_back(pObj);
}

