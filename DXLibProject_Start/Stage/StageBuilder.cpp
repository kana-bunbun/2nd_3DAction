#include "pch.h"
#include "StageBuilder.h"
#include"World/Character/CharacterManager.h"
#include"World/Character/Player/Player.h"
#include"Utility/Loader/JsonLoader.h"

Stage::StageData StageBuilder::BuildStageTest() const
{
	Stage::StageData stage;
	
	Vector3 playerPos = Vector3::zero;
	Player* pPlayer = CharacterManager::GetInstance().GetPlayer();
	if(pPlayer)
		playerPos+=pPlayer->GetTransform().position;
	for (int i = 0; i < 10; i++) {
		Vector3 randomPos = Vector3(MyRandom::Float01(), MyRandom::Float01(), MyRandom::Float01()) * 350;
		stage.objects.push_back({ "TestBlock", { {playerPos + randomPos},{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f} } });
	}

	return stage;
}

Stage::StageData StageBuilder::BuildFromJson(const std::string& path) const
{
	Stage::StageData data;
	data.objects = Data::Json::LoadJsonAs<Stage::ObjectData>(path);
	return data;
}
