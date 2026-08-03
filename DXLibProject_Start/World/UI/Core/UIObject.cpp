#include "UIObject.h"

UIObject::UIObject():
	m_position(Vector2::Zero),
	m_visible(true),
	m_parent(nullptr)
{
}

void UIObject::Init()
{
	// 自身固有の初期化処理
	OnInit();
	// 子オブジェクトの初期化処理
	for (auto& child : m_children) {
		if (!child)continue;
		child->Init();
	}
}

void UIObject::Update(float deltaTime)
{
	// 自身固有の更新処理
	OnUpdate(deltaTime);
	// 子オブジェクトの更新処理
	for (auto& child : m_children) {
		if (!child)continue;
		child->Update(deltaTime);
	}
}

void UIObject::Draw()
{
	// 自身か親オブジェクトが非表示なら描画せずreturn
	if (!IsVisibleInHierarchy())return;

	// 自身固有の描画処理
	OnDraw();
	// 子オブジェクトの描画処理
	for (auto& child : m_children) {
		if (!child)continue;
		child->Draw();
	}
}

void UIObject::End()
{
	// 子オブジェクトの終了処理
	for (auto& child : m_children) {
		if (!child)continue;
		child->End();
	}
	// 自身固有の終了処理
	OnEnd();
}

Vector2 UIObject::GetWorldPosition() const
{
	// 親オブジェクトがいなければ
	// 自身が親オブジェクトなので自身の座標を返す
	if (!m_parent)return m_position;
	return m_parent->GetWorldPosition() + m_position;
}

bool UIObject::IsVisibleInHierarchy() const
{
	// 自身が非表示なら非表示を返す
	if (!m_visible)return false;

	// 親オブジェクトがいる場合、親オブジェクトの表示状態を返す
	if (m_parent)return m_parent->IsVisibleInHierarchy();

	return true;
}

void UIObject::AddChild(std::unique_ptr<UIObject> child)
{
	// オブジェクトが不正なら即時return
	if (!child)return;
	// 指定された子オブジェクトの親オブジェクトを自身に設定
	child->m_parent = this;

	// 子オブジェクトの初期設定
	child->Init();
	// 子オブジェクトを配列に追加
	m_children.emplace_back(std::move(child));
}
