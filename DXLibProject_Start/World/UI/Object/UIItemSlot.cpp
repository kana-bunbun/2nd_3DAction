#include"pch.h"
#include "UIItemSlot.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/Vector2.h"
#include"../../Character/Character.h"
#include"../../../System/ImageManager.h"
#include"../../Object/Item/ItemList.h"
#include"../../Object/Item/ItemData.h"
namespace {
	// アイテムアイコン画像の画像パスID
	constexpr int kItemPathID[static_cast<int>(ItemData::Type::Max)] = {
		3000,
		3001,
		3002,
		3003,
		3004,
		3005,
	};
	// アイテムスロット背景の画像パスID
	constexpr int kBackGroundPathID = 1500;
	constexpr float kSlotScale = 0.05f * Game::kWindowScale;
	constexpr float kItemScale = 1.2f * Game::kWindowScale;
	constexpr Vector2 kSelectIconOffset = { 0.0f,-70 * Game::kWindowScale };
	constexpr int kNormalIconSize = 32;
}
UIItemSlot::UIItemSlot(int ID):
	m_slotID(ID)
{
	// スロット背景画像取得
	m_backGroundImage = ImageManager::GetInstance().GetImage(kBackGroundPathID);

}
UIItemSlot::~UIItemSlot()
{
}
void UIItemSlot::OnDraw()
{
	// スロット背景の描画
	DrawRotaGraph(m_position.x, m_position.y, kSlotScale, 0, m_backGroundImage->GetHandle(), TRUE);
	// 自身が担当しているスロットにアイテムがなければ即時return
	if (!m_itemData.ExistItem())return;
	// 描画する画像を取得
	int itemGraphID = kItemPathID[static_cast<int>(m_itemData.GetType())];
	std::shared_ptr<ImageResource> itemGraph = ImageManager::GetInstance().GetImage(itemGraphID);
	// 描画座標を求める
	Vector2 drawPos = m_position;
	//if (m_select)drawPos += kSelectIconOffset;
	int graphHandle = itemGraph->GetHandle();
	// アイテムアイコン描画
	DrawRotaGraph(
		drawPos.x, drawPos.y,
		GetNormalizeGraphScale(itemGraph->GetHandle()),
		0, itemGraph->GetHandle(), TRUE);
}

float UIItemSlot::GetNormalizeGraphScale(int graphHandle)
{
	float scale = 1.0f;
	int sizeX=1, sizeY=1;
	// 画像が読み込めていなければ不正値を返す
	if (graphHandle == -1)return -1.0f;
	GetGraphSize(graphHandle, &sizeX, &sizeY);
	// 指定画像の縦か横の大きい方を基準の大きさとする
	float baseSize = (sizeX > sizeY) ? sizeX : sizeY;
	// 0での除算回避用の処理
	if (!baseSize)return 0.0f;

	// アイテムスロットに合うサイズを返す
	return static_cast<float>(kNormalIconSize)/baseSize;
}

