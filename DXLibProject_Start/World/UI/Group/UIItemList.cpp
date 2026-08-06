#include "UIItemList.h"
#include"../../../Utility/MyMath.h"
#include"../../../Utility/Game.h"
#include"../../../World/Character/CharacterManager.h"
#include"../../../World/Character/Player/Player.h"
#include"../Object/UIItemCursor.h"
namespace {
	constexpr Vector2 kFirstSlotPosition = { Game::kScreenWidth * 0.05f,Game::kScreenHeight * 0.9f };
	constexpr Vector2 kSlotDistance = { 100 * Game::kWindowScale ,0.0f };
}
UIItemList::UIItemList():
	m_selectIndex(0)
{

}

void UIItemList::OnInit()
{
	// プレイヤーのアイテムリスト
	Player* player = CharacterManager::GetInstance().GetPlayer();
	for (int i = 0; i < m_itemSlots.size(); i++) {
		std::unique_ptr<UIItemSlot>slot = std::make_unique<UIItemSlot>(i);
		slot->Init();
		Vector2 position = CalculateSlotPos(i);
		slot->SetPosition(position);
		m_itemSlots[i] = slot.get();
		AddChild(std::move(slot));
	}
	std::unique_ptr<UIItemCursor> cursor=std::make_unique<UIItemCursor>();
	m_pItemCursor = cursor.get();
	m_pItemCursor->SetPosition(CalculateSlotPos(0));
	AddChild(std::move(cursor));
}

void UIItemList::OnUpdate(float deltatime)
{
	ItemList itemList = *CharacterManager::GetInstance().GetPlayer()->GetItemList();
	for (auto& itemSlot : m_itemSlots) {
		itemSlot->SetItemData(itemList.GetItemData(itemSlot->GetID()));
	}
}

void UIItemList::SelectPrevIndex()
{
	// 1つ前の項目を選択する
	// カーソルの移動先の座標を設定してから選択中のインデックスをクランプ
	m_selectIndex++;
	if (m_pItemCursor) {
		Vector2 lerpPos = CalculateSlotPos(m_selectIndex);
		m_pItemCursor->SetLerpPosition(lerpPos);
	}
	m_selectIndex = MyMath::Clamp(m_selectIndex, 0, kItemSlotNum);
	
}

void UIItemList::SelectNextIndex()
{
	// 1つ後の項目を選択する
	// カーソルの移動先の座標を設定してから選択中のインデックスをクランプ
	m_selectIndex--;
	if (m_pItemCursor) {
		Vector2 lerpPos = CalculateSlotPos(m_selectIndex);
		m_pItemCursor->SetLerpPosition(lerpPos);
	}
	m_selectIndex = MyMath::Clamp(m_selectIndex, 0, kItemSlotNum);
}

const Vector2& UIItemList::CalculateSlotPos(int slotID)
{
	return kFirstSlotPosition + (kSlotDistance * (slotID+1));

}
