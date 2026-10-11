#pragma once
#include "Transform.h"
#include "ArtKeys.h"

class BitmapArt;

class GameObject
{
private:
	BitmapArt* _pBitmapArt{ nullptr };

public:
	Transform::Position position;

	void BindBitmapArt(BitmapArt* bitmapArt) { _pBitmapArt = bitmapArt; }

	/// <summary>
	/// ManaAndGearという実質的なmain関数で作成された_bitmapArtクラスを使って描画
	/// </summary>
	/// <param name="artKey"></param>
	/// <param name="position"></param>
	void Draw(ArtKeys artKey, Transform::Position position);
	
	
	
};

