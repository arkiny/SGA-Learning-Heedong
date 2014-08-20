/*
	@author		Heedong Arkiny Lee
	@git		https://github.com/arkiny/SGA-Learning-Heedong
	@reference : http://www.relisoft.com/win32/winnie.html

	�⺻������ WinAPI���� ���̴� ��Ʈ�� Parameter�� 
	��κ� LPCWSTR(Long Pointer to Constant Wide String)
	2byte char�� ����Ǵ� str������ Parameter
*/

#include "000-1 SimpleWindw.h"

LRESULT CALLBACK WindowsProcedure(HWND hwnd, unsigned int message, 
									WPARAM wParam, LPARAM lParam);

WinClass::WinClass(WNDPROC winProc, wchar_t const * className, HINSTANCE hInst){
	_class.style = 0;
	_class.lpfnWndProc = winProc; // windows procedure
	_class.cbClsExtra = 0;
	_class.cbWndExtra = 0;
	_class.hInstance = hInst;  // owner of the class
	_class.hIcon = 0;
	_class.hCursor = ::LoadCursor(0, IDC_ARROW); // optional
	_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// also optional
	_class.lpszMenuName = 0;
	_class.lpszClassName = (LPCWSTR)className; // mendatory
}

WinMaker::WinMaker(wchar_t const * caption, wchar_t const * className, 
					HINSTANCE hInstance){
	_hwnd = ::CreateWindow(
		(LPCWSTR) className,	// name of the window class
		caption,				// window caption
		WS_OVERLAPPEDWINDOW,	// style
		// F12�ؼ� ���� WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
		// ���߿� ������ ���鶧 �ִ�ȭ ��ư�� ���ų� �Ҷ� ���⼭ �����ϸ� �ȴٰ� �մϴ�.
		CW_USEDEFAULT,			// x position
		CW_USEDEFAULT,			// y position
		CW_USEDEFAULT,			// width
		CW_USEDEFAULT,			// height
		0,						// handle to parent
		0,						// handle to menu
		hInstance,				// applcation instance
		0);						// window creation data	
}

// Window Procedure called by Windows
// �ݹ�Ǵ� ���ν��� �Լ�
// wmquit = 0 �ϰ��, ���� �޼�����, ����
// �ƴҽ� DefWindwsProc�� ���Ͽ� ����
LRESULT CALLBACK WindowProcedure
(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;

	}
	// defWindowProc�� ��Ÿ �޼����� �����ϱ����� ����
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}

// Window API�� WinMain���� �����
// while loop������ return 0�� ���������� ��� ����
// wm_quit�� ���� ������� 0�� �ƴ� ��
// wm_quit�� ������� 0�� �ް� ��
// ���� ���� ����� -1
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
	char * cmdParam, int cmdShow){

	wchar_t className[] = L"MyfirstWindow";

	// Winclass Ŭ������ ������ �ý��ۿ� ���
	WinClass winClass(WindowProcedure, className, hInst);
	winClass.Register();

	// ���� �����ְ�
	WinMaker win(L"�̰� ���� ù ����â�̴�! �ȳ� ����!", className, hInst);
	win.Show(cmdShow);

	// �ܺ� �̺�Ʈ�� �޾ƿͼ� ó��
	MSG  msg;
	int status;
	while ((status = ::GetMessage(&msg, 0, 0, 0)) != 0)
	{
		if (status == -1)
			return -1;
		::DispatchMessage(&msg);
	}

	return msg.wParam;
}


// ������ ������ �ڵ� 
// (string�� wstr���� �ٲٰų� char�� wchar_t �� �ٲٰų�..)

/*WCHAR strtemp[50];
MultiByteToWideChar(0, 0, className, 50, strtemp, 50);
LPCWSTR cstrtemp = strtemp;*/
// string to wide string(UNICODE)
/*std::wstring strtemp(className.begin(), className.end());
LPCWSTR classNamet = strtemp.c_str();*/

/*std::wstring strtemp = std::wstring(className.begin(), className.end());
LPCWSTR LWclassName = strtemp.c_str();
strtemp = std::wstring(caption.begin(), caption.end());
LPCWSTR LWcaptiont = strtemp.c_str();*/

// string to wide string(UNICODE)