#include "UIItemList.h"
#include"../../../Utility/MyMath.h"
#include"../../../Utility/Game.h"
namespace {
	constexpr Vector2 kFirstSlotPosition = { Game::kScreenWidth * 0.05f,Game::kScreenHeight * 0.9f };
	constexpr Vector2 kSlotDistance = { 100 * Game::kWindowScale ,0.0f };
}
UIItemList::UIItemList():
	m_selectIndex(0)
{
	for (int i = 0; i < m_slots.size(); i++) {
		std::unique_ptr<UIItemSlot>slot = std::make_unique<UIItemSlot>(i);
		slot->Init();
		Vector2 position = kFirstSlotPosition + (kSlotDistance * i);
		slot->SetPosition(position);
		m_slots[i] = slot.get();
		AddChild(std::move(slot));
	}
}

void UIItemList::SelectPrevIndex()
{
	m_selectIndex = MyMath::Clamp(m_selectIndex++, 0, kItemSlotNum);
	
}

void UIItemList::SelectNextIndex()
{
	m_selectIndex = MyMath::Clamp(m_selectIndex--, 0, kItemSlotNum);
}
