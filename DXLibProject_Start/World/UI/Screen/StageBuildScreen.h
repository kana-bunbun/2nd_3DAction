#pragma once
#include"../core/Screen.h"

class TileManager;
class CameraManager;
class Player;
class Dragon;
class Barrier;
class UIItemList;
class StageSpawner;
class StagePart;
class StagePartDatabase;
namespace Collision {
	class Triangle;
	class Sphere;
}
class StageBuildScreen:public Screen
{
public:
	StageBuildScreen();
	~StageBuildScreen();

	void Init() override;
	void CreateObjects();
	void Update(float deltaTime, const InputData& _inputData) override;
	void Draw() override;
private:
	std::unique_ptr<CameraManager> m_pCameraMgr;
	std::unique_ptr<TileManager>m_pTileManager;
	Player* m_pPlayer;
	Dragon* m_pDragon;
	Barrier* m_pBarrier;
	UIItemList* m_pUiItemList;

	std::unique_ptr<StagePartDatabase>m_pStagePartDatabase;
	std::unique_ptr<StageSpawner>m_pStageSpawner;
	std::vector<StagePart*>m_pStageParts;
	std::unique_ptr<Collision::Triangle>m_pTriangle0;
	std::unique_ptr<Collision::Triangle>m_pTriangle1;
	std::unique_ptr<Collision::Triangle>m_pTriangle2;
	std::unique_ptr<Collision::Triangle>m_pTriangle3;
	std::unique_ptr<Collision::Sphere>m_pSphere;

};

