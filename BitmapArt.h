#pragma once
#include <d2d1.h>
#include <windows.h>
#include <unordered_map>
#include "ArtKeys.h"

class IWICImagingFactory;

class BitmapArt
{
private:
	ID2D1RenderTarget* _pRenderTarget {nullptr};
	IWICImagingFactory* _pWICImagingFactory{ nullptr };
	std::unordered_map<ArtKeys, ID2D1Bitmap*> _pArtMapEnumType;

public:
	~BitmapArt() { AllArtRelease(); }

	void Init(ID2D1RenderTarget* renderTargetPointer, IWICImagingFactory* WICImagingFactoryPointer);

	void LoadArt(ArtKeys artKey, LPCWSTR path);

	void DrawArt(ArtKeys key, D2D1_POINT_2F _pos);

	void AllArtRelease();
 
};

