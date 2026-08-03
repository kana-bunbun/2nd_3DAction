#pragma once
#include"../../../Utility/Vector2.h"
#include<vector>
#include<memory>

/// <summary>
/// UIで扱うオブジェクトの基底クラス
/// </summary>
class UIObject
{
public:
	UIObject();
	virtual ~UIObject() {};
	void Init();
	/// <summary>
	/// 更新処理
	/// 現状、非表示にしていても更新処理は走る
	/// </summary>
	void Update(float deltaTime);
	/// <summary>
	/// 描画処理
	/// IsVisibleInHierarchyの結果が非表示なら即時return
	/// </summary>
	void Draw();
	void End();
	void SetPosition(const Vector2& position) { m_position = position; }
protected:
	// 派生クラス拡張用の関数

	// 基本的に空の関数
	// 個別で処理したいことがあればoverrideで記載
	virtual void OnInit() {};
	virtual void OnUpdate(float deltaTime) {};
	virtual void OnDraw() {};
	virtual void OnEnd() {};


public:
	// 座標関連の関数
	const Vector2& GetPosition()const { return m_position; }
	Vector2 GetWorldPosition()const;

	void SetVisible(bool visible) { m_visible = visible; }
	bool IsVisible() const { return m_visible; }
	/// <summary>
	/// 親階層の表示状態を考慮した結果を取得
	/// </summary>
	/// <returns></returns>
	bool IsVisibleInHierarchy() const;

	// 親子階層関連の関数

	/// <summary>
	/// 子オブジェクトを追加
	/// </summary>
	/// <param name="child"></param>
	void AddChild(std::unique_ptr<UIObject>child);
	/// <summary>
	/// 親オブジェクトを取得
	/// </summary>
	UIObject* GetParent()const { return m_parent; }
protected:
	Vector2 m_position;
	bool m_visible;

	/// <summary>
	/// 親子階層　親オブジェクト
	/// </summary>
	UIObject* m_parent;
	/// <summary>
	/// 親子階層　子オブジェクト
	/// 	/// </summary>
	std::vector<std::unique_ptr<UIObject>>m_children;

};

