#pragma once
#include "GameObjcet.h"
#include <memory>
#include <vector>

class GameObjectManager
{
private:
	//std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> clonedGameObjects;

	//privateにコンストラクタを置くと他のクラスで　GameObjectManager otherManager;とか出来なくなる
	GameObjectManager() = default;

public:

	void AddListGameObject(GameObject& gameObject);

	/// <summary>
	/// Cloneされたものはnewされている（ヒープ）なのでデストラクタ時にdeleteするリストに登録する
	/// スタック領域の変数はヒープではないので、deleteすることは出来ない（また異世界に飛ばされてしまう
	/// </summary>
	/// <param name="gameObject"></param>
	void AddCloneGameObject(GameObject& gameObject);
	
	void Update();
	void Draw();

	static GameObjectManager& GetInstance()
	{
		// 初めて呼び出された時に1度だけ初期化される（スレッドセーフ）
		static GameObjectManager instance;
		return instance;
	}

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
	// ムーブ演算も削除しておくとより安全
	GameObjectManager(GameObjectManager&&) = delete;
	GameObjectManager& operator=(GameObjectManager&&) = delete;

	~GameObjectManager()
	{
		// プログラム終了時に全オブジェクトを破棄
		for (GameObject* obj : clonedGameObjects)
		{
			if(obj){
				MessageBox(NULL, L"消したCloneObject", L"通知くん", 0);
				delete obj; }
		}
		clonedGameObjects.clear();
	}

};

//まぁね、僕設計とか真面目にやったことないんですけど作戦会議しないと駄目そうなので考えます
	//目標：初心者の人に分かりやすい　これが大事なんで...
	//GameObject player;とかは良いんだよ,てか実際使うときさすがにGameObject型で宣言しないだろ、UnityでC#無しの
	//オブジェクトを作らないように...だったらGameObjcetを継承したクラスを沢山作ってもらおう。
	//Player playerとか作った時に描画とか移動は手軽に出来る（神）として、Bulletみたいなクラスはどうしましょう。
	//Bullet.Cloned()　でvirtual void GameObject::Cloned(){}とかで「クローンされたら」にあたるものが出来るかも。
	//ではGameObjectManagerの仕事は？ここまでの話だけなら必要なくない？
	//作る意味【１】初心者の人が簡単にインスタンス生成させられる窓口として
	//作る意味【２】実行中、動的に生成されるGameObjcet達のメモリの解放を行うため(追記：これはuniquePtrがやる事なんだよなぁ)
	//いけそうじゃね
	//インスタンス生成される窓口とは言ってみたけど、<T>を使うやり方とGameObject自身が自分をクローンする方法があるんか
	//そして【１】【２】を見た限りマジでObjManagerいらない説が...
	//今一番悩んでるのはユーザーがGameObjを継承した任意のクラスの複製をどうするかってのに頭かかえてる
	//T型でこわいのはObj派生以外が来たら泣くよっていう不安、まあTで一回作るわ

//template<typename T>
//inline std::shared_ptr<T> GameObjectManager::Clone(const T& original, Transform& _transform)
//{
//	auto clonedObject = std::make_shared<T>(original);
//
//	clonedObject->OnCloned();
//	clonedObject->transform.position = _transform.position;
//
//	gameObjects.push_back(clonedObject);
//
//	return clonedObject;
//}


