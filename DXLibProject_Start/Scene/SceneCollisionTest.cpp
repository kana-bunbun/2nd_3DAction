#include "SceneCollisionTest.h"
#include "SceneSelectDebug.h"
#include<DxLib.h>
#include"../Utility/Color.h"
#include"../Utility/MyMath.h"
#include"../Utility/Input.h"

SceneCollisionTest::SceneCollisionTest()
{

}

void SceneCollisionTest::Init()
{
    // フェード処理開始
    SceneBase::StartFadeIn();
}

void SceneCollisionTest::End()
{

}

std::unique_ptr<SceneBase> SceneCollisionTest::Update(float deltaTime)
{
    if (Input::IsPressed(Input::Button::Back, Input::Pad::P1))
        return std::make_unique<SceneSelectDebug>();
    return nullptr;
}

void SceneCollisionTest::Draw()
{
    DrawString(130, 130, "CollisionTest", Color::kWhite);
}
