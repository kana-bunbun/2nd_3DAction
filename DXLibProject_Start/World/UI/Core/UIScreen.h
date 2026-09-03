#pragma once
#include<vector>
#include<memory>
#include<type_traits>
#include"UIObject.h"
#include"Input/InputData.h"
#include"../ScreenCommand.h"
#include"Screen.h"
/// <summary>
/// UIObjectをまとめて管理するクラス
/// 1画面につき１つのインスタンスを作成
/// このクラスはSceneからuniqe_ptrで使用される想定
/// Sceneが破棄されたら自動で破棄される
/// 
/// 複数のUIObjectを一括で管理するマネージャーのような内容だが
/// あくまで画面を管理するクラスとして使用
/// </summary>
class UIScreen:public Screen
{
public:
	UIScreen()=default;
	~UIScreen() = default;

	void Init() override {};
	void Update(float deltaTime,const InputData& input) override;
	void Draw() override;

	/// <summary>
	/// UIオブジェクトの生成
	/// </summary>
	template<class T,class... Args>
	T* CreateUIObject(Args&&... args);

	

protected:

	/// <summary>
	/// UIObjectの追加
	/// </summary>
	/// <param name="object"></param>
	void AddUIObject(std::unique_ptr<UIObject> object);
	/// <summary>
	/// コマンドの設定
	/// </summary>
	/// <param name="command"></param>
	void SetUICommand(const UI::Command& command) { m_command = command; }

protected:
	/// <summary>
	/// このクラスで管理するUIObject
	/// </summary>
	std::vector<std::unique_ptr<UIObject>>m_rootObjects;


};

template<class T, class ...Args>
inline T* UIScreen::CreateUIObject(Args && ...args)
{
	// UIオブジェクトを継承しているかどうかチェック
	static_assert(std::is_base_of<UIObject, T>::value, "CreateUIObject UIObject 未継承");

	// オブジェクト生成
	auto uiObj = std::make_unique<T>(std::forward<Args>(args)...);

	// 初期化
	uiObj->Init();

	// UIScreenがUIObjectを管理する
	// 外部参照用の生ポインタrawPtrは使わずunique_ptrで保持
	//
	T* rawPtr = uiObj.get();

	// スマートポインタをm_rootObjectsに追加
	m_rootObjects.emplace_back(std::move(uiObj));
	return rawPtr;
}
