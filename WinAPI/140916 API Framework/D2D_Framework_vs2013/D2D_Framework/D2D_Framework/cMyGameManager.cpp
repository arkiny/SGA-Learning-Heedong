#include "StdAfx.h"
#include "cMyGameManager.h"
//#include "cPlayer.h"

cMyGameManager::cMyGameManager(void)
:x(0), y(0), m_fAngle(0.0f), m_fAlpha(1.0f)
{
	m_ipD2DBitmapBG = nullptr;
	m_ipD2DBitmap = nullptr;
}


cMyGameManager::~cMyGameManager(void)
{
	SafeRelease(m_ipD2DBitmapBG);
	SafeRelease(m_ipD2DBitmap);
}


void cMyGameManager::OnInit(cD2DRenderer& renderer)
{
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmapBG = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Tulips.jpg");
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/ccc.png");

}

void cMyGameManager::Render(cD2DRenderer& renderer)
{

	if (m_ipD2DBitmapBG != nullptr)
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(0.0f, 0.0f, static_cast<float>(size.width), static_cast<float>(size.height));
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 1024.0f, 768.0f);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapBG, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	if (m_ipD2DBitmap != nullptr)
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y, x + 100.0f, y + 100.0f);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

		D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
		renderer.GetRenderTarget()->SetTransform(rot);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_fAlpha,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}


	if (m_ipD2DBitmap != nullptr)
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y + 100.0f, x + 100.0f, y + 200.0f);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

		//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
		//renderer.GetRenderTarget()->SetTransform(rot);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	wchar_t* wszText_ = L"Hello World using  DirectWrite!";
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		100,
		300,
		800,
		400
		);

	renderer.GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		renderer.GetTextFormat(),
		layoutRect,
		renderer.GetBrush());
}

void cMyGameManager::Update(float deltaTime)
{
	// 게임의 업데이트 처리
	x += deltaTime* 50.0f;

	m_fAngle += 10.0f;

	m_fAlpha -= 0.1f;
	if (m_fAlpha <= 0.0f)
		m_fAlpha = 1.0f;
}

void cMyGameManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 키 컨트롤 처리
	switch (message)
	{	
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		return;

	}
}