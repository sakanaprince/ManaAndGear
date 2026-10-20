#include "GameObjectManager.h"

void GameObjectManager::Update()
{
	for (auto& clonedObj : gameObjects)
	{
		if (clonedObj->IsActive() == false) { continue; }

		clonedObj->Update();
	}
}

void GameObjectManager::Draw()
{
	for (auto& clonedObj : gameObjects)
	{
		if (clonedObj->IsActive() == false) { continue; }

		clonedObj->Draw();
	}
}
