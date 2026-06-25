#include "GameObjectManager.h"
#include"Object/Barrier.h"
#include<memory>
#include<vector>

#include"GameObject.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	End();
}

void GameObjectManager::Init()
{

}

void GameObjectManager::End()
{
	Clear();
}

void GameObjectManager::Update(float deltaTime)
{
	for (auto& obj : m_objects) {
		if (!obj->IsActive())continue;
		obj->Update(deltaTime);
	}
}

void GameObjectManager::LateUpdate(float deltaTime)
{
	for (auto& obj : m_objects) {
		if (!obj->IsActive())continue;
		obj->LateUpdate(deltaTime);
	}
}

void GameObjectManager::Draw()
{
	std::vector<GameObject*>transparentIndex;
	for (auto& object:m_objects) {
		if (!object->IsActive())continue;
		if (object->IsTransparent()) {
			transparentIndex.push_back(object.get());
			continue;
		}
		object->Draw();
	}
	// 透明になるオブジェクトは後に描画する
}

void GameObjectManager::CheckCollision()
{

}

void GameObjectManager::Clear()
{
	for (auto& obj : m_objects) {
		obj->End();
	}
	m_objects.clear();
	m_destrpyObjects.clear();
}

void GameObjectManager::DestroObject(GameObject* obj)
{
	if (!obj)return;
	m_destrpyObjects.push_back(obj);
}

void GameObjectManager::ProcessDestroy()
{
	// 削除予定のオブジェクトがなければスルー
	if (m_destrpyObjects.empty())return;

	// 管理している全オブジェクトをチェック、削除するのでイテレータで対応
	for (auto it = m_objects.begin(); it != m_objects.end();) {
		GameObject* obj = it->get();

		// 削除フラグを用意
		bool destroy = false;

		// 削除予定リストと比較
		for (auto* target : m_destrpyObjects) {
			if (obj == target) {
				destroy = true;
				break;
			}
		}
		if (destroy) {
			obj->End();
			it = m_objects.erase(it);
		}
		else {
			// 削除予定のものがなければ次の要素をチェック
			it++;
		}
	}

	// 削除対応が終わったので削除予定リストをクリア
	m_destrpyObjects.clear();
}

const std::vector<std::unique_ptr<GameObject>>& GameObjectManager::GetObjects() const
{
	return m_objects;
}
