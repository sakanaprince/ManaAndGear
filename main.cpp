#include "ManaAndGear.h"
#include "TestPlayer.h"
#include <vector>
#include <memory>

Transform::Position PLAYER_INIT_POS{200,400};

GameObject player{200,400};
GameObject enemy{ 300, 0 };
TestPlayer testPlayer{ 100,100 };
std::vector<std::shared_ptr<TestPlayer>> allGameObject;

int waitTime = 0;

float speed{ 5.0f };
float dirX{ 0.0f };
float dirY{ 0.0f };

World_WakeUp
{
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber1, L"./Data/Image/test2.png");
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber2, L"./Data/Image/Ammonite.png");
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

	if (_gameInput.GetKey('A')) { dirX = -1.0f; }
	else if(_gameInput.GetKey('D')) { dirX = 1.0f;}
	else { dirX = 0.0f; }

	if (_gameInput.GetKey('W')) { dirY = -1.0f; }
	else if (_gameInput.GetKey('S')) { dirY = 1.0f; }	
	else { dirY = 0.0f; }

	if (_gameInput.GetKey(VK_SPACE))
	{

		auto ob = _gameObjectManager.Clone(testPlayer);
		allGameObject.push_back(ob);
	}



	for (auto& obj : allGameObject)
	{
		obj->transform.position += {dirX* speed, dirY* speed};
		obj->Draw(ArtKeys::ArtNumber1);

		auto objArtSize = _bitmapArt.GetArtSize(ArtKeys::ArtNumber2);


		obj->hitBox = { obj->transform.position,
			{obj->transform.position.x + objArtSize.width, obj->transform.position.y + objArtSize.height} };


		if (obj->IsHit_BoxBox(enemy.hitBox)) { obj->transform.position = PLAYER_INIT_POS; }
	}

	player.transform.position += {dirX * speed, dirY * speed};

	if (player.IsHit_BoxBox(enemy.hitBox))
	{
		player.transform.position = PLAYER_INIT_POS;
	}
}