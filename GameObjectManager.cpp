#include "GameObjectManager.h"

void GameObjectManager::AddListGameObject(GameObject& gameObject)
{		
	//MessageBox(NULL, L"Stack OBJ", L"e", 0);
	gameObjects.push_back(&gameObject);	
}

void GameObjectManager::AddCloneGameObject(GameObject& gameObject)
{
	//MessageBox(NULL, L"Heap OBJ", L"e", 0);
	clonedGameObjects.push_back(&gameObject);
}

void GameObjectManager::Update()
{
	for (auto& obj : gameObjects)
	{
		if (obj->IsActive() == false) { continue; }

		obj->Update();
	}

	for (auto& obj : clonedGameObjects)
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

	for (auto& obj :clonedGameObjects)
	{
		if (obj->IsActive() == false) { continue; }

		obj->Draw();
	}
}
