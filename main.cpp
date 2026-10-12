#include "ManaAndGear.h"

Transform::Position PLAYER_INIT_POS{200,400};
GameObject player{200,400};
GameObject enemy{ 128, 0 };
int waitTime = 0;

World_WakeUp
{
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber1, L"./Data/Image/test2.png");
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber2, L"./Data/Image/Ammonite.png");
	player.BindBitmapArt(&ManaAndGear::_bitmapArt);
	enemy.BindBitmapArt(&ManaAndGear::_bitmapArt);
}

World_Start{}

World_Update
{
	player.Draw(ArtKeys::ArtNumber1);
	enemy.Draw(ArtKeys::ArtNumber2);

	auto playerArtSize = _bitmapArt.GetArtSize(ArtKeys::ArtNumber1);
	Transform::Position offset = { playerArtSize.width, playerArtSize.height };
	player.hitBox = { player.transform.position, player.transform.position + offset };

	auto enemyArtSize = _bitmapArt.GetArtSize(ArtKeys::ArtNumber2);
	Transform::Position enHitOffset = { enemyArtSize.width,enemyArtSize.height };
	enemy.hitBox = { enemy.transform.position, enemy.transform.position + enHitOffset };
	enemy.DrawHitBox();

	player.transform.position.y -= 0.9f;

	if (player.IsHit_BoxBox(enemy.hitBox))
	{
		MessageBox(NULL, L"きたーーーーーあたった", L"", 0);
		player.transform.position = PLAYER_INIT_POS;
	}
}



void Kari()
{
	player.Draw(ArtKeys::ArtNumber1);
	enemy.Draw(ArtKeys::ArtNumber2);

	auto playerArtSize = _bitmapArt.GetArtSize(ArtKeys::ArtNumber1);
	Transform::Position offset = { playerArtSize.width, playerArtSize.height };
	player.hitBox = { player.transform.position, player.transform.position + offset };
	player.DrawHitBox();

	auto enemyArtSize = _bitmapArt.GetArtSize(ArtKeys::ArtNumber2);
	Transform::Position enHitOffset = { enemyArtSize.width,enemyArtSize.height };
	enemy.DrawHitBox(enemy.transform.position, enemy.transform.position + enHitOffset);
	enemy.hitBox = { enemy.transform.position, enemy.transform.position + enHitOffset };

	if (player.IsHit_BoxBox(enemy.hitBox))
	{
		MessageBox(NULL, L"きたーーーーーあたった", L"", 0);
		player.transform.position = PLAYER_INIT_POS;
	}

	waitTime++;
	if (waitTime < 60) { return; }
	player.transform.position.y -= 0.9f;
}