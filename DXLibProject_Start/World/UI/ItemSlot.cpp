#include "ItemSlot.h"
#include "../../System/ResourceManager.h"
#include "../../System/Debug/ProfileScope.h"
#include "../../Utility/Game.h"
#include "../../Utility/MyMath.h"

namespace {
	const char* const kItemPath[static_cast<int>(ItemData::Type::Max)] = {
		"Honey",
		"Jam",
		"Pepper",
		"Whiskey",
		"HealBottle",
		"MolotovCocktail",
	};
	const char* const kBackGroundPath = "Icon Background";
	constexpr float kSlotScale = 0.05f * Game::kWindowScale;
	constexpr float kItemScale = 1.2f * Game::kWindowScale;
	constexpr Vector3 kSelectIconOffset = { 0.0f,-70 * Game::kWindowScale,0.0f };
	constexpr int kNormalIconSize = 32;
}

ItemSlot::ItemSlot():
	m_itemData(),
	m_select(false),
	m_holdNum(0)
{
	m_graphData = ResourceManager::GetInstance().GetGraph(kBackGroundPath);
	m_itemData.m_type = ItemData::Type::Invalid;
}

ItemSlot::~ItemSlot()
{

}

void ItemSlot::Init()
{
	m_holdNum = 0;
	m_select = false;
	m_itemData.m_type = ItemData::Type::Invalid;
}

void ItemSlot::Draw()
{
	std::string ss = "ItemCursor" + std::to_string(m_drawPos.x) + "::Draw()";
	ProfileScope scope(ss);

	DrawRotaGraph(m_drawPos.x, m_drawPos.y, kSlotScale, 0, m_graphData->GetHandle(), TRUE);
	if (m_itemData.m_type == ItemData::Type::Invalid)return;
	GraphData* itemGraph = ResourceManager::GetInstance().GetGraph(kItemPath[static_cast<int>(m_itemData.m_type)]);
	Vector3 drawPos = m_drawPos;
	if (m_select)drawPos += kSelectIconOffset;
	DrawRotaGraph(drawPos.x, drawPos.y, NormalizeGraphScale(itemGraph->GetHandle()), 0, itemGraph->GetHandle(), TRUE);

}

void ItemSlot::End()
{
}

void ItemSlot::Add()
{
	m_holdNum++;
}

void ItemSlot::Sub()
{
	m_holdNum--;
	m_holdNum = MyMath::Clamp(m_holdNum, 0, m_holdNum);
	if (m_holdNum)return;
	// 所持数が0になったら

	// アイテムの種類を不正値にする
	m_itemData.m_type = ItemData::Type::Invalid;
}

void ItemSlot::SetItemType(ItemData::Type type)
{
	m_itemData.m_type = type;

	if (type == ItemData::Type::Invalid)return;
	//m_graphData = ResourceManager::GetInstance().GetGraph(kItemPath[static_cast<int>(m_itemData.m_type)]);

}

float ItemSlot::NormalizeGraphScale(int graphHandle)
{
	int sizeX, sizeY;
	GetGraphSize(graphHandle, &sizeX, &sizeY);
	// 横の大きさと縦の大きさのうち大きい方を取得
	int max = (sizeX > sizeY) ? sizeX : sizeY;
	float scale = static_cast<float>(kNormalIconSize) / static_cast<float>(max);
	return scale* kItemScale;
}
