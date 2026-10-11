#pragma once
#include "HitBox.h"
#include "ArtKeys.h"

class BitmapArt;

class GameObject
{
private:
	BitmapArt* _pBitmapArt{ nullptr };

public:
	//GameObject宣言時に初期座標を指定できるように

	GameObject() = default;
	GameObject(float _x, float _y) : transform(_x, _y) {};

	//直感的に使えるようにあえて,publicにしている
	Transform transform;
	HitBox hitBox;


	void BindBitmapArt(BitmapArt* bitmapArt) { _pBitmapArt = bitmapArt; }

	/// <summary>
	/// ManaAndGearという実質的なmain関数で作成された_bitmapArtクラスを使って描画
	/// </summary>
	/// <param name="artKey"></param>
	/// <param name="position"></param>
	void Draw(ArtKeys artKey, Transform::Position setPosition);
	void Draw(ArtKeys artKey);


	bool IsHitBox(HitBox otherHitBox) const;
	
	
	
};

