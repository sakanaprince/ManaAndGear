#include "GameObjectManager.h"

void GameObjectManager::Update()
{
	for (auto& clonedObj : cloneGameObjects)
	{
		clonedObj->Draw();
	}
}
