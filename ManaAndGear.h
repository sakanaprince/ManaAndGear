#pragma once
#include <windows.h>
#include <d2d1.h>
#include <wincodec.h> //デコード、pngとか画像ファイルを扱うのに必要らしい

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


//わしのクラス
#include "COMRelease.h"
#include "BitmapArt.h"
#include "Utility.h"
#include "Transform.h"
#include "GameObjcet.h"
#include "GameInput.h"
#include "GameObjectManager.h"
#include "FontText.h"
#include "Time.h"

//DxLibの設定の時に「追加の○○ディレクトリ」的なのを設定していたけれど要はこれみたい
//ライブラリディレクトリとインクルードディレクトリは別物でした...DxLibはコード内でpragma commmentしてくれてる
//自分のプロジェクトファイル内に存在しないクラスを使おうとしている時に必要らしい

//【外部のライブラリを使用】
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")


#define World_WakeUp  void UserInit()
#define World_Start  void UserStart()
#define World_FirstUpdate void UserUpdate(double deltaTime)
#define World_SecondUpdate void UserUI_Update(double deltaTime)

//ユーザーに書いてもらう
void UserInit();
void UserStart();
void UserUpdate(double deltaTime);
void UserUI_Update(double deltaTime);


namespace ManaAndGear
{
    //TODO:クラスで隠せ、でなきゃ外部参照されて予測変換邪魔で作業にならない
    //1. 2.とかついてんのはAI、この口調がおれが書いたやつ
    COMRelease _componentRelease;
    BitmapArt  _bitmapArt;
    GameInput _gameInput;
    Time _time;

    namespace UI
    {
        FontText fontText;
    }
  

    //【1】最低限いるやつ　windows側で用意されてるからこっちから実体は作れない（ポインタのみ）
    ID2D1Factory* pFactory = nullptr;
    
    //【2】Handle Windowsみたいなこと言ってるからウィンドウ関連でこいつはBitmapArtに渡す
    ID2D1HwndRenderTarget* pRenderTarget = nullptr;
    
    //色の描画らしい（未使用なので消した）colorブラシ
    
    //DEL【3】Windows imaging component工場
    IWICImagingFactory* pWICFactory = nullptr;
    
    //【4】デコーダー
    IWICBitmapDecoder* pDecoder = nullptr;
    
    //【5】画像ハンドル的な？
    IWICBitmapFrameDecode* pFrameDecode_testArt = nullptr;
    
    //【6】こんばーたー
    IWICFormatConverter* pConverter = nullptr;
    
    //DEL【7】こいつが画像ハンドルです皆さん！！！！！！！！！！！
    ID2D1Bitmap* pBitmap_testArt = nullptr;

}

using namespace ManaAndGear;
using namespace ManaAndGear::UI;

//あんしん　おなじみ　だいすき
const float playerSpeed = 5.0f;


// 描画処理のごく普通の関数！！
const static void Render()
{
    //ポインタがnullならやりようがないのでreturn
    if (!pRenderTarget) { return; }

    //公式リファレンスを見れば分かる（意外といけるよw）
    pRenderTarget->BeginDraw();

    // 画面を暗いグレーでクリア
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateGray));

    //実は座標は4,294,967,295になっている。UINTにfloatマイナスが暗黙の変換になるから...

     //神便利画像サイズ取得関数
    D2D1_SIZE_F artSize = pBitmap_testArt->GetSize();

    D2D1_RECT_F drawTargetRect = D2D1::RectF(
        0,
        0,
        0 + artSize.width,
        0 + artSize.height);

    //pRenderTarget->DrawBitmap(pBitmap_testArt, drawTargetRect, 1.0f);

    _bitmapArt.DrawArt(ArtKeys::ArtNumber1, {100,50});

    //Beginで始まるEndで終わる
    pRenderTarget->EndDraw();
}

// ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SIZE:
    {
        //下位16ビットor上位16ビットを見てるらしい、10進数で頼むわ...
        UINT width = LOWORD(lParam);
        UINT height = HIWORD(lParam);
        if (pRenderTarget)
        {
            pRenderTarget->Resize(D2D1::SizeU(width, height));
        }
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// エントリポイント 
// _In_とかは注釈　まぁ...なんていうの？セマンティクス的な？？注釈は注釈なんだよぉ...
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    //=====メモリリーク検知の設定======
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif 

    D2D1_FACTORY_OPTIONS factoryOptions = {};

    //詳細にデバッグログを出す設定
    factoryOptions.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
    //=====メモリリーク検知の設定======

    // 1. Direct2D ファクトリの作成　　　　　　　　　　　↓デバッグ出るように設定
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factoryOptions, &pFactory);
    _componentRelease.AddReleaseTarget(pFactory);

    using namespace Util;

    //コンポーネント初期化（1引数にはNULLを送れだとよ...公式がそういった。まるちすれっどの方が得そうなので選択)
    //追記　まるちすれっど危ないみたい
    HRESULT coInitializeResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (IsNG(coInitializeResult)) { FatalError(L"コンポーネントオブジェクト初期化失敗"); }
    

    // 2. ウィンドウクラスの登録
    const wchar_t CLASS_NAME[] = L"Direct2DGameWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // 3. ウィンドウの作成
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Direct2D 2D Game Base",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd) { FatalError(L"hwndが上手く作られなかった"); }

    // 4. レンダーターゲット（描画先）の作成
    RECT rc;
    GetClientRect(hwnd, &rc);

    HRESULT renderTargetCreateResult = pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
        &pRenderTarget
    );

    if (IsNG(renderTargetCreateResult)) { FatalError(L"renderTarget作成失敗"); }
    _componentRelease.AddReleaseTarget(pRenderTarget);

    //引数わかんなすぎてここAiにきいた
    HRESULT coCreateResult = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pWICFactory)
    );

    if (IsNG(coCreateResult)) { FatalError(L"インスタンス生成失敗"); }
    _componentRelease.AddReleaseTarget(pWICFactory);

    /*
    1=>見たまま
    2=>識別子はおすすめに任せ
    3=>読み込むために使うという意志表明(読み取り専用)
    4=>どのタイミングでキャッシュをするか
    5=>デコーダーのポインタのアドレスを求められている(**ともいえる)
    */
    HRESULT decoderCreateResult = pWICFactory->CreateDecoderFromFilename(L"./Data/Image/test2.png",
        nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

    if (IsNG(decoderCreateResult)) { FatalError(L"デコーダー作成失敗"); }
    _componentRelease.AddReleaseTarget(pDecoder);

    //GIFのような一枚で複数枚使うやつもいるから0と指定しなきゃいけないpngがそもそも1枚なので0番目
    //そいつを入れたい testArtに                ↓GIFとかじゃないから0frame目でok
    HRESULT getFrameResult = pDecoder->GetFrame(0, &pFrameDecode_testArt);
    if (IsNG(getFrameResult)) { FatalError(L"GetFrameできなかった"); }
    _componentRelease.AddReleaseTarget(pFrameDecode_testArt);

    HRESULT convResult = pWICFactory->CreateFormatConverter(&pConverter);
    if (IsNG(convResult)) { FatalError(L"フォーマットコンバーター生成失敗"); }

    //いよいよDirect2Dで使用できる形式に画像の変換が始まる
    HRESULT convInitResult = pConverter->Initialize(
        pFrameDecode_testArt,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);

    if (IsNG(convInitResult)) { FatalError(L"コンバーター初期化失敗"); }
    _componentRelease.AddReleaseTarget(pConverter);

    //ようやく画像が使える状態（ここで乙りかけてた
    HRESULT bmpResult = pRenderTarget->CreateBitmapFromWicBitmap(
        pConverter,                      // 変換済みのWICデータ
        nullptr,                         // プロパティ（デフォルト）
        &pBitmap_testArt                 // ついに ID2D1Bitmap* が手に入る！
    );

    if (IsNG(bmpResult)) { FatalError(L"ビットマップ作成失敗"); }
    _componentRelease.AddReleaseTarget(pBitmap_testArt);

    ShowWindow(hwnd, nCmdShow);

    //大きさをプレイヤーが変えられないようにする
    //SetWindowPos(hwnd, nullptr, 0, 0, SCREEN_Width, SCREEN_Height, SHOW_FULLSCREEN);

    //NO MOVEとしてるので座標位置設定が機能しなくなるので固定直前に位置を設定しておく作戦
    //SetWindowPos(hwnd, nullptr, 0, 0, SCREEN_Width, SCREEN_Height, SWP_NOMOVE);

    // 6. メッセージループ（ゲームループ）
    //MSG構造体にはウィンドウ、メッセージ、時間、マウス座標まで入ってる。
    MSG msg = {};

    _time.Init();
    _bitmapArt.Init(pRenderTarget, pWICFactory);
    fontText.Init(pRenderTarget, &_time);
    GameObject::BindBitMapArt(&_bitmapArt);


    //以下ユーザー側の処理を行う
    UserInit();
    UserStart();

    while (msg.message != WM_QUIT)
    {
        //実行ファイルがメッセージを受け取るために PeekMessageを使い、溜まっているメッセージを処理させる
        //ここで受け取れるようにしないと実行中のゲームを終了する手段が消える
        //キューに登録されていないメッセージをディスパッチする。まぁ入力があれば仕事をするってことかな
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //空白入ってたらしく「予期せぬトークンです」って言われたWWWWWWWWこんなこともあるんや

        // キー入力状態の取得と移動計算  左端のビットを見て「今押されているか」を見るらしいよ
        //一応、右端のビットで「押された瞬間」を取れるみたいだけど危ないらしい。まーそれは自作できるからおｋ

        //position.x += dir.x * playerSpeed;
        //position.y += dir.y * playerSpeed;

        //constexpr float artWidth = 256.0f;

        //if (pRenderTarget)
        //{
        //    D2D1_SIZE_F clientSize = pRenderTarget->GetSize();

        //    if (position.x + artWidth > clientSize.width)
        //    {
        //        position.x = clientSize.width - artWidth;
        //        dir.x = dir.x * -1.0f;
        //    }
        //    else if (position.x < 0.0f)
        //    {
        //        position.x = 0.0f;
        //        dir.x = dir.x * -1.0f;
        //    }

        //    //公式サイト見たら分かるけどA~Zは大文字かつシングルクオーテーションで囲まないと使えない
        //    if (GetAsyncKeyState('W')) { position.y -= playerSpeed; }
        //    if (GetAsyncKeyState('S')) { position.y += playerSpeed; }
        //}
        if (pRenderTarget)
        {
            pRenderTarget->BeginDraw();
            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateGray));
        }

        _time.StartFrame();
        float elapsedTime = _time.GetDeltaTime();

        UserUpdate(elapsedTime);
        GameObjectManager::GetInstance().Update();
        GameObjectManager::GetInstance().Draw();
        UserUI_Update(elapsedTime);

        _time.EndFrame();

        HRESULT renderResult = pRenderTarget->EndDraw();
        if (IsNG(renderResult)) { FatalError(L"EndDraw失敗"); }
    }

    // 7. リソースの解放(COMReleaseデストラクタで自動で行われる)
    return 0;
}
