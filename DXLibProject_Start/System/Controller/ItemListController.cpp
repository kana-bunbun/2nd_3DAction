#include "pch.h"
#include "ItemListController.h"
#include "System/ActionIntervalParamManager.h"
#include "World/UI/Group/UIItemList.h"

namespace {
	constexpr int kCursorMoveIntervelID = 2;
}

ItemListController::ItemListController(UIItemList* _itemLlist):
	m_cursorInterval(),
	m_itemList(_itemLlist)
{
	Init();
}

void ItemListController::Init()
{
	m_cursorInterval.Init(kCursorMoveIntervelID);

}

void ItemListController::SetItemList(UIItemList* _itemLlist)
{
	m_itemList=_itemLlist;
}

void ItemListController::Update(float deltaTime, const InputData& _inputData)
{
	UpdateMoveCursor(deltaTime, _inputData);
	UpdateAction(deltaTime, _inputData);
}

void ItemListController::UpdateMoveCursor(float deltaTime, const InputData& _inputData)
{
	Vector2 inputVector = _inputData.GetVector(Input::Action::CursorMove);

	// カーソル移動の入力をした瞬間
	if (_inputData.IsPressed(Input::Action::ItemCursorMove)) {
		// インターバルの初期化
		m_cursorInterval.Setup();
		// カーソル移動のインターバル開始
		m_cursorInterval.SetActive(true);
		// カーソル移動
		m_itemList->MoveCursor(inputVector);
		Vector2 inputVectora = _inputData.GetVector(Input::Action::ItemCursorMove);
	}
	// カーソル移動の入力をしているあいだ
	if (_inputData.IsDown(Input::Action::ItemCursorMove)) {
		// インターバルの更新
		m_cursorInterval.Update(deltaTime);

		if (m_cursorInterval.IsExecute()) {
			// 入力したベクトルをもとにカーソル移動
			m_itemList->MoveCursor(inputVector);
			// カウントをリセット
			m_cursorInterval.ReCount();
		}
	}
	// カーソル移動の入力を離した瞬間
	else if (_inputData.IsReleased(Input::Action::ItemCursorMove)) {
		// インターバルの終了処理
		m_cursorInterval.Finish();
	}
}
