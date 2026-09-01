
#include "SceneTest.h"
#include "SceneBase.h"
#include "../Utility/Vector3.h"
#include "../Utility/Color.h"
#include "../Utility/GameSetting.h"
#include "../Utility/MyRandom.h"
#include "../Utility/Loder/Data.h"
#include "../Utility/Loder/FromCSV.h"
#include "../Utility/Loder/CSVLoader.h"
#include "../Utility/Loder/JsonLoader.h"
#include "../World/Component/Transform.h"
#include "../World/Component/Collision.h"
#include "../Camera/CameraOld.h"
#include "../Camera/CameraManager.h"
#include "../Camera/FollowCamera.h"
#include "../Camera/DebugCamera.h"
#include "../System/SoundManager.h"
#include "../System/FontManager.h"
#include "../System/Debug/ProfileScope.h"
#include "../System/Debug/Profiler.h"
#include"../World/Character/Bee.h"
#include"../World/Character/CharacterManager.h"
#include"../World/Character/Enemy/Enemy.h"
#include"../World/Character/Player/Player.h"
#include"../World/Character/Guardian/Dragon.h"
#include"../World/Object/Barrier.h"
#include"../World/Map/TileManager.h"
#include"../World/Map/MapCreate.h"
#include"../World/Map/MapManager.h"
#include"../World/Object/FloorBlock.h"
#include"../World/Object/Item/BlendManager.h"
#include"../World/Object/Item/ItemManager.h"
#include"../World/Object/Item/ItemObjectManager.h"
#include"../World/GameObjectManager.h"
#include"../World/UI/Core/ScreenManager.h"
#include"../World/UI/Screen/InGameMainScreen.h"
#include"../World/UI/Screen/MainScreen.h"
#include"Input/InputManager.h"
#include"Input/InputData.h"
#include<cassert>
#include<memory>
#include<DxLib.h>

namespace {

	constexpr float kLineAreaSize = 10000.0f;	// 地面を描画する線のエリアの大きさ
	constexpr int kLineNum = 50;				// 地面を描画する線の数

	// ビルボードで使用する画像のファイルパス
	const char* const kBillBoardDataPath = ".\\Resource\\image\\DxLogo.png";

	constexpr Vector3 kInitGrassPos = { 0.0f, 0.0f, -400.0f };	// 草の初期座標

	const char* const kFontName = "Ink Free";
	constexpr int kFontSize = 50;
	constexpr int kFontThickness = 50;


}

SceneTest::SceneTest():
	m_pScreenManager(nullptr)
{
	m_pScreenManager = std::make_unique<ScreenManager>();
	m_pScreenManager->PushScreen(std::make_unique<MainScreen>());

}

SceneTest::~SceneTest() {}

void SceneTest::Init() {

	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	// フェード処理開始
	SceneBase::StartFadeIn();
}

void SceneTest::End() {
	SoundManager::GetInstance().Release();

	GameObjectManager::GetInstance().End();
	ItemManager::GetInstance().End();
}

std::unique_ptr<SceneBase> SceneTest::Update(float deltaTime) {
	ProfileScope("Update");

	InputData inputData = InputManager::GetInputData();
	m_pScreenManager->Update(deltaTime, inputData);
	
	ItemManager::GetInstance().Update();
	return nullptr;
}

void SceneTest::Draw() {
	ProfileScope("Draw");

	//ItemManager::GetInstance().Draw();
	// 描画処理
	m_pScreenManager->Draw();
	InputData inputData = InputManager::GetInputData();
	float inputRadian = inputData.GetRadian(Input::Action::Move);
	printfDx("LeftTrigger : Radian : %f\n", inputRadian);
	printfDx("LeftTrigger :  angle : %f\n", inputRadian*MyMath::ToDegree);

}

void SceneTest::DrawGround()
{
	Vector3 pos1;
	Vector3 pos2;

	pos1 = Vector3(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = Vector3(-kLineAreaSize / 2.0f, 0.0f, kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1.ToVECTOR(), pos2.ToVECTOR(), Color::kWhite);
		pos1.x += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.x += kLineAreaSize / static_cast<float>(kLineNum);
	}

	pos1 = Vector3(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = Vector3(kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1.ToVECTOR(), pos2.ToVECTOR(), Color::kWhite);
		pos1.z += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.z += kLineAreaSize / static_cast<float>(kLineNum);
	}
}


