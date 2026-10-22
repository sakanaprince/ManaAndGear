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

World_WakeUp
{
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber1, L"./Data/Image/test2.png");
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber2, L"./Data/Image/Ammonite.png");

	player.SetArt(ArtKeys::ArtNumber1);
	bullet.SetArt(ArtKeys::ArtNumber2);
	bullet.SetActive(false);
}

World_Start{}

World_Update
{
	if (_gameInput.GetKey('A')) { dirX = -1.0f; }
	else if(_gameInput.GetKey('D')) { dirX = 1.0f;}
	else { dirX = 0.0f; }

	if (_gameInput.GetKey('W')) { dirY = -1.0f; }
	else if (_gameInput.GetKey('S')) { dirY = 1.0f; }	
	else { dirY = 0.0f; }

	player.transform.position += {dirX * speed, dirY * speed};

	//！！！念願の超簡単クローン処理ができたぞ！！！
	if (_gameInput.GetKey(VK_SPACE))
	{
		GameObject* ob = bullet.Clone(player.transform);
		ob->SetArt(ArtKeys::ArtNumber2);
		ob->SetActive(true);
	}

	ManaAndGear::_fontText.TextDraw(30, 30, L"DDD");

}