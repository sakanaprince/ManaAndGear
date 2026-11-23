#include "BitmapArt.h"

#include <wincodec.h>
#include "Utility.h"

void BitmapArt::Init(ID2D1RenderTarget* renderTargetPointer, IWICImagingFactory* WICImagingFactoryPointer)
{
	_pRenderTarget = renderTargetPointer;
	_pWICImagingFactory = WICImagingFactoryPointer;
	_pArtMapEnumType.clear();
}

void BitmapArt::LoadArt(ArtKeys artKey, LPCWSTR path)
{
	//同じキーを上書きしようとしたら警告出す
	auto it = _pArtMapEnumType.find(artKey);

	if (it != _pArtMapEnumType.end()) { MessageBox(NULL, L"artKey(ここに番号を入れる)を上書きする！元登録されていた画像は消えた。", L"", 0); }

	IWICBitmapDecoder* pBitmapDecoder = nullptr;

	HRESULT createDecoderResult = _pWICImagingFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pBitmapDecoder);
	if (Util::IsNG(createDecoderResult)) { Util::FatalError(L"BitmapArt:デコードできんかった"); }

	IWICBitmapFrameDecode* pFrameDecode = nullptr;

	HRESULT getFrameResult = pBitmapDecoder->GetFrame(0, &pFrameDecode);
	if (Util::IsNG(getFrameResult)) { Util::FatalError(L"BitmapArt:フレーム取得出来なかった"); }

	//【はぁ】昔の書き方も試して**にしたけど警告が
	IWICFormatConverter* pFormatConverter = nullptr;

	HRESULT formatConverterResult = _pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
	if (Util::IsNG(formatConverterResult)) { Util::FatalError(L"コンバーター作成失敗"); }


	//ここの第一引数ぬまった、多分引数は親クラスなので一族ならなんでもokというルールだった
	//全く同じ型が見つからず困惑してた
	HRESULT convInitResult = pFormatConverter->Initialize(
		pFrameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);
	if (Util::IsNG(convInitResult)) { Util::FatalError(L"BitmapArt:FormatConverter初期化失敗"); }
	
	HRESULT bitMapCreateResult = _pRenderTarget->CreateBitmapFromWicBitmap(
		pFormatConverter, nullptr, &_pArtMapEnumType[artKey]);
	if (Util::IsNG(bitMapCreateResult)) { Util::FatalError(L"BitmapArt:bitMap作成失敗"); }

	pFormatConverter->Release();
	pFrameDecode->Release();
	pBitmapDecoder->Release();
}

void BitmapArt::LoadSingleArtFromSpriteSeat(ArtKeys artKey, LPCWSTR path, int x, int y, int width, int height)
{
	//同じキーを上書きしようとしたら警告出す
	auto it = _pArtMapEnumType.find(artKey);

	if (it != _pArtMapEnumType.end()) { MessageBox(NULL, L"artKey(ここに番号を入れる)を上書きする！元登録されていた画像は消えた。", L"", 0); }

	IWICBitmapDecoder* pBitmapDecoder = nullptr;

	HRESULT createDecoderResult = _pWICImagingFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pBitmapDecoder);
	if (Util::IsNG(createDecoderResult)) { Util::FatalError(L"BitmapArt:デコードできんかった"); }

	IWICBitmapFrameDecode* pFrameDecode = nullptr;

	HRESULT getFrameResult = pBitmapDecoder->GetFrame(0, &pFrameDecode);
	if (Util::IsNG(getFrameResult)) { Util::FatalError(L"BitmapArt:フレーム取得出来なかった"); }

	WICRect clipRect = { x,y,width,height };

	IWICBitmapClipper* pClipper = nullptr;

	HRESULT createBitmapClipperResult = _pWICImagingFactory->CreateBitmapClipper(&pClipper);
	if (Util::IsNG(createBitmapClipperResult)) { Util::FatalError(L"BitmapArt:WICFactoryからpClipper作成できんかった"); }

	HRESULT clipperInitialize = pClipper->Initialize(pFrameDecode, &clipRect);
	if (Util::IsNG(clipperInitialize)) { Util::FatalError(L"クリッパー作成失敗"); }

	//【はぁ】昔の書き方も試して**にしたけど警告が
	IWICFormatConverter* pFormatConverter = nullptr;

	HRESULT formatConverterResult = _pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
	if (Util::IsNG(formatConverterResult)) { Util::FatalError(L"コンバーター作成失敗"); }


	//ここの第一引数ぬまった、多分引数は親クラスなので一族ならなんでもokというルールだった
	//全く同じ型が見つからず困惑してた
	HRESULT convInitResult = pFormatConverter->Initialize(
		pClipper,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);
	if (Util::IsNG(convInitResult)) { Util::FatalError(L"BitmapArt:FormatConverter初期化失敗"); }

	HRESULT bitMapCreateResult = _pRenderTarget->CreateBitmapFromWicBitmap(
		pFormatConverter, nullptr, &_pArtMapEnumType[artKey]);
	if (Util::IsNG(bitMapCreateResult)) { Util::FatalError(L"BitmapArt:bitMap作成失敗"); }

	pFormatConverter->Release();
	pFrameDecode->Release();
	pBitmapDecoder->Release();
}

void BitmapArt::LoadSpriteSeat(SpriteSeatKeys seatKey, LPCWSTR path, int frameCountX, int frameCountY, int startX, int startY, int width, int height)
{
	//同じキーを上書きしようとしたら警告出す
	auto it = _SpriteSeatMapEnumType.find(seatKey);

	if (it != _SpriteSeatMapEnumType.end()) { MessageBox(NULL, L"seatKey(ここに番号を入れる)を上書きする！元登録されていたシート画像は消えた。", L"", 0); }

	//安全のためにリストを空にしておく
	_SpriteSeatMapEnumType[seatKey].spritsVector.clear();

	IWICBitmapDecoder* pBitmapDecoder = nullptr;

	HRESULT createDecoderResult = _pWICImagingFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pBitmapDecoder);
	if (Util::IsNG(createDecoderResult)) { Util::FatalError(L"BitmapArt:デコードできんかった"); }

	IWICBitmapFrameDecode* pFrameDecode = nullptr;

	HRESULT getFrameResult = pBitmapDecoder->GetFrame(0, &pFrameDecode);
	if (Util::IsNG(getFrameResult)) { Util::FatalError(L"BitmapArt:フレーム取得出来なかった"); }

	//まずfor文の準備がいるなぁ
	for (int y = 0; y < frameCountY; y++)
	{
		for (int x = 0; x < frameCountX; x++)
		{
			WICRect clipRect = { x * width,y * height,width,height };

			IWICBitmapClipper* pClipper = nullptr;

			HRESULT createBitmapClipperResult = _pWICImagingFactory->CreateBitmapClipper(&pClipper);
			if (Util::IsNG(createBitmapClipperResult)) { Util::FatalError(L"BitmapArt:WICFactoryからpClipper作成できんかった"); }

			HRESULT clipperInitialize = pClipper->Initialize(pFrameDecode, &clipRect);
			if (Util::IsNG(clipperInitialize)) { Util::FatalError(L"クリッパー作成失敗"); }

			//【はぁ】昔の書き方も試して**にしたけど警告が
			IWICFormatConverter* pFormatConverter = nullptr;

			HRESULT formatConverterResult = _pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
			if (Util::IsNG(formatConverterResult)) { Util::FatalError(L"コンバーター作成失敗"); }

			//ここの第一引数ぬまった、多分引数は親クラスなので一族ならなんでもokというルールだった
			//全く同じ型が見つからず困惑してた
			HRESULT convInitResult = pFormatConverter->Initialize(
				pClipper,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);
			if (Util::IsNG(convInitResult)) { Util::FatalError(L"BitmapArt:FormatConverter初期化失敗"); }

			ID2D1Bitmap *bitmap = nullptr;

			//bitmapに貯めておいて
			HRESULT bitMapCreateResult = _pRenderTarget->CreateBitmapFromWicBitmap(
				pFormatConverter, nullptr, &bitmap);
			if (Util::IsNG(bitMapCreateResult)) { Util::FatalError(L"BitmapArt:bitMap作成失敗"); }

			//ここでvectorに入れる
			_SpriteSeatMapEnumType[seatKey].spritsVector.push_back(bitmap);

			pFormatConverter->Release();
			//bitmap->Release();
		}
	}

	pFrameDecode->Release();
	pBitmapDecoder->Release();
}

void BitmapArt::DrawArt(ArtKeys key, D2D1_POINT_2F _pos)
{
	auto it = _pArtMapEnumType.find(key);

	if (it == _pArtMapEnumType.end())
	{
		MessageBox(NULL, L"Art取得失敗", L"", 0);
		return;
	}
	
	if(it->second == nullptr){ MessageBox(NULL, L"NULLじゃね", L"", 0); }

	D2D1_SIZE_F artSize = it->second->GetSize();

	D2D1_RECT_F drawTargetRect = D2D1::RectF(
		_pos.x, _pos.y, _pos.x + artSize.width, _pos.y + artSize.height);

	_pRenderTarget->DrawBitmap(it->second, drawTargetRect, 1.0f);
}

void BitmapArt::DrawArtSlice(ArtKeys key, D2D1_POINT_2F _pos, float x, float y)
{
	auto it = _pArtMapEnumType.find(key);

	if (it == _pArtMapEnumType.end())
	{
		MessageBox(NULL, L"Art取得失敗", L"", 0);
		return;
	}

	if (it->second == nullptr) { MessageBox(NULL, L"NULLじゃね", L"", 0); }

	D2D1_SIZE_F artSize = it->second->GetSize();

	D2D1_RECT_F drawTargetRect = D2D1::RectF(
		_pos.x, _pos.y, _pos.x + artSize.width * 0.5f, _pos.y + artSize.height);

	_pRenderTarget->DrawBitmap(it->second, drawTargetRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, drawTargetRect);
}

void BitmapArt::DrawSpriteSeat(SpriteSeatKeys key, int idx, D2D1_POINT_2F _pos)
{
	auto it = _SpriteSeatMapEnumType.find(key);

	if (it == _SpriteSeatMapEnumType.end())
	{
		MessageBox(NULL, L"Art取得失敗", L"", 0);
		return;
	}

	if (idx < 0 || it->second.spritsVector.size() <= idx) { return; }

	auto bitmap = it->second.spritsVector[idx];

	if (bitmap == nullptr) 
	{ 
		MessageBox(NULL, L"NULLじゃね", L"", 0); 
		return;
	}

	if (bitmap != nullptr)
	{
		D2D1_SIZE_F artSize = bitmap->GetSize();

		D2D1_RECT_F drawTargetRect = D2D1::RectF(
			_pos.x, _pos.y, _pos.x + artSize.width, _pos.y + artSize.height);

		_pRenderTarget->DrawBitmap(bitmap, drawTargetRect, 1.0f);
	}

	//bitmap->Release();
}

void BitmapArt::DrawHitBoxBrush(const Transform::Position& leftTop, const Transform::Position& rightBottom) const
{
	ID2D1SolidColorBrush* pColorBrush{ nullptr };

	HRESULT createResult = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.9f, 0.2f, 0.2f), &pColorBrush);

	if (Util::IsNG(createResult)) { Util::FatalError(L"BitMapArtのcolorBrush作成失敗"); }

	if (pColorBrush)
	{
		//LEFT TOP RIGHT BOTTOMの順です
		D2D1_RECT_F rect = { leftTop.x,leftTop.y,rightBottom.x,rightBottom.y };
		_pRenderTarget->DrawRectangle(rect, pColorBrush,5.0f);

		pColorBrush->Release();
		pColorBrush = nullptr;
	}
}

D2D1_SIZE_F BitmapArt::GetArtSize(ArtKeys artkey)
{
	auto it = _pArtMapEnumType.find(artkey);

	if (it == _pArtMapEnumType.end())
	{
		MessageBox(NULL, L"Art取得失敗(先にLoadArtで登録しないと...)", L"", 0);
		return {0,0};
	}

	return it->second->GetSize();
}




void BitmapArt::AllArtRelease()
{
	//ポインタを指してるオブジェクト参照　をリリースってこと？
	for (auto& obj : _pArtMapEnumType)
	{
		if (obj.second)
		{
			obj.second->Release();
			obj.second = nullptr;
			//MessageBox(NULL, L"アート解放した", L"", 1);
		}
	}

	for (auto& obj : _SpriteSeatMapEnumType)
	{
		for (auto& art : obj.second.spritsVector)
		{
			if (art)
			{
				art->Release();
				art = nullptr;
				//MessageBox(NULL, L"スプライトシートからのアート解放した", L"", 1);
			}
		}
		
	}

	_pArtMapEnumType.clear();
}
