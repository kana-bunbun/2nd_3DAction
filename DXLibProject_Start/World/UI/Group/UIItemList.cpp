#include"pch.h"

#include "UIItemList.h"
#include"Utility/MyMath.h"
#include"Utility/Game.h"
#include"World/Character/CharacterManager.h"
#include"World/Character/Player/Player.h"
#include"../Object/UIItemCursor.h"
#include"Data/ActionintervalParam.h"
#include"Utility/Loader/FromCsv.h"
#include"World/Action/ActionInterval.h"
#include"System/ActionIntervalParamManager.h"
#include"World/Object/Item/ItemManager.h"
#include"World/Object/Item/BlendManager.h"

namespace {
	constexpr Vector2 kFirstSlotPosition = { Game::kScreenWidth * 0.05f,Game::kScreenHeight * 0.9f };
	constexpr Vector2 kSlotDistance = { 100 * Game::kWindowScale ,0.0f };
	// カーソル移動のインターバル
	constexpr int kCursorIntervalID = 2;
	// カーソル移動のアクション
	constexpr Input::Action kCursorMoveAction = Input::Action::ItemCursorMove;
}
UIItemList::UIItemList():
	m_cursorIndex(0),
	m_itemSlots(),
	m_pItemCursor(nullptr),
	m_cursorInterval(),
	m_pCharacter(nullptr),
	m_pItemList(nullptr)
{
	m_cursorInterval.Init(kCursorIntervalID);
	m_selectIndex.fill(-1);
}

void UIItemList::OnInit()
{
	if (!m_pCharacter) {
		m_pCharacter = CharacterManager::GetInstance().GetPlayer();
	}
	if (!m_pItemList) {
		m_pItemList = m_pCharacter->GetItemList();
	}

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
	m_pItemCursor->SetLerpPosition(CalculateSlotPos(m_cursorIndex));
	m_pItemCursor->SetPosition(CalculateSlotPos(m_cursorIndex));
	AddChild(std::move(cursor));
}

void UIItemList::OnUpdate(float deltatime, const InputData& _inputData)
{
	CursorUpdate(deltatime, _inputData);

	printfDx("m_selectIndex : %d\n", m_cursorIndex);
	DebugDraw();
}

void UIItemList::AfterUpdate(float deltatime, const InputData& _inputData)
{
	m_pItemCursor->SetLerpPosition(CalculateSlotPos(m_cursorIndex));

}

void UIItemList::CursorUpdate(float deltatime, const InputData& _inputData)
{
	for (int i = 0; i < m_itemSlots.size(); i++) {
		// プレイヤーの所持アイテムリストの情報を設定
		m_itemSlots[i]->SetItemData(m_pItemList->GetItemData(m_itemSlots[i]->GetID()));
	}
}

void UIItemList::SelectPrevIndex()
{
	// 1つ前の項目を選択する
	// カーソルの移動先の座標を設定してから選択中のインデックスをクランプ
	m_cursorIndex--;
	m_pItemCursor->SetLerpPosition(CalculateSlotPos(m_cursorIndex));
	m_cursorIndex = MyMath::Clamp(m_cursorIndex, 0, kItemSlotMax - 1);
	
}

void UIItemList::SelectNextIndex()
{
	// 1つ後の項目を選択する
	// カーソルの移動先の座標を設定してから選択中のインデックスをクランプ
	m_cursorIndex++;
	m_pItemCursor->SetLerpPosition(CalculateSlotPos(m_cursorIndex));
	m_cursorIndex = MyMath::Clamp(m_cursorIndex, 0, kItemSlotMax - 1);
}

const Vector2& UIItemList::CalculateSlotPos(int slotID)
{
	return kFirstSlotPosition + (kSlotDistance * (slotID+1));

}

void UIItemList::DebugDraw()
{
	ImGui::Begin("ItemList");
	for (int i = 0; i < m_itemSlots.size();i++) {
		ImGui::Text("slot%d Type : %d | num : %d \n", m_itemSlots[i]->GetID(), static_cast<int>(m_itemSlots[i]->GetItemData().GetType()), m_itemSlots[i]->GetItemData().GetItemNum());
	}
	std::string selected =  "selectedIndex : ";
	for (int i = 0; i < m_selectIndex.size(); i++) {

		if (i > 0)selected += " | ";

		selected += std::to_string(m_selectIndex[i]);
	}
	ImGui::Text(selected.c_str());
	ImGui::End();
}

void UIItemList::MoveCursor(const Vector2& inputVector)
{
	DirectionFour inputDirection = DirectionFour::Invalid;

	// 横方向の入力量があるとき
	if (MyMath::Abs(inputVector.x) > MyMath::Epsilon)
	// 左右の大きい方を入力方向とする
	inputDirection = (inputVector.x >= 0) ? DirectionFour::Right : DirectionFour::Left;

	// 入力方向が不正値なら処理しない
	int directionIndex = static_cast<int>(inputDirection);
	if (directionIndex < 0 || directionIndex >= static_cast<int>(DirectionFour::Max))return;
	// 4方向指定のカーソル移動処理
	MoveCursor(inputDirection);
}

void UIItemList::MoveCursor(const DirectionFour& direction)
{
	if (direction == DirectionFour::Right) {
		// カーソル右方向に1つずらす
		SelectNextIndex();
	}
	if (direction == DirectionFour::Left) {
		// カーソル左方向に1つずらす
		SelectPrevIndex();
	}
}

void UIItemList::UseItem()
{
	// リスト上の消費処理
	m_pItemList->UseItem(m_cursorIndex);
	m_itemSlots[m_cursorIndex]->ConsumeItem(m_pCharacter->GetTransform());
}

void UIItemList::Select()
{
	if (!m_itemSlots[m_cursorIndex]->Exists())return;
	bool selected = m_itemSlots[m_cursorIndex]->Select();
	if (selected) {
		for (int i = 0; i < m_selectIndex.size(); i++) {
			// 選択中のインデックスに不正値があれば
			if (m_selectIndex[i]<0||m_selectIndex[i]>=m_itemSlots.size()) {
				// インデックスを現在のカーソル番号に
				m_selectIndex[i] = m_cursorIndex;
				// 番号を設定できたので関数を抜ける
				return;
			}
			// すでに選択可能な最大個数まで選択していたら
			if (i == m_selectIndex.size() - 1) {
				// 選択できないので選択状態をもとに戻す
				Cancel(m_cursorIndex);
				return;
			}
		}
	}
	else {
		Cancel(m_cursorIndex);
	}

}

void UIItemList::Cancel(int slotID)
{
	// 指定されているスロット番号が正常な値なら
	if (slotID >= 0 && slotID < m_itemSlots.size()) {
		// その番号のスロットのキャンセルを呼ぶ
		m_itemSlots[slotID]->Cancel();
		for (auto& select : m_selectIndex) {
			if (select != slotID)continue;
			select = -1;
			break;
		}
	}
	// 不正値が渡されているとき
	else {
		// すべてのキャンセル処理を呼ぶ
		for (auto& slot : m_itemSlots) {
			slot->Cancel();
		}
		m_selectIndex.fill(-1);
	}
}

void UIItemList::Blend()
{
	// 最大数選択されていなければ処理しない
	if (SelectedNum() != kItemSelectMax)return;

	ItemList* _itemList = m_pCharacter->GetItemList();
	if (!_itemList)return;

	// 選択中のアイテムの種類を取得
	ItemData::Type select0 = m_itemSlots[m_selectIndex[0]]->GetItemData().GetType();
	ItemData::Type select1 = m_itemSlots[m_selectIndex[1]]->GetItemData().GetType();
	// 選択アイテムの合成結果を取得
	ItemData::Type blendResult = BlendManager::GetInstnce().Blend(select0, select1);

	// 合成結果が不正値なら処理しない
	if (blendResult == ItemData::Type::Invalid){
		Cancel();
		return;
	}
	// アイテムを追加できたかどうかを調べる
	bool addItem = _itemList->AddItem(blendResult);

	// アイテムを追加できなければ処理しない
	if (!addItem)return;

	// アイテムを追加できたので選択スロットの消費処理
	for (auto& select : m_selectIndex) {
		_itemList->UseItem(select);
	}
}

void UIItemList::SetCharacter(Character* pCharacter)
{
	m_pCharacter = pCharacter;
	m_pItemList = m_pCharacter->GetItemList();
}

int UIItemList::SelectedNum()
{
	int selectNum = 0;
	for (auto& select : m_selectIndex) {
		// 選択しているインデックスが不正値ならスキップ
		if (select < 0 || select >= kItemSlotMax)continue;
		// 選択している数に加算
		selectNum++;
	}

	return selectNum;
}
