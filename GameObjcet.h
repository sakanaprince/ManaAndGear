#pragma once
#include "HitBox.h"
#include "ArtKeys.h"
#include <memory>

class BitmapArt;

class GameObject
{
private:
	inline static BitmapArt* _pBitmapArt{ nullptr };
	ArtKeys _art{};
	SpriteSeatKeys _spriteSeat{};
	bool _active{ true };
	bool _animeMode{ false };

	float _animationTimer{ 0.0f };
	float _animationDuration{ 0.1f };
	//ディープコピー とか　あさいコピーとかが存在する
	//ディープがしっかりコピー　unity Prefab的な
	//あさいコピーが参照？的なイメージ　（*EnemySlimeStatusをEnemySlimeが参照する的な、
	// EnemySlimeが持っているEnemySlimeStatusを変更すると全員変更されてしまう！）

protected:

public:


	GameObject();
	//GameObject宣言時に初期座標を指定できるように
	GameObject(float _x, float _y);

	GameObject(const GameObject& other);

	//座標や当たり判定など、よく使う変数
	//これらは初心者の人にとって直感的に使えるように、あえて publicにしている
	Transform transform;
	HitBox hitBox;
	int _animeIndex{ 0 };
	float _animationSpeed{ 1.0f };
	bool _isHitBoxDraw{ false };

	void AnimationUpdate(float deltaTime);


	void SetArt(ArtKeys artKey) { _art = artKey; }

	void SetSpriteSeat(SpriteSeatKeys spriteSeatKey) { _spriteSeat = spriteSeatKey; }


	/// <summary>
	/// ArtKeysの中に読み込まれている画像をsetPositionの位置に描画
	/// </summary>
	/// <param name="artKey">ArtKeys::って入れたら出てくるよ</param>
	/// <param name="position">とりあえず描画するなら{}に好きな数を入れると良いかも。例{10,50}</param>
	void Draw(ArtKeys artKey, Transform::Position setPosition) const;

	/// <summary>
	/// ArtKeysの中に読み込まれている画像を自身の座標の位置に描画する
	/// </summary>
	/// <param name="artKey"></param>
	void Draw(ArtKeys artKey) const;

	void Draw_FromGameObjectManager()const;

	/// <summary>
	/// 当たり判定を描画
	/// </summary>
	/// <returns>s</returns>
	void const DrawHitBox() const;

	/// <summary>
	/// 指定された値で"四角の当たり判定"を描画
	/// </summary>
	/// <param name="leftTopPos">四角の左上の場所</param>
	/// <param name="rightBottomPos">四角の右下の場所</param>
	void DrawHitBox(const Transform::Position& leftTopPos, const Transform::Position& rightBottomPos)const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="otherHitBox"></param>
	/// <returns>当たったらtrue、当たらなかったらfalseになります</returns>
	bool IsHit_BoxBox(HitBox otherHitBox) const;

	//アクセサー(boolはIsにしてます)
	void SetActive(const bool active) { _active = active; }
	bool const IsActive() const { return _active; }
	void SetAnimationMode(const bool animeOn) { _animeMode = animeOn; }
	bool const IsAnimationMode()const { return _animeMode; }
	void SetAnimationSpeed(const float speed) { _animationSpeed = speed; }


	/// <summary>
	/// 実装してくれてありがとう！
	/// </summary>
	/// <returns></returns>
	virtual GameObject* Clone(Transform initTransform) = 0;

	virtual void Update() = 0;
	virtual void OnCloneDelated() = 0;

	/// <summary>
	/// 【おねがい】この関数は使わないで！
	/// </summary>
	/// <param name="setPBitmapArt">すでに作者が必要な機能をセット済み</param>
	static void BindBitMapArt(BitmapArt* setPBitmapArt)
	{
		if (_pBitmapArt)
		{
			MessageBox(NULL, L"BindBitMapArtのBinBitMapArtは使わないで欲しいっていったじゃん！！泣", L"泣いてる", 0);
			return;
		}
		_pBitmapArt = setPBitmapArt;
	}

};