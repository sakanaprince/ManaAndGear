#pragma once
#include <d2d1.h>
#include <windows.h>
#include <unordered_map>
#include "ArtKeys.h"
#include "Transform.h"

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

	void LoadArtFromSpriteSeat(ArtKeys artKey, LPCWSTR path, int x, int y, int width, int height);

	void DrawArt(ArtKeys key, D2D1_POINT_2F _pos);

	void DrawArtSlice(ArtKeys key, D2D1_POINT_2F _pos, float x, float y);

	void DrawHitBoxBrush(const Transform::Position& leftTop, const Transform::Position& rightBottom)const;

	D2D1_SIZE_F GetArtSize(ArtKeys artkey);

	void AllArtRelease();
};

