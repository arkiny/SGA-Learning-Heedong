#pragma once
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
class cGameMgr;
class cGameApplication
{
public:
	cGameApplication(cGameMgr*);
	virtual ~cGameApplication(void);

	bool Init(HINSTANCE hInstance, WCHAR* title, WCHAR* className, int nCmdShow);
	void Run();
	virtual void Update(float deltaTime);
	virtual void Render();
	
	virtual void Draw(HDC hdc){}
	HWND GetHWND(){return _hwnd;}
	static RECT _wndRect;
private:
	BOOL	InitInstance(HINSTANCE, int);
	ATOM	MyRegisterClass(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	HINSTANCE _hInst;								// 현재 인스턴스입니다.
	HWND _hwnd;
	TCHAR _szTitle[128];					// 제목 표시줄 텍스트입니다.
	TCHAR _szWindowClass[128];			// 기본 창 클래스 이름입니다.
	
	/// 애플리케이션의 현재 FPS(최근 1초)를 기억한다
	float _fps;
protected:
	
};

