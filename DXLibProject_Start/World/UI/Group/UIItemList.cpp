#include"pch.h"

#include "UIItemList.h"
#include"Utility/MyMath.h"
#include"Utility/Game.h"
#include"World/Character/CharacterManager.h"
#include"World/Character/Player/Player.h"
#include"../Object/UIItemCursor.h"
#include"Data/ActionintervalParam.h"
#include"Utility/Loder/FromCsv.h"
#include"World/Action/ActionInterval.h"
#include"System/ActionIntervalParamManager.h"
#include"World/Object/Item/ItemManager.h"

namespace {
	constexpr Vector2 kFirstSlotPosition = { Game::kScreenWidth * 0.05f,Game::kScreenHeight * 0.9f };
	constexpr Vector2 kSlotDistance = { 100 * Game::kWindowScale ,0.0f };
	// カーソル移動のインターバル
	constexpr int kCursorIntervalID = 2;
	// カーソル移動のアクション
	constexpr Input::Action kCursorMoveAction = Input::Action::ItemCursorMove;
}
UIItemList::UIItemList():
	m_selectIndex(0),
	m_itemSlots(),
	m_pItemCursor(nullptr),
	m_cursorInterval(),
	m_pCharacter(nullptr)
{
	m_cursorInterval.Init(kCursorIntervalID);
}

void UIItemList::OnInit()
{
	// プレイヤーのアイテムリスト
	m_pCharacter = CharacterManager::GetInstance().GetPlayer();
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
	m_pItemCursor->SetPosition(CalculateSlotPos(m_selectIndex));
	AddChild(std::move(cursor));
}

void UIItemList::OnUpdate(float deltatime, const InputData& inputData)
{
	ItemList* itemList = m_pCharacter->GetItemList();
	InputData input = inputData;
	Vector2 inputVector = input.GetVector(Input::Action::CursorMove);

	m_pItemCursor->SetLerpPosition(CalculateSlotPos(m_selectIndex));
	
	if (input.IsPressed(kCursorMoveAction)) {
		// インターバルの初期化
		m_cursorInterval.Setup();
		// カーソル移動のインターバル開始
		m_cursorInterval.SetActive(true);
		// カーソル移動
		MoveCursor(inputVector);
	}

	if (input.IsDown(kCursorMoveAction)) {
		m_cursorInterval.Update(deltatime);
		printfDx("inputVector x : %f | y : %f\n", inputVector.x, inputVector.y);
		if (m_cursorInterval.IsExecute()) {
		// 入力したベクトルをもとにカーソル移動
		MoveCursor(inputVector);
		// カウントをリセット
		m_cursorInterval.ReCount();
		}
	}
	else if (input.IsReleased(kCursorMoveAction)) {
		// インターバルの終了処理
		m_cursorInterval.Finish();
	}
	for (int i = 0; i < m_itemSlots.size();i++) {
		// プレイヤーの所持アイテムリストの情報を設定
		m_itemSlots[i]->SetItemData(itemList->GetItemData(m_itemSlots[i]->GetID()));
	}

	if (input.IsPressed(Input::Action::UseItem)) {
		// リスト上の消費処理
		itemList->UseItem(m_selectIndex);
		// アイテムの
		ItemData item=itemList->GetItemData(m_selectIndex);
		ItemManager::GetInstance().CreateFieldItem(item.GetType(), m_pCharacter->GetPosition());
	}

	printfDx("m_selectIndex : %d\n", m_selectIndex);
}

void UIItemList::SelectPrevIndex()
{
	// 1つ前の項目を選択する
	// カーソルの移動先の座標を設定してから選択中のインデックスをクランプ
	m_selectIndex--;
	m_pItemCursor->SetLerpPosition(CalculateSlotPos(m_selectIndex));
	m_selectIndex = MyMath::Clamp(m_selectIndex, 0, kItemSlotMax - 1);
	
}

void UIItemList::SelectNextIndex()
{
	// 1つ後の項目を選択する
	// カーソルの移動先の座標を設定してから選択中のインデックスをクランプ
	m_selectIndex++;
	m_pItemCursor->SetLerpPosition(CalculateSlotPos(m_selectIndex));
	m_selectIndex = MyMath::Clamp(m_selectIndex, 0, kItemSlotMax - 1);
}

const Vector2& UIItemList::CalculateSlotPos(int slotID)
{
	return kFirstSlotPosition + (kSlotDistance * (slotID+1));

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
