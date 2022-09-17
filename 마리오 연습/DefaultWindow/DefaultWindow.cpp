// DefaultWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// 윈도우 창 생성 설정
BOOL                InitInstance(HINSTANCE, int);			// 윈도우 창 생성
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,		// 인스턴스 : 메모리에 할당되는 실체, 즉 객체의 요소
                     _In_opt_ HINSTANCE hPrevInstance,	// 전에 실행되었던 인스턴스의 핸들이 넘어온다. 없을 경우 null
                     _In_ LPWSTR    lpCmdLine,	// 문자열을 지원하는 성격
                     _In_ int       nCmdShow)	// 윈도우 
{

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
    
	MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame		MainGame;
	MainGame.Initialize();

	DWORD		dwTime = GetTickCount(); // 1 / 1000초의 해당하는 DWORD 정수 값을 반환하는 함수


	//PM_REMOVE	: 메세지 큐에서 메세지를 읽어옴과 동시에 메세지를 큐에서 제거
	//PM_NOREMOVE : 메세지 큐에서 메세지를 읽어옴과 동시에 메세지를 제거하지는 않는다. 

    // 기본 메시지 루프입니다.
    while (true)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);	// 키보드 메세지를 가공하여 프로그램에서 사용할 수 있도록 번역하는 함수
				DispatchMessage(&msg); // 시스템 큐에서 꺼낸 메세지를 프로그램에 전달하여 처리를 지시하는 함수(WndProc 호출)
			}
		}
		else
		{
			if (dwTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();
				
				dwTime = GetTickCount();
			}

			
		}
       
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	RECT		rc{0, 0, WINCX, WINCY};

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
     //rc = rc + 기본 창 스타일 + 메뉴 바 크기 고려 여부

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, // 어느 위치에 창을 생성할 것인가(x, y 좌표)
	  rc.right - rc.left, 
	  rc.bottom - rc.top, // 생성할 창의 가로, 세로 사이즈
	  nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

	case WM_KEYDOWN:

		switch (wParam)
		{		
		case VK_ESCAPE:
			DestroyWindow(g_hWnd);
			break;	
		}
		break;
		
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
  
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



// kernel : 메모리를 관리하고 프로그램을 구동시키는 기능을 담당하는 라이브러리
// user :  유저 인터페이스와 윈도우 창을 관리하는 라이브러리
// GDI : 화면 처리와 그래픽을 담당하는 라이브러리