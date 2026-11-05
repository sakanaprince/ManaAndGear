#include "GameObjectManager.h"

void GameObjectManager::AddListGameObject(GameObject& gameObject)
{		
	//MessageBox(NULL, L"Stack OBJ", L"e", 0);
	if (GetAllGameObjectCounts() > MaxGameObjectCount)
	{
#ifdef _DEBUG
		MessageBox(NULL, L"心配！ゲームオブジェクト多すぎませんか？", L"Debugビルド時専用メッセージ", 0);
#endif // DEBUG
	}

	gameObjects.push_back(&gameObject);	
}

void GameObjectManager::AddCloneGameObject(GameObject& gameObject)
{
	if (GetAllGameObjectCounts() > MaxGameObjectCount)
	{
#ifdef _DEBUG
		MessageBox(NULL, L"心配！クローンやりすぎてないですか？", L"Debugビルド時専用メッセージ", 0);
#endif // DEBUG
	}

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
