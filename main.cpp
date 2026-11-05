#include "ManaAndGear.h"
#include <vector>
#include <memory>

#include "TestPlayer.h"
#include "TestBullet.h"
Transform::Position PLAYER_INIT_POS{200,400};

TestPlayer player{200,400};
TestBullet bullet{200,300};

int waitTime = 0;

float speed{ 5.0f };
float dirX{ 0.0f };
float dirY{ 0.0f };

int typeCount = 0;
World_WakeUp
{
	//ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber1, L"./Data/Image/test2.png");
	ManaAndGear::_bitmapArt.LoadArtFromSpriteSeat(ArtKeys::ArtNumber1, L"./Data/Image/test2.png",10,20,64,64);
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber2, L"./Data/Image/Ammonite.png");

	player.SetArt(ArtKeys::ArtNumber1);
	bullet.SetArt(ArtKeys::ArtNumber2);
	bullet.SetActive(false);
}

World_Start{}

World_FirstUpdate
{
	if (_gameInput.GetKey('A')) { dirX = -1.0f; }
	else if(_gameInput.GetKey('D')) { dirX = 1.0f;}
	else { dirX = 0.0f; }

	if (_gameInput.GetKey('W')) { dirY = -1.0f; }
	else if (_gameInput.GetKey('S')) { dirY = 1.0f; }	
	else { dirY = 0.0f; }

	player.transform.position += {dirX * speed, dirY * speed};

	if (_gameInput.GetKey(VK_SPACE))
	{
		GameObject* ob = bullet.Clone(player.transform);
		ob->SetArt(ArtKeys::ArtNumber2);
		ob->SetActive(true);
	}

	if (_gameInput.GetKey('T'))
	{
		typeCount++;
	}

	/*
	class Player
	{
		Update()
		{
			if(time > 0.1f)
			{
				//これが呼ばれたら次のコマになる
				NextSpriteFrame();
				//あー分かった、これ大事なのが「1枚の画像をライブラリ内で区切って読み込めたら」ってことなんだ。
				//そしたらScratchみたいに「コスチュームのn番目」ってできるよね？
				//じゃあまず分割ロードから作ります 13:58 
				//14:18テストの時
			}
		}
	}
	*/
}

float timer{ 0.0f };
UINT32 typewriterCount{ 0 };
World_SecondUpdate
{

	return;
	if (_gameInput.GetKey('1')) { ManaAndGear::UI::fontText.TextDraw(30, 30, L"やぁ！さかなディフェンスです。", D2D1_COLOR_F{ 1,1,1,1 }); }
	else if (_gameInput.GetKey('2')) { ManaAndGear::UI::fontText.TextDraw(30, 30, L"やぁ！さかなディフェンスです。", D2D1_COLOR_F{ 0,1,0,1 }); }
	else if (_gameInput.GetKey('3')) { ManaAndGear::UI::fontText.TextDraw(30, 30, L"やぁ！さかなディフェンスです。"); }
	else { ManaAndGear::UI::fontText.TextDraw(30, 70, L"やぁ！さかなディフェンスです。", D2D1_COLOR_F{0,0,0,1}); }
	

	std::wstring message = L"NowTime: " + std::to_wstring(ManaAndGear::_time.GetNowTime());

	ManaAndGear::UI::fontText.TextDraw(30,100,message.c_str());

	timer += deltaTime;
	if (timer > 0.2f)
	{
		typewriterCount++;
		timer = 0.0f;
	}
		

	//ManaAndGear::UI::fontText.TextDrawTypewriter(60,200,
	//	L"ほにゅうびんってなんですか？そう私はよく聞かれるが\nその答えはあざらしが"
	//	L"知っていると答える。ではあざらしとは何か？\nそれは私がよく知っていると思う。"
	//	L"そう、あざらしとはマジックあざらしである。魔法を使って国を救う正義の存在である。",D2D1_COLOR_F{1,0,0,1},typewriterCount);
}