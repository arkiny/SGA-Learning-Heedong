#include "StdAfx.h"
#include "cGameApplication.h"
#include "cGameMgr.h"
#include <MMSystem.h>



cGameMgr* g_pGameMgr;

RECT cGameApplication::_wndRect = {0,0,1024,768};
cGameApplication::cGameApplication(cGameMgr* pGameMgr)
{
	g_pGameMgr = pGameMgr;
}


cGameApplication::~cGameApplication(void)
{
	delete g_pGameMgr;
}

bool cGameApplication::Init(HINSTANCE hInstance, WCHAR* title, WCHAR* className, int nCmdShow)
{
	_hInst = hInstance;
	// 문자열을 초기화합니다.
	wsprintf(_szTitle,title);
	wsprintf(_szWindowClass, className);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	return TRUE;

}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
//
ATOM cGameApplication::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.lpszClassName = _szWindowClass;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.style = CS_VREDRAW | CS_HREDRAW ;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = &cGameApplication::WndProc;
	wc.lpszMenuName = NULL;

	return RegisterClass(&wc);
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
BOOL cGameApplication::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   _hInst = hInstance; // 인스턴스 핸들을 멤버 변수에 저장합니다.
  

   hWnd = CreateWindow(_szWindowClass, _szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   _hwnd = hWnd;
    GetClientRect(_hwnd,&_wndRect);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK cGameApplication::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pGameMgr->MsgProc(hWnd, message, wParam, lParam);

	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		Paint(hdc, hWnd);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
	
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void cGameApplication::Run()
{
	DWORD prevTime = timeGetTime();
	DWORD curTime = prevTime;
	DWORD deltaTime = 0;
	DWORD accumTime = 0;
	int   accumFrame = 0;

	MSG msg;
	HDC hdc = GetDC(_hwnd);
	

	// 기본 메시지 루프입니다.
	while (true)
	{
		

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}
		else
		{
			curTime = timeGetTime();
			deltaTime = curTime - prevTime;
			prevTime = curTime;

			accumTime += deltaTime;
			accumFrame++;

			
			static WCHAR fpsString[20] = L"";



			if( accumTime >= 1000 )
			{
				_fps = (accumFrame*1000.0f)/accumTime;	// 최악의 경우 1 frame의 오차가 있을 수 있다

				accumTime -= 1000;
				accumFrame = 0;

		
				swprintf( fpsString, L"FPS : %2.2f", _fps );
				//SetWindowText(_hwnd,fpsString);
			}

		
			Update( deltaTime / 1000.0f);
			::InvalidateRect(_hwnd,NULL,FALSE);
			Render(hdc);
		
			
		}
	
		
	}

	

	ReleaseDC(_hwnd,hdc);

}

void cGameApplication::Render(HDC hdc1)
{	
	
	HDC hdc = GetDC(_hwnd);
	cGameApplication::Paint(hdc, _hwnd);
	ReleaseDC(_hwnd,hdc);


}

void cGameApplication::Update(float deltaTime)
{
	g_pGameMgr->Update(deltaTime);
}

void cGameApplication::Paint(HDC hdc, HWND hWnd)
{
	static int count=0;
	wchar_t str[128];
	wsprintf(str,L"%d",++count);
	SetWindowText(hWnd,str);
	

	HDC	MemDC = CreateCompatibleDC(hdc);

	HBITMAP	hBlankBitMap = CreateCompatibleBitmap(hdc,
			_wndRect.right,
			_wndRect.bottom);
	//빈 비트맵을 메모리 DC에 선택 (도화지)
	HBITMAP	hOldBit = (HBITMAP)SelectObject(MemDC, hBlankBitMap);

	g_pGameMgr->Render(MemDC);

	BitBlt(hdc, 0, 0, _wndRect.right, _wndRect.bottom, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, hOldBit);
	DeleteObject(hBlankBitMap);
	DeleteObject(MemDC);

	

}