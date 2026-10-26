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
	ID2D1SolidColorBrush* pSolidColorBrush;
	IDWriteTextFormat* _pTextFormat{nullptr};

	float _currentTime{ 0.0f };
	UINT32 _typewriterAutoCount{0};

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
			30.0f,
			L"en-us",
			&_pTextFormat
		);

		HRESULT result = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 1.0f, 1.0f), &pSolidColorBrush);

		if (Util::IsNG(result)) { Util::FatalError(L"FontText:solidColorBrush作成失敗"); }
	}


	//同名の関数でオーバーロードすれば良い話に見えそうだけど初心者向けなので
	//ややこしく思わせないために別名で定義

	void TextDraw(float x, float y, const wchar_t* text, D2D1_COLOR_F cl = { 0.0f,0.0f,1.0f,1.0f });

	void TextDrawTypewriter(float x, float y, const wchar_t* text, D2D1_COLOR_F cl = { 0.0f,0.0f,1.0f,1.0f }, UINT32 typeCount = 1);

	void TextDrawTypewriterAuto(float outputDuration, float deltaTime, float x, float y, const wchar_t* text, D2D1_COLOR_F cl = { 0.0f,0.0f,1.0f,1.0f });

	
	~FontText()
	{
		if (pSolidColorBrush) 
		{ 
			pSolidColorBrush->Release();
			pSolidColorBrush = nullptr;
		}
	}
};

