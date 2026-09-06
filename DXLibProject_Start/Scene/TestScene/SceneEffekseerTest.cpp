#include"pch.h"

#include "SceneEffekseerTest.h"
#include "Scene/SceneBase.h"
#include "Utility/Vector3.h"
#include "Utility/Color.h"
#include "Utility/GameSetting.h"
#include "Utility/MyRandom.h"
#include "Utility/Loder/Data.h"
#include "Utility/Loder/FromCSV.h"
#include "Utility/Loder/CSVLoader.h"
#include "Utility/Loder/JsonLoader.h"
#include "World/Component/Transform.h"
#include "World/Component/Collision.h"
#include "Camera/CameraOld.h"
#include "Camera/CameraManager.h"
#include "Camera/FollowCamera.h"
#include "Camera/DebugCamera.h"
#include "System/SoundManager.h"
#include "System/FontManager.h"
#include "System/Debug/ProfileScope.h"
#include "System/Debug/Profiler.h"
#include "System/EffectResourceManager.h"
#include "System/EffectManager.h"
#include"World/Character/Bee.h"
#include"World/Character/CharacterManager.h"
#include"World/Character/Enemy/Enemy.h"
#include"World/Character/Player/Player.h"
#include"World/Character/Guardian/Dragon.h"
#include"World/Object/Barrier.h"
#include"World/Map/TileManager.h"
#include"World/Map/MapCreate.h"
#include"World/Map/MapManager.h"
#include"World/Object/FloorBlock.h"
#include"World/Object/Item/BlendManager.h"
#include"World/Object/Item/ItemManager.h"
#include"World/Object/Item/ItemObjectManager.h"
#include"World/GameObjectManager.h"
#include"World/UI/Core/ScreenManager.h"
#include"World/UI/Screen/InGameMainScreen.h"
#include"World/UI/Screen/MainScreen.h"
#include"Input/InputManager.h"
#include"Input/InputData.h"


namespace {

	constexpr float kLineAreaSize = 10000.0f;	// 地面を描画する線のエリアの大きさ
	constexpr int kLineNum = 50;				// 地面を描画する線の数

	// ビルボードで使用する画像のファイルパス
	const char* const kBillBoardDataPath = ".\\Resource\\image\\DxLogo.png";

	constexpr Vector3 kInitGrassPos = { 0.0f, 0.0f, -400.0f };	// 草の初期座標

	const char* const kFontName = "Ink Free";
	constexpr int kFontSize = 50;
	constexpr int kFontThickness = 50;

	const char* const kEffectPath = "Resource\\Effect\\Laser01.efkefc";
}

SceneEffekseerTest  ::SceneEffekseerTest  () :
	m_pScreenManager(nullptr),
	m_pEffectResourceManager(nullptr),
	m_pEffectManager(nullptr)

{
	m_pScreenManager = std::make_unique<ScreenManager>();
	m_pScreenManager->PushScreen(std::make_unique<MainScreen>());

}

SceneEffekseerTest  ::~SceneEffekseerTest  () {}

void SceneEffekseerTest  ::Init() {

	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	// フェード処理開始
	SceneBase::StartFadeIn();

	// エフェクト読み込み
	m_pEffectResourceManager = std::make_unique<EffectResourceManager>();
	m_pEffectManager= std::make_unique<EffectManager>(m_pEffectResourceManager);
}

void SceneEffekseerTest  ::End() {
	SoundManager::GetInstance().Release();

	GameObjectManager::GetInstance().End();
	ItemManager::GetInstance().End();

	m_pEffectResourceManager->Clear();
	m_pEffectManager->Clear();
}

std::unique_ptr<SceneBase> SceneEffekseerTest  ::Update(float deltaTime) {
	ProfileScope("Update");

	InputData inputData = InputManager::GetInputData();
	printfDx("input  isDown up : %d\n", inputData.IsDown(Input::Action::Up));
	m_pScreenManager->Update(deltaTime, inputData);

	printfDx("input  isDown Up : %d\n", inputData.IsDown(Input::Action::Up));

	printfDx("input isDown Up : %d\n", inputData.IsDown(Input::Action::Up));
	printfDx("input isDown Right : %d\n", inputData.IsDown(Input::Action::Right));
	printfDx("input isDown Down : %d\n", inputData.IsDown(Input::Action::Down));
	printfDx("input isDown Left : %d\n", inputData.IsDown(Input::Action::Left));
	printfDx("input isDown Decide : %d\n", inputData.IsDown(Input::Action::Decide));
	printfDx("input isDown Cancel : %d\n", inputData.IsDown(Input::Action::Cancel));
	printfDx("input isDown Menu : %d\n", inputData.IsDown(Input::Action::Menu));
	printfDx("input isDown Start : %d\n", inputData.IsDown(Input::Action::Start));
	printfDx("input isDown Move : %d\n", inputData.IsDown(Input::Action::Move));
	printfDx("input isDown SelectMove : %d\n", inputData.IsDown(Input::Action::SelectMove));
	printfDx("input isDown Camera : %d\n", inputData.IsDown(Input::Action::Camera));
	printfDx("input isDown DragonCall : %d\n", inputData.IsDown(Input::Action::DragonCall));
	printfDx("input isDown Dash : %d\n", inputData.IsDown(Input::Action::Dash));
	printfDx("input isDown Parry : %d\n", inputData.IsDown(Input::Action::Parry));

	// エフェクトの再生処理
	if (inputData.IsDown(Input::Action::Menu)) {
		// エフェクトの再生
		//m_playEffectHandle = PlayEffekseer3DEffect(m_effectHandle);
		Transform playerTransform = CharacterManager::GetInstance().GetPlayer()->GetTransform();
		m_pEffectManager->Play(1,playerTransform.position);
		//SetPosPlayingEffekseer3DEffect(m_playEffectHandle, playerTransform.position.x, playerTransform.position.y + 100 , playerTransform.position.z);
		//SetRotationPlayingEffekseer3DEffect(m_playEffectHandle, playerTransform.rotation.x, playerTransform.rotation.y, playerTransform.rotation.z);

	}
	// エフェクトの更新処理
	m_pEffectManager->Update(deltaTime);

	ItemManager::GetInstance().Update();
	return nullptr;
}

void SceneEffekseerTest  ::Draw() {
	ProfileScope("Draw");

	//ItemManager::GetInstance().Draw();
	// 描画処理
	m_pScreenManager->Draw();
	InputData inputData = InputManager::GetInputData();
	float inputRadian = inputData.GetRadian(Input::Action::Move);
	printfDx("LeftThumb : Radian : %f\n", inputRadian);
	printfDx("LeftThumb :  angle : %f\n", inputRadian * MyMath::ToDegree);
	printfDx("LeftThumb :  ratio : %f\n", inputData.GetInputRatio(Input::Action::Move));

	m_pEffectManager->Draw();
}

void SceneEffekseerTest ::DrawGround()
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


