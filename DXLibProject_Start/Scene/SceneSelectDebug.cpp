#include "SceneSelectDebug.h"
#include<DxLib.h>
#include"../Utility/Color.h"
#include"../Utility/MyMath.h"
#include"../Utility/Input.h"
#include"SceneTest.h"
#include"SceneCollisionTest.h"

#include<functional>

// 現状の規模間だと、この処理でもよいが、
// Sceneを追加した際
// シーンの名前（クラス名とほぼ同じ）の情報を
// 複数回記載することになり、めんどくさい
// 
// 現状の手順
// ・Sceneクラスのヘッダーをインクルード
// ・InitでSceneの登録
// ・Updateで分岐、戻り値の記載
// 1つのシーンを追加した際にすべきことをなるべく減らしたい
// この際、どんな状右方、データの型を持っているかどうかも整理する
// 
// Sceneの情報
// ・各Sceneのクラスを記述したヘッダー
// ・各シーンの名前・文字列→Draw関数内で描画する際に使用
// ・Sceneの名前→vectorに追加してその後の内部処理で使用
// ・各Sceneのクラス→シーン遷移の戻り値で使用
// 
// ヘッダーのファイル名をプログラムのデータでまとめるのは難しそう
// シーンの名前は型でまとめられそう
// 
// 関数オブジェクト
// 処理をデータのように扱う
// これを用いることで上記のシーン情報をまとめることができる
// 
//


SceneSelectDebug::SceneSelectDebug():
    m_selectIndex(0)
{
    m_sceneList.reserve(10);
}

void SceneSelectDebug::Init()
{
    m_sceneList.emplace_back("Debug");
    m_sceneList.emplace_back("Test");
    m_sceneList.emplace_back("Collision");
    m_sceneList.emplace_back("Debug");

}

void SceneSelectDebug::End()
{
    m_sceneList.clear();
}

std::unique_ptr<SceneBase> SceneSelectDebug::Update(float deltaTime)
{
    // 選択項目の更新
    if (!Input::IsPressed(Input::Button::B, Input::Pad::P1)) {
        // 決定ボタンを押していないとき
        
        // 上を押したら選択中のインデックスを減らす
        if (Input::IsPressed(Input::Button::Up, Input::Pad::P1))m_selectIndex--;
        // 下を押したら選択中のインデックスを増やす
        if (Input::IsPressed(Input::Button::Down, Input::Pad::P1))m_selectIndex++;
        // 一定範囲内でループ
        m_selectIndex = (m_sceneList.size() + m_selectIndex) % m_sceneList.size();
        return nullptr;
    }


    // シーン遷移
    const std::string& currentSceneName = m_sceneList[m_selectIndex];

    if (currentSceneName == "Test") {
        return std::make_unique<SceneTest>();
    }
    if (currentSceneName == "Collision") {
        return std::make_unique<SceneCollisionTest>();
    }


    return nullptr;
}

void SceneSelectDebug::Draw()
{
    int baseX = 130;
    int baseY = 130;
    DrawString(baseX, baseY, "SceneSelect 決定ボタンで遷移", Color::kWhite);
    for (int i = 0; i < m_sceneList.size(); i++) {
        int color = Color::kWhite;
        if (i == m_selectIndex)color = Color::kRed;
        DrawString(baseX, baseY + 30 * (i + 1), m_sceneList[i].c_str(), color);
    }
}
