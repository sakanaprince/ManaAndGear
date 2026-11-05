#include "FontText.h"
#include "Time.h"

#include <iostream>
#include <algorithm>

void FontText::Init(ID2D1RenderTarget* render, Time* pTime)
{
	_pRenderTarget = render;
	_pTime = pTime;

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
		30.0f,
		L"en-us",
		&_pTextFormat
	);

	HRESULT result = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 1.0f, 1.0f), &pSolidColorBrush);

	if (Util::IsNG(result)) { Util::FatalError(L"FontText:solidColorBrush作成失敗"); }
}

void FontText::TextDraw(float x, float y, const wchar_t* text, D2D1_COLOR_F cl)
{
	D2D1_RECT_F targetRect =
	{
		x,y,x + 1000, y + 500
	};

	pSolidColorBrush->SetColor(cl);


	UINT32 textLength = static_cast<UINT32>(wcslen(text));

	//ここの第二引数いじればタイプライター風に出来る説
	if (pSolidColorBrush) { _pRenderTarget->DrawTextW(text, textLength, _pTextFormat, targetRect, pSolidColorBrush); }

}

void FontText::TextDrawTypewriter(float x, float y, const wchar_t* text, D2D1_COLOR_F cl, UINT32 typeCount)
{
	D2D1_RECT_F targetRect =
	{
		x,y,x + 1000, y + 500
	};

	pSolidColorBrush->SetColor(cl);


	UINT32 textMaxLength = static_cast<UINT32>(wcslen(text));

	//個人メモ：マクロ展開を防ぐために()する　std::((num ? num))みたいなことに
	UINT32 drawTextCount = (std::min)(typeCount, textMaxLength);

	//ここの第二引数いじればタイプライター風に出来る説
	if (pSolidColorBrush) { _pRenderTarget->DrawTextW(text, drawTextCount, _pTextFormat, targetRect, pSolidColorBrush); }

}