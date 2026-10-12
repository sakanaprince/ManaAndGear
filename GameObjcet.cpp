#include "GameObjcet.h"
#include "BitmapArt.h"
#include "Utility.h"

void GameObject::Draw(ArtKeys artKey, Transform::Position setPosition)
{
	if (_pBitmapArt == nullptr)
	{
		Util::FatalError(L"初期化を忘れている！Bind関数をはじめに呼んで！");
		return;
	}

	_pBitmapArt->DrawArt(artKey, setPosition);


	//ManaAndGearをインクルードしたいけどそうするとwinMain複数定義になる
	//けどインクルードしないと_bitmapArtが使えない
	//自力解決！完成しているpBitmapArtのポインタを受け取ればそれを使える
}

void GameObject::Draw(ArtKeys artKey)
{
	if (_pBitmapArt == nullptr)
	{
		Util::FatalError(L"初期化を忘れている！Bind関数をはじめに呼んで！");
		return;
	}

	

	_pBitmapArt->DrawArt(artKey, transform.position);
}

void GameObject::DrawHitBox() const
{
	_pBitmapArt->DrawHitBox(hitBox.leftTopPosition, hitBox.rightBottomPosition);
}

void GameObject::DrawHitBox(const Transform::Position& leftTopPos, const Transform::Position& rightBottomPos) const
{
	_pBitmapArt->DrawHitBox(leftTopPos, rightBottomPos);
}



bool GameObject::IsHit_BoxBox(HitBox otherHitBox) const
{
	//AABB
	bool X_Hit = false;

	if (hitBox.leftTopPosition.x <= otherHitBox.rightBottomPosition.x
		&& hitBox.rightBottomPosition.x >= otherHitBox.leftTopPosition.x)
	{
		X_Hit = true;
	}
	else
	{
		//無駄な計算を省くために早期return
		return false;
	}

	bool Y_Hit = false;

	if (hitBox.leftTopPosition.y <= otherHitBox.rightBottomPosition.y
		&& hitBox.rightBottomPosition.y >= otherHitBox.leftTopPosition.y)
	{
		Y_Hit = true;
	}
	
	return X_Hit && Y_Hit;
}
