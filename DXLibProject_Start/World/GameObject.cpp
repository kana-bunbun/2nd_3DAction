#include "GameObject.h"

#include<DxLib.h>
#include<cassert>

#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
#include"../World/Component/Collision.h"
#include"Map/MapManager.h"


GameObject::GameObject():
m_transform(),
m_modelHandle(-1),
m_isActive(true)
{
}

void GameObject::End()
{
	// モデルを読み込んでいたら破棄
	if (m_modelHandle != -1){
		MV1DeleteModel(m_modelHandle);
		m_modelHandle = -1;
	}
}

void GameObject::UpdateCollision()
{
	for (auto& collision : m_collisions) {
		collision.shape->SetPosition(m_transform.position);
	}
}


void GameObject::Draw()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelHandle == -1)return;
	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelHandle);

}

void GameObject::DebugCollision(int color)
{
	for (auto& collision : m_collisions) {
		if (collision.type == GameObject::CollisionType::Null)continue;
		collision.shape->DebugDraw();
	}
}

void GameObject::SetPosition(const Vector3& position)
{
	m_transform.position = position;
	UpdateCollision();
}

//const Collision::Shape& GameObject::GetCollision() const
//{
//	for (const auto& collision : m_collisions) {
//		if (collision.type == CollisionType::Body) {
//			return *collision.shape;
//		}
//	}
//	return *m_collision;
//	return *m_collisions.front().shape;
//}

void GameObject::UpdateHitData()
{
	// 前回のフレームで当たっているかどうかを調べる
	for (int i = 0; i < m_hitData.size(); i++) {
		if (m_hitData[i].isHit) {
			m_hitData[i].isHit = false;
		}
		// 当たっていなければ配列から削除する
		else {
			m_hitData[i].collision = nullptr;
			delete m_hitData[i].collision;
			m_hitData.erase(m_hitData.begin() + i);
		}
	}
}

void GameObject::AddCollision(std::unique_ptr<Collision::Shape> shape, CollisionType type)
{
	assert(shape && "GameCbject::AddCOllision : shape null");

	m_collisions.push_back({ std::move(shape),type });
}

int GameObject::GetOnTileID()
{
	// 前回の衝突判定チェック時からの移動量を調べる
	float moveValue = (m_oldPos - m_transform.position).GetSqLength();
	// 前回更新時から移動していたら
	if (moveValue>MyMath::SquareEpsilon) {
		// 現在自身がいるマスIDを更新
		m_onTileID = MapManager::GetInstance().GetIDFromWorldPos(m_transform.position);
		// 座標更新
		m_oldPos = m_transform.position;
	}
	// マスIDを返す
	return m_onTileID;
}

bool GameObject::IsCollisionEnter(Collision::Shape* collision)
{
	bool inList = false;
	for (int i = 0; i < m_hitData.size(); i++) {

		if (m_hitData[i].collision != collision)continue;
		m_hitData[i].isHit = true;
		inList = true;
		break;
	}
	// 配列に入っていなければtrue
	return !inList;
}
