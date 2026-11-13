#pragma once
#include <d2d1.h>
#include <windows.h>
#include <unordered_map>
#include "ArtKeys.h"
#include "Transform.h"

#include <vector>

class IWICImagingFactory;

/// <summary>
/// ここでspriteSeatKeyのn番目のコマを取得って出来たら最高
/// </summary>
struct SpriteSeat
{
	SpriteSeatKeys spriteSeatKey;
	std::vector<ID2D1Bitmap*> spritsVector;
};


class BitmapArt
{
private:
	ID2D1RenderTarget* _pRenderTarget {nullptr};
	IWICImagingFactory* _pWICImagingFactory{ nullptr };
	std::unordered_map<ArtKeys, ID2D1Bitmap*> _pArtMapEnumType;
	std::unordered_map<SpriteSeatKeys, SpriteSeat> _SpriteSeatMapEnumType;

public:
	~BitmapArt() { AllArtRelease(); }

	void Init(ID2D1RenderTarget* renderTargetPointer, IWICImagingFactory* WICImagingFactoryPointer);

	void LoadArt(ArtKeys artKey, LPCWSTR path);

	/// <summary>
	/// スプライトシートから範囲を指定して一枚の絵として使う
	/// </summary>
	/// <param name="artKey"></param>
	/// <param name="path">ファイルのパス　例=> ./Data/art.png</param>
	/// <param name="x">その画像の左上からいくつ右を始点にする</param>
	/// <param name="y">その画像の左上からいくつ下を始点にする</param>
	/// <param name="width">始点から右側いくらを取る</param>
	/// <param name="height">始点から下側いくらを取る</param>
	void LoadSingleArtFromSpriteSeat(ArtKeys artKey, LPCWSTR path, int x, int y, int width, int height);

	void LoadSpriteSeat(SpriteSeatKeys seatKey, LPCWSTR path, int frameCountX, int frameCountY,
		int startX, int startY, int width, int height);

	void DrawArt(ArtKeys key, D2D1_POINT_2F _pos);

	void DrawArtSlice(ArtKeys key, D2D1_POINT_2F _pos, float x, float y);

	void DrawSpriteSeat(SpriteSeatKeys key, int idx, D2D1_POINT_2F _pos);

	void DrawHitBoxBrush(const Transform::Position& leftTop, const Transform::Position& rightBottom)const;

	D2D1_SIZE_F GetArtSize(ArtKeys artkey);

	int GetSpriteSeatVectorSize(SpriteSeatKeys key)
	{
		return _SpriteSeatMapEnumType[key].spritsVector.size();
	}

	void AllArtRelease();
};

