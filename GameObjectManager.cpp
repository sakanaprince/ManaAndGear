#include "GameObjectManager.h"

void GameObjectManager::Update()
{
	for (auto& obj : gameObjects)
	{
		if (obj->IsActive() == false) { continue; }

		obj->Update();
	}
}

void GameObjectManager::Draw()
{
	for (auto& obj : gameObjects)
	{
		if(obj->IsActive() == false) { continue; }

		obj->Draw();
	}
}
