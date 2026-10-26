#pragma once
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include "Utility.h"


#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class Time;

class FontText
{
private:
	ID2D1RenderTarget* _pRenderTarget{nullptr};
	IDWriteFactory* _writeFactory{nullptr};
	ID2D1SolidColorBrush* pSolidColorBrush;
	IDWriteTextFormat* _pTextFormat{nullptr};

	UINT32 _typewriterAutoCount{0};
	Time* _pTime{ nullptr };

public:

	void Init(ID2D1RenderTarget* render, Time* pTime);


	//同名の関数でオーバーロードすれば良い話に見えそうだけど初心者向けなので
	//ややこしく思わせないために別名で定義

	void TextDraw(float x, float y, const wchar_t* text, D2D1_COLOR_F cl = { 0.0f,0.0f,1.0f,1.0f });

	void TextDrawTypewriter(float x, float y, const wchar_t* text, D2D1_COLOR_F cl = { 0.0f,0.0f,1.0f,1.0f }, UINT32 typeCount = 1);

	//void TextDrawTypewriterAuto(float outputDuration, float x, float y, const wchar_t* text, D2D1_COLOR_F cl = { 0.0f,0.0f,1.0f,1.0f });

	
	~FontText()
	{
		if (pSolidColorBrush) 
		{ 
			pSolidColorBrush->Release();
			pSolidColorBrush = nullptr;
		}
	}
};

