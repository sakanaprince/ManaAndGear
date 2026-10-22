#pragma once
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include "Utility.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
class FontText
{
private:
	ID2D1RenderTarget* _pRenderTarget{nullptr};
	IDWriteFactory* _writeFactory{nullptr};

	IDWriteTextFormat* _pTextFormat{nullptr};

public:
	void Init(ID2D1RenderTarget* render)
	{
		_pRenderTarget = render;

		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&_writeFactory));

		//writeFactoryがフォーマットを作成
		_writeFactory->CreateTextFormat(
			L"Gabriola",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			72.0f,
			L"en-us",
			&_pTextFormat
		);
	}

	void TextDraw(float x, float y, const wchar_t* text)
	{
		ID2D1SolidColorBrush* pSolidColorBrush;
		_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 1.0f, 1.0f), &pSolidColorBrush);


	

		HRESULT result = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 1.0f, 1.0f), &pSolidColorBrush);

		if (Util::IsNG(result)) { Util::FatalError(L"FontText:solidColorBrush作成失敗"); }

		D2D1_RECT_F targetRect =
		{
			x,y,x + 1000, y + 500
		};

		if(pSolidColorBrush){ _pRenderTarget->DrawTextW(text, 512, _pTextFormat, targetRect, pSolidColorBrush); }

		if (pSolidColorBrush) { pSolidColorBrush->Release(); }
		
	}
};

