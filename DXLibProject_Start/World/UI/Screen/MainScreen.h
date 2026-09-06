#pragma once
#include"pch.h"

#include"../core/Screen.h"
class TileManager;
class CameraManager;
class Player;
class Dragon;
class Barrier;
class UIItemList;

/// <summary>
/// ゲームのメイン画面
/// </summary>
class MainScreen:public Screen
{
public:
	MainScreen();
	~MainScreen();

	void Init() override ;
	void CreateObjects();
	void Update(float deltaTime, const InputData& inputData) override;
	void Draw() override;
private:
	std::unique_ptr<CameraManager> m_pCameraMgr;
	std::unique_ptr<TileManager>m_pTileManager;
	Player* m_pPlayer;
	Dragon* m_pDragon;
	Barrier* m_pBarrier;
	UIItemList* m_pUiItemList;
};

