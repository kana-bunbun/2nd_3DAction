#include "GameObjectManager.h"
#include"Object/Barrier.h"
#include"Character/Character.h"
#include<memory>
#include<vector>
#include"../Utility/MyMath.h"
#include"Map/MapConst.h"
#include"GameObject.h"

GameObjectManager& GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return instance;
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
		obj->UpdateHitData();
		obj->Update(deltaTime);
		obj->UpdateCollision();
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
	for (auto& object : transparentIndex) {
		if (!object->IsActive())continue;
		object->Draw();
	}
	// 当たり判定のデバッグ表示
	for (auto& object : m_objects) {
		if (!object->IsActive())continue;
		//object->DebugCollision();
	}
	// 後描画処理
	for (auto& object : m_objects) {
		if (!object->IsActive())continue;
		object->LateDraw();
	}

}

void GameObjectManager::CheckCollision()
{
	//// GameObjectManagerに登録されているオブジェクトを総当たりでチェックする
	//for (size_t i = 0; i < m_objects.size(); i++) {
	//	// オブジェクトの取得
	//	GameObject* objA = m_objects[i].get();

	//	// アクティブになっていなければスルー
	//	if (!objA->IsActive())continue;

	//	for (size_t j = 0; j < m_objects.size(); j++) {
	//		// オブジェクトの取得
	//		GameObject* objB = m_objects[j].get();

	//		// アクティブになっていなければスルー
	//		if (!objB->IsActive())continue;

	//		// コリジョンが未設定かどうか確認

	//		const Collision::Shape& collisionA = objA->GetCollision();
	//		const Collision::Shape& collisionB = objB->GetCollision();
	//		
	//		Collision::Result result = collisionA.CheckCollision(collisionB);
	//		// 当たっていなければスルー
	//		if (!result.isHit)continue;

	//		// 当たっていたらそれぞれのオブジェクトに衝突結果を渡す
	//		objA->ResolveCollision(*objB, result);
	//		// 法線を反転させてから渡す
	//		result.normal *= -1;
	//		objB->ResolveCollision(*objA, result);

	//	}

	//}

	// GameObjectManagerに登録されているGameObjectを総当たりでチェックする
	// 衝突判定で使用するオブジェクトの取得、衝突判定の有無をチェック
	// 確認が取れたら衝突判定の結果を取得し、各オブジェクトへ結果を返す
	for (size_t i=0; i < m_objects.size(); i++) {
		// オブジェクトの取得
		GameObject* objA = m_objects[i].get();
	
		// アクティブになっていなければスルー
		if (!objA->IsActive())continue;
		// objAのすべてのコリジョンを取得
		const auto& collisionsA = objA->GetCollisions();
		// コリジョンがなければスルー
		if (collisionsA.empty())continue;
		for (size_t j = i+1; j < m_objects.size(); j++) {
			// オブジェクトの取得
			GameObject* objB = m_objects[j].get();
			// アクティブになっていなければスルー
			if (!objB->IsActive())continue;
			// objBのすべてのコリジョンを取得
			const auto& collisionsB = objB->GetCollisions();
			// コリジョンがなければスルー
			if (collisionsB.empty())continue;
			// 壁同士の当たり判定は調べない
			if (objA->GetCollisionTag() == CollisionTag::Wall &&
				objB->GetCollisionTag() == CollisionTag::Wall)continue;
			// 現在いるマスが隣り合っていない場合スルー
			if (!IsChebyishevTile(objA, objB))continue;

			for (auto& collisionA : collisionsA) {
				// コリジョンがなければスルー
				if (!collisionA.shape)continue;
				if (collisionA.type == CollisionType::Null)continue;

				for (auto& collisionB : collisionsB) {
					// コリジョンがなければスルー
					if (!collisionB.shape)continue;
					if (collisionB.type == CollisionType::Null)continue;
					// 衝突判定
					Collision::Result resultA = collisionA.shape->CheckCollision(*collisionB.shape);

					if ((objA->GetCollisionTag() == CollisionTag::Wall &&
						collisionB.type==CollisionType::Heal) ||
						(objA->GetCollisionTag() == CollisionTag::Dragon &&
							collisionB.type == CollisionType::Heal)) {
						int f = 0;
					}
					// 当たっていなければスルー
					if (!resultA.isHit)continue;


					// objAの衝突後処理
					objA->ResolveCollision(*objB, collisionA, collisionB, resultA);

					// 衝突結果をコピー
					Collision::Result resultB = resultA;
					// 法線を反転
					resultB.normal *= -1;
					
					// objBの衝突後処理
					objB->ResolveCollision(*objA, collisionB, collisionA, resultB);
					

				}
			}

		}

	}

}

void GameObjectManager::Clear()
{
	for (auto& obj : m_objects) {
		obj->End();
	}
	m_objects.clear();
	m_destrpyObjects.clear();
}

void GameObjectManager::DestroyObject(GameObject* obj)
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

void GameObjectManager::StrageObject(GameObject* obj)
{
	// キャラクタークラスにキャストができたら
	Character* castToCharacter = dynamic_cast<Character*>(obj);
	if (castToCharacter) {
		// キャラクタークラスの配列に追加
		m_characters.push_back(castToCharacter);
		// IDを設定
		castToCharacter->m_ID = m_characters.size() - 1;
		return;
	}
}

const std::vector<std::unique_ptr<GameObject>>& GameObjectManager::GetObjects() const
{
	return m_objects;
}

bool GameObjectManager::IsChebyishevTile(GameObject* baseObj, GameObject* checkObj)
{
	// 2つのオブジェクトのマスIDを取得
	int baseID = baseObj->GetOnTileID();
	int checkID = checkObj->GetOnTileID();
	// 2つのオブジェクトのマスIDの差を取得
	int differ = MyMath::Abs(baseID - checkID);
	// IDの差が 1 以下の時(同じマスまたは左右に隣り合っている時)または
	// 差が横幅-1 以上かつ横幅+1 以下の時(斜めまたは上下に隣り合っている時)true
	if (differ <= 1||
		(differ <= MapConst::MAP_SQUARE_WIDTH_COUNT - 1 &&
		differ >= MapConst::MAP_SQUARE_WIDTH_COUNT + 1))return true;
	// それ以外はfalse
	return false;
}
