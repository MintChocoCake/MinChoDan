#include "stdafx.h"
#include "LineMgr.h"


CLineMgr*	CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
	ZeroMemory(m_LinePoint, sizeof(m_LinePoint));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	// 파일 저장과 로드를 라인 매니저에서 해서 초기화문으로 파일을 불러옴
	Load_File();
}

int CLineMgr::Update(void)
{
	// 실패 
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LSHIFT))
		m_bDrowing = true;
	
	// 임시 - 그릴떈 false 넣으셈 ㅋㅋ..
	if (false == m_bDrowing)
	{

		POINT		pt{};

		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		// 디파인에서 exturn 해놓은 핸들 g_hWnd

		pt.x -= (long)CScrollMgr::Get_Instance()->Get_Scroll_X();
		// 플레이어가 오른쪽으로 움직인다. ->  플레이어의 x 좌표가 +  , 스크롤의 x 좌표는 - 
		// 두 값이 상쇄되어야 플레이어가 중앙 / 중앙 윈도우 범위( 100<=  에서 벗어나지 않음

		pt.y -= (long)CScrollMgr::Get_Instance()->Get_Scroll_Y();


		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			// 라인 에디트 최초 실행
			// 왼쪽 포인터 X 의 값이없고 && 왼쪽 포인터 Y 의 값이 없다면
			if (!m_LinePoint[LEFT].fX && !m_LinePoint[LEFT].fY)
			{
				// 첫마우스 좌표를 전달
				m_LinePoint[LEFT].fX = (float)pt.x;
				m_LinePoint[LEFT].fY = (float)pt.y;
			}
			// 최초 실행 이후
			else
			{
				// 좌우 그릴때 y 좌표 고정
				if (CKeyMgr::Get_Instance()->Key_Down('Q'))
				{
					pt.y = m_LinePoint[LEFT].fY;
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				else
				{
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				// 상하 그릴때 x 좌표 고정 
				if (CKeyMgr::Get_Instance()->Key_Down('E'))
				{
					pt.x = m_LinePoint[LEFT].fX;
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				else
				{
					m_LinePoint[RIGHT].fY = (float)pt.y;
					m_LinePoint[RIGHT].fX = (float)pt.x;
				}
				// 마우스 좌표
				//m_LinePoint[RIGHT].fX = (float)pt.x;
				//m_LinePoint[RIGHT].fY = (float)pt.y;

				// 왼쪽, 오른쪽 점의 좌표를 넘겨줌 ( Line 에서 두 점을 선으로 그림 )
				m_LineList.push_back(new CLine(m_LinePoint[LEFT], m_LinePoint[RIGHT]));

				// 다음 선을 그릴떈, 오른쪽 점이 왼쪽 점이 되야 해서 오른쪽 점의 좌표를 왼쪽 점의 좌표가 되게 바꿔주기 
				m_LinePoint[LEFT].fX = m_LinePoint[RIGHT].fX;
				m_LinePoint[LEFT].fY = m_LinePoint[RIGHT].fY;
			}
		}

		// 마오스 오른쪽 클릭으로 왼쪽좌표 초기화
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			m_LinePoint[LEFT].fX = (float)pt.x;
			m_LinePoint[LEFT].fY = (float)pt.y;
		}

	}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_File();
		return 0;
	}

	// 클라이언트 파일이라 나중에 뺴야되는 부분
	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		Load_File();
		return 0;
	}

	// 스크롤을 플레이어 방향과 반대로 이동하여 중점을 상쇄시킴 ?
	// 왼쪽 키를 누르면 스크롤을 오른쪽으로 이동
	/*
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(5.f);
	// 오른쪽 키를 누르면 스크롤을 왼쪽으로 이동
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(-5.f);
		*/

	return 0;
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC _hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(_hDC);
}

void CLineMgr::Release(void)
{
	// 라인 리스트의 첫번쨰 부터 끝 까지 탐색해서 세이프 딜리트
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	// 해당 요소의 리스트를 삭제
	m_LineList.clear();
}

// 라인 타기 ( x 좌표는 레퍼런스 y 좌표는 참조값으로 계속 갱신 ? )
bool CLineMgr::Collision_Line(float& _fX, float& _fY, float* _pfY)
{
	// TargetLine을 결정하기전에 플레이어 위치랑 비교해서 ㄱㄱㄱㄱㄱ

	if (m_LineList.empty())
		return false;

	// 라인을 타게할 타겟 라인
	CLine*		pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tL_Point.fX &&
			_fX <= iter->Get_Info().tR_Point.fX &&
			_fY <= iter->Get_Info().tL_Point.fY &&
			_fY <= iter->Get_Info().tR_Point.fY) {
			pTargetLine = iter;
			/*if (*_pfY - iter->Get_Info().tL_Point.fY >
				*_pfY - iter->Get_Info().tR_Point.fY)
			{
				pTargetLine = iter;
			}
			else if (*_pfY - iter->Get_Info().tL_Point.fY <
				*_pfY - iter->Get_Info().tR_Point.fY)
			{
				pTargetLine = iter;
			}*/
		}
	}

	if (nullptr == pTargetLine)
		return false;

	// 라인타기 공식 : 직선의 방정식
	// Y = ( 높이 / 밑변 ) * [Y절편]( X - x1 ) + y1  
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pTargetLine->Get_Info().tL_Point.fX;
	float	y1 = pTargetLine->Get_Info().tL_Point.fY;

	float	x2 = pTargetLine->Get_Info().tR_Point.fX;
	float	y2 = pTargetLine->Get_Info().tR_Point.fY;

	*_pfY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
	

	/*
	if (m_LineList.empty())
		return false;

	// 라인을 타게할 타겟 라인
	CLine*		pTargetLine = nullptr;

	float		fLine_PY = 0.f;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tL_Point.fX &&
			_fX <= iter->Get_Info().tR_Point.fX) {
			
			float	x1 = iter->Get_Info().tL_Point.fX;
			float	y1 = iter->Get_Info().tL_Point.fY;

			float	x2 = iter->Get_Info().tR_Point.fX;
			float	y2 = iter->Get_Info().tR_Point.fY;

			fLine_PY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			if (fLine_PY >= *_pfY && fLine_PY <= *_pfY )
			{
				*_pfY = fLine_PY;
				pTargetLine = iter;
				return true;
			}
		}
	}

	if (nullptr == pTargetLine)
		return false;
		*/

	// 라인타기 공식 : 직선의 방정식
	// Y = ( 높이 / 밑변 ) * [Y절편]( X - x1 ) + y1  
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	/*float	x1 = pTargetLine->Get_Info().tL_Point.fX;
	float	y1 = pTargetLine->Get_Info().tL_Point.fY;

	float	x2 = pTargetLine->Get_Info().tR_Point.fX;
	float	y2 = pTargetLine->Get_Info().tR_Point.fY;

	fLine_PY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
	*/
}

void CLineMgr::Save_File(void)
{
	// 파일 개방
	HANDLE		hFile = CreateFile(L"../IsData/Line.dat", // 파일경로 , 생성할 파일 이름
		GENERIC_WRITE,	// 파일 접근 모드 (쓰기 전용) GENERIC_READ(읽기 전용)
		NULL,			
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// 개방 실패시 반환되는 매크로 ( -1 임 )
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		// 파일 쓰기
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);
		// ( 개방할 파일 , 저장할 데이터 주소 , 저장할 데이터 크기 , 예외처리 용 변수 주소 , 몰?루
	}

	// 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 성공"), L"성공", MB_OK);

}

void CLineMgr::Load_File(void)
{
	HANDLE		hFile = CreateFile(L"../IsData/Line.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	// 파일 로드 시 선들의 정보를 받아아줄 LINE 타입 tIfno
	LINE		tInfo{}; 

	// 파일을 끝까지 다 읽어 오기위해 while 문 사용
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		// 예외가 0 ( 다 읽었을시 ) 탈출
		if (0 == dwByte)
			break;

		// Info 정보를 Line 에전달하여 생성하고 생성된 요소를 리스트에 넣음
		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 성공"), L"성공", MB_OK);
}
