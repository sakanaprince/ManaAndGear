#include "FontText.h"

#include <iostream>
#include <algorithm>

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

void FontText::TextDrawTypewriterAuto(float outputDuration, float deltaTime, float x, float y, const wchar_t* text, D2D1_COLOR_F cl)
{
	_currentTime += deltaTime;
	if (_currentTime >= outputDuration)
	{
		_currentTime = 0.0f;
		_typewriterAutoCount++;
	}

	

	D2D1_RECT_F targetRect =
	{
		x,y,x + 1000, y + 500
	};

	pSolidColorBrush->SetColor(cl);


	UINT32 textMaxLength = static_cast<UINT32>(wcslen(text));
	 

	UINT32 drawTextCount = (std::min)(_typewriterAutoCount, textMaxLength);

	//ここの第二引数いじればタイプライター風に出来る説
	if (pSolidColorBrush) { _pRenderTarget->DrawTextW(text, drawTextCount, _pTextFormat, targetRect, pSolidColorBrush); }
}
