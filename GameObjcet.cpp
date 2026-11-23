#include "GameObjcet.h"
#include "BitmapArt.h"
#include "Utility.h"
#include "GameObjectManager.h"

GameObject::GameObject()
{
	GameObjectManager::GetInstance().AddListGameObject(*this);
}

GameObject::GameObject(float _x, float _y) : transform(_x, _y)
{
	GameObjectManager::GetInstance().AddListGameObject(*this);
}

GameObject::GameObject(const GameObject& other)
:transform(other.transform.position.x, other.transform.position.y)
{
	GameObjectManager::GetInstance().AddCloneGameObject(*this);
}

void GameObject::AnimationUpdate(float deltaTime)
{
	_animationTimer += _animationSpeed * deltaTime;

	if (_animationTimer >= _animationDuration)
	{
		_animationTimer = 0.0f;
		_animeIndex = (_animeIndex + 1) % _pBitmapArt->GetSpriteSeatVectorSize(_spriteSeat);
		int a = 0;
	}

}

void GameObject::Draw(ArtKeys artKey, Transform::Position setPosition) const
{
	if (_pBitmapArt == nullptr)
	{
		Util::FatalError(L"pBitmapArtがnullptrだBind関数が呼ばれていないかも\nライブラリの不具合です。ごめんなさい。");
		return;
	}

	_pBitmapArt->DrawArt(artKey, setPosition);


	//ManaAndGearをインクルードしたいけどそうするとwinMain複数定義になる
	//けどインクルードしないと_bitmapArtが使えない
	//自力解決！完成しているpBitmapArtのポインタを受け取ればそれを使える
}

void GameObject::Draw(ArtKeys artKey) const
{
	if (_pBitmapArt == nullptr)
	{
		Util::FatalError(L"pBitmapArtがnullptrだBind関数が呼ばれていないかも\nライブラリの不具合です。ごめんなさい。");
		return;
	}

	_pBitmapArt->DrawArt(artKey, transform.position);
}

void GameObject::Draw_FromGameObjectManager() const
{
	if (_pBitmapArt == nullptr)
	{
		Util::FatalError(L"pBitmapArtがnullptrだBind関数が呼ばれていないかも\nライブラリの不具合です。ごめんなさい。");
		return;
	}

	if (_animeMode)
	{
		_pBitmapArt->DrawSpriteSeat(_spriteSeat,_animeIndex,transform.position);
	}
	else
	{
		_pBitmapArt->DrawArt(_art, transform.position);
	}

	if (!_isHitBoxDraw) { return; }
	
	_pBitmapArt->DrawHitBoxBrush(hitBox.leftTopPosition, hitBox.rightBottomPosition);
}

void const GameObject::DrawHitBox() const
{	
	_pBitmapArt->DrawHitBoxBrush(hitBox.leftTopPosition, hitBox.rightBottomPosition);	
}


void GameObject::DrawHitBox(const Transform::Position& leftTopPos, const Transform::Position& rightBottomPos) const
{
	_pBitmapArt->DrawHitBoxBrush(leftTopPos, rightBottomPos);
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
