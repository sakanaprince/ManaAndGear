#pragma once
#include <unordered_map>

#include <d2d1.h>
#include <wincodec.h>
#include "ArtKeys.h"

class BitmapArt
{
private:
	ID2D1RenderTarget* pRenderTarget {nullptr};
	std::unordered_map<ArtKeys, ID2D1Bitmap*> pArtMapEnumType;

public:
	~BitmapArt()
	{
		AllArtRelease();
	}

	void Init(ID2D1RenderTarget* renderTargetPointer)
	{
		pRenderTarget = renderTargetPointer;
		ID2D1Bitmap* aaa;
	}

	void LoadArt(ArtKeys artKey, LPCWSTR path)
	{
		//同じキーを上書きしようとしたら
		auto it = pArtMapEnumType.find(artKey);

		if (it != pArtMapEnumType.end())
		{
			MessageBox(NULL, L"artKey(ここに番号を入れる)を上書きする！元登録されていた画像は消えた。", L"", 0);
		}

	

	}

	ID2D1Bitmap* GetArt(ArtKeys key)
	{
		auto it = pArtMapEnumType.find(key);

		if (it == pArtMapEnumType.end()) 
		{
			MessageBox(NULL, L"Art取得失敗", L"", 0);
			return nullptr;
		}

		return it->second;
	}

	void AllArtRelease()
	{
		//ポインタを指してるオブジェクト参照　をリリースってこと？
		for (auto& obj : pArtMapEnumType)
		{
			if (obj.second)
			{
				obj.second->Release();
				obj.second = nullptr;
			}
		}

		pArtMapEnumType.clear();
		MessageBox(NULL, L"アート解放した", L"", 1);
	}
 
};

