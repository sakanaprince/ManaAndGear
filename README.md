# ManaAndGear

**プログラミング初心者がC++でのゲーム開発のハードルを下げられる2Dゲーム制作ライブラリ**

Microsoftの**Direct2D**を自作関数でラップし、複雑な初期設定やリソース管理を意識せずに、画像の描画・入力処理・当たり判定などを扱えるようにしました。  
機能面だけでなく、**「最初につまずきにくく、作ったものがすぐ形になること」**を重視した初心者目線の設計を取り入れています。

---

## 💡 工夫した点：目に見える変化を真っ先に！

ゲーム制作では、最初の「画面に何かが出た！」という体験がモチベーションにつながります。ManaAndGearでは、**わずか2行のコード**で任意の画像を描画できるようにしています。

1. **画像を読み込む（`LoadArt()`）**  
   画像ファイルのパスと、ライブラリ側で用意した列挙体 `ArtKeys` のキーを指定して読み込みます。
2. **座標を指定して描画する（`DrawArt()`）**  
   `ArtKeys` と描画したい座標を指定するだけで、毎フレームウィンドウに描画されます。
3. **解放処理はライブラリ側で担当**  
   画像リソースの解放はライブラリ側で行われるため、メモリ管理の複雑さに悩まされずに済みます。

> **設計の意図について**  
> `ArtKeys` と画像を紐づける仕組みのため、同時に扱える画像数には限りがあります。それでもこの方式を選んだのは、**「初心者が最低限の手間で画像を描画し、目に見える変化をいち早く体験できるようにしたい」**という考えからです。

---

## ✨ 現在の機能

* **WinMain / Direct2D の初期設定**（複雑なセットアップをライブラリ側で隠蔽）
* **画像の読み込みと描画**（`LoadArt()` / `DrawArt()`）
* **スプライトシートの分割読み込み**
* **キー入力の受付**
* **当たり判定の設定**
* **テキストの描画**

---

## 🔄 ゲームループ用関数（ライフサイクル）

ライブラリ側で用意している関数を実装することで、処理の順番を意識しながらゲームを構築できます。

| 関数名 | 呼ばれるタイミング | 主な使用例 |
| :--- | :--- | :--- |
| `World_WakeUp` | 最初（起動時） | 画像の読み込み（`LoadArt()` など） |
| `World_Start` | `World_WakeUp` の直後 | 各キャラクターの初期位置・ステータス設定 |
| `World_FirstUpdate` | 毎フレーム | 移動・入力処理・当たり判定などのゲームループ |
| `World_SecondUpdate` | `World_FirstUpdate` 後（毎フレーム） | テキスト・UIの描画など |

---

## 🚀 使い方のイメージ

```cpp
// 例：

#include "ManaAndGear.h"

Player player;

World_WakeUp()
 {
    LoadArt(ArtKeys::ArtNumber1, L"player.png");
}

World_Start()
{
    player.SetArt(ArtKeys::ArtNumber1);
    player.transform.position = {0.0f, 0.0f};
}

World_FirstUpdate()
{
    // キー入力や移動・当たり判定などの処理
    if (_gameInput.GetKey('A')) { dirX = -1.0f; }
    else if(_gameInput.GetKey('D')) { dirX = 1.0f;}
    else { dirX = 0.0f; }
    
    if (_gameInput.GetKey('W')) { dirY = -1.0f; }
    else if (_gameInput.GetKey('S')) { dirY = 1.0f; }	
    else { dirY = 0.0f; }

    float speed = 10.0f;
    player.transform.position += {dirX * speed, dirY * speed};
}

World_SecondUpdate()
{
    ManaAndGear::UI::fontText.TextDraw(30, 70, L"遊び方：十字キーで動かします");
}
