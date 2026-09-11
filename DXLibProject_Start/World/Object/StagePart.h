#pragma once
#include"World/GameObject.h"
class StagePart:public GameObject
{
public:

	StagePart();
	virtual ~StagePart() = default;

	void Init()override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result)override;
	void SetName(const std::string& partName) { m_partName = partName; }
	const std::string GetName() const { return m_partName; }
	void Draw()override;
private:
	std::string m_partName;
};

