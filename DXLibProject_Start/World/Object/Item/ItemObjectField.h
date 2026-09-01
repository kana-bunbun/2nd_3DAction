#pragma once
#include "../../GameObject.h"
#include "ItemData.h"
#include <array>
namespace {
	constexpr int kHitLog = 2;
}
class ItemCursor;
class ItemObjectField:public GameObject
{
public:
	ItemObjectField();
	~ItemObjectField();

	void Init()override;
	void End()override;
	void Update(float deltaTime,const InputData& inputData)override;
	void Draw()override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	void PickUpItem(const InputData& inputData);
	void Setup(const ItemData::Type& type, const Vector3& position);
public:
	void SetItemCursor(ItemCursor* itemcursor) { m_pItemCursor = itemcursor; }

private:
	ItemCursor* m_pItemCursor;
	ItemData::Type m_type;
	std::array<bool, kHitLog> m_hitLog;
};

