#include "ItemSlot.h"
#include "../../System/ResourceManager.h"
#include "../../Utility/Game.h"

namespace {
	const char* const kItemPath[static_cast<int>(BlendManager::Type::Max)] = {
		"Item_Apple",
		"Item_Beer",
		"Item_Bread",
		"Item_Cheese",
		"Item_CheeseBread",
	};
	const char* const kBackGroundPath = "Icon Background";
	constexpr float kSlotScale = 0.05f * Game::kWindowScale;
	constexpr float kItemScale = 1.2f * Game::kWindowScale;
	constexpr Vector3 kSelectIconOffset = { 0.0f,-70 * Game::kWindowScale,0.0f };
	
}

ItemSlot::ItemSlot():
	m_type(BlendManager::Type::Invalid),
	m_select(false),
	m_holdNum(0),
	graphHandle(-1)
{

}

ItemSlot::~ItemSlot()
{

}

void ItemSlot::Init()
{
	m_holdNum = 0;
	m_select = false;
	m_type = BlendManager::Type::Invalid;
}

void ItemSlot::Draw()
{
	int backGroundHandle = ResourceManager::GetInstance().GetGraph(kBackGroundPath);
	DrawRotaGraph(m_drawPos.x, m_drawPos.y, kSlotScale, 0, backGroundHandle, TRUE);
	if (m_type == BlendManager::Type::Invalid)return;
	int itemHandle = ResourceManager::GetInstance().GetGraph(kItemPath[static_cast<int>(m_type)]);
	Vector3 drawPos = m_drawPos;
	if (m_select)drawPos += kSelectIconOffset;
	DrawRotaGraph(drawPos.x, drawPos.y, kItemScale, 0, itemHandle, TRUE);

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
}

void ItemSlot::SetItemType(BlendManager::Type itemType)
{

}
