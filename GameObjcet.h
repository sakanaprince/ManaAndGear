#pragma once
#include "Transform.h"
#include "ArtKeys.h"

class BitmapArt;

class GameObject
{
private:
	BitmapArt* _pBitmapArt{ nullptr };

public:
	GameObject() = default;
	GameObject(float _x, float _y) : transform(_x, _y) {};


	//直感的に使えるようにあえてpublicにしているposition
	Transform transform;


	void BindBitmapArt(BitmapArt* bitmapArt) { _pBitmapArt = bitmapArt; }

	/// <summary>
	/// ManaAndGearという実質的なmain関数で作成された_bitmapArtクラスを使って描画
	/// </summary>
	/// <param name="artKey"></param>
	/// <param name="position"></param>
	void Draw(ArtKeys artKey, Transform::Position setPosition);
	void Draw(ArtKeys artKey);
	
	
	
};

