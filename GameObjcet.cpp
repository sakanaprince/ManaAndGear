#include "GameObjcet.h"
#include "BitmapArt.h"
#include "Utility.h"

void GameObject::Draw(ArtKeys artKey, Transform::Position position)
{
	if (_pBitmapArt == nullptr)
	{
		Util::FatalError(L"初期化を忘れている！Bind関数をはじめに呼んで！");
		return;
	}

	_pBitmapArt->DrawArt(artKey, position);


	//ManaAndGearをインクルードしたいけどそうするとwinMain複数定義になる
	//けどインクルードしないと_bitmapArtが使えない
	//自力解決！完成しているpBitmapArtのポインタを受け取ればそれを使える
}
