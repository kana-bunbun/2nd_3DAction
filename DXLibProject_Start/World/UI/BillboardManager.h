#pragma once
#include"../../Utility/Vector3.h"
#include<array>
class BillboardManager
{
public:
	// ビルボードで描画する種類
	enum eBillboard {
		Stair,
		Collection,
		Max,
	};
public:
	static BillboardManager& GetInstance();
	~BillboardManager();
	void Init();
	void End();
	void DrawBillboard(Vector3 position,float centerX,float centerY,float size,float rad,eBillboard billboardType);
private:
	// シングルトンにする
	BillboardManager() = default;
	// コピー禁止
	BillboardManager(const BillboardManager&) = delete;
	// コピー代入禁止
	BillboardManager& operator=(const BillboardManager&) = delete;
	// ムーブ禁止
	BillboardManager(BillboardManager&&) = delete;
	// ムーブ代入禁止
	BillboardManager& operator=(const BillboardManager&&) = delete;
private:
	std::array<int, eBillboard::Max>m_graphHandles;
};

