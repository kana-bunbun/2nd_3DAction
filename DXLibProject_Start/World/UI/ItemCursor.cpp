#include "ItemCursor.h"
#include"../../Utility/Game.h"
#include"../../Utility/Vector3.h"
#include"../../Utility/MyMath.h"
#include"../../System/FontManager.h"
#include"../../Utility/Color.h"
#include"../../System/TimeManager.h"
#include"../Object/Item/BlendManager.h"
#include"../Character/Player/Player.h"
#include"../Object/Item/ItemObjectManager.h"
#include"../Object/Item/HealBottle.h"
#include"ItemSlot.h"
#include<string>
#include<array>
namespace {

	// スロット表示する際の中心座標
	constexpr Vector3 kSlotCenterPos = { Game::kScreenWidth /  3.0f,Game::kScreenHeight * 0.9f,0.0f };
	// スロットのスケール
	constexpr float kSlotScale = 0.05f * Game::kWindowScale;
	// スロット1つ1つの間隔
	constexpr float kSlotDistance = 100.0f * Game::kWindowScale;
	// カーソル画像の大きさ
	constexpr float kCursorScale = 1.3f * Game::kWindowScale;
	// カーソルの補間スピード
	constexpr float kCursorLerpSpeed = 30.0f;

	const char* const kBackGroundPath = "Resource\\Graph\\Icon Background.png";
	const char* const kCursorPath = "Resource\\Graph\\ItemCursor.png";
	const char* const kItemPath[static_cast<int>(BlendManager::Type::Max)] =
	{
		"Resource\\Graph\\HealBottleIcon.png",
		"Resource\\Graph\\Item_Beer.png",
		"Resource\\Graph\\Item_Bread.png",
		"Resource\\Graph\\Item_Cheese.png",
		"Resource\\Graph\\Item_Apple.png",
	};
	// 所持数テキストの表示オフセット
	constexpr Vector3 kHoldNumTextOffset = { 15*Game::kWindowScale,10 * Game::kWindowScale,0.0f };
	// フォント関連
	//const char* const kFontName = "OCRB";
	const char* const kFontName = "Bauhaus 93";
	constexpr int kFontThickness = 5*Game::kWindowScale;
	constexpr int kFontSize = 20 * Game::kWindowScale;
	
	// 長押しで連続的にカーソル移動する際のインターバル
	constexpr float kHoldArrowInterval = 0.04f;

}
ItemCursor::ItemCursor():
	m_selectIndex(0),
	m_showSelectIndex(m_selectIndex),
	m_cursorHandle(-1),
	m_cursorPosition(GetSelectPos(0)),
	m_pad(Input::Pad::Invalid),
	m_isBlendMenu(false),
	m_holdLeftCount(0.0f),
	m_holdRightCount(0.0f),
	m_pPlayer(nullptr),
	m_pItemObjectManager(nullptr)
{
	m_cursorHandle = LoadGraph(kCursorPath);
	m_slots.fill(nullptr);
	for (int i = 0; i < m_slots.size(); i++) {
		m_slots[i] = new ItemSlot();
		m_slots[i]->SetPosition(GetSelectPos(i));
	}
	for (int i = 0; i < m_slots.size(); i++) {
		int num = (m_slots.size() + i) % m_slots.size();
		int type = (static_cast<int>(BlendManager::Type::Max) + i) % static_cast<int>(BlendManager::Type::Max);
		for (int j = 0; j < type * i * i+1; j++) {
		AddItem(static_cast<BlendManager::Type>(type));
		}
	}
	m_selected.fill(BlendManager::Type::Invalid);
}

ItemCursor::~ItemCursor()
{
	DeleteGraph(m_cursorHandle);
	m_cursorHandle = -1;
}

void ItemCursor::Init()
{

}

void ItemCursor::End()
{

}

void ItemCursor::Update()
{

	// カーソル座標の更新処理
	UpdateCursor();
	// 入力による更新処理
	UpdateToInput();


}

void ItemCursor::UpdateCursor()
{
	// カーソルとスロットの座標の差からカーソル座標の補間をする

	// 目標のスロット座標までカーソルの位置を補間
	Vector3 desirePos = GetSelectPos(m_showSelectIndex);
	Vector3 differ = desirePos - m_cursorPosition;
	float deltaTime = TimeManager::GetRawDeltaTime();
	// 補間での移動割合を値域内で収める
	float lerpValue = MyMath::Clamp(deltaTime * kCursorLerpSpeed, 0.0f, 1.0f);
	// 誤差の範囲内なら同じ座標にする
	if (differ.GetSqLength() < MyMath::Epsilon* MyMath::Epsilon) {
		m_cursorPosition = desirePos;
	}
	else {
		// 誤差の範囲外なら補間による座標移動
		m_cursorPosition += differ * lerpValue;
	}

}

void ItemCursor::UpdateToInput()
{
	// コントローラーが割り当てられているとき処理を行う
	if (m_pad == Input::Pad::Invalid)return;

	if (Input::Hold(Input::Button::Left, m_pad)) {
		m_holdLeftCount += TimeManager::GetDeltaTime();
	}
	if (Input::Hold(Input::Button::Right, m_pad)) {
		m_holdRightCount += TimeManager::GetDeltaTime();
	}

	// 入力に応じて選択中のインデックスを更新
	if (Input::IsPressed(Input::Button::Left, m_pad)||
		m_holdLeftCount>=kHoldArrowInterval) {
		m_selectIndex--;
		m_holdLeftCount = 0.0f;
	}
	if (Input::IsPressed(Input::Button::Right, m_pad) ||
		m_holdRightCount >= kHoldArrowInterval) {
		m_selectIndex++;
		m_holdRightCount = 0.0f;
	}
	// 選択中インデックスの更新処理
	NormalizeIndex();
	// メニュー選択状態でなければ
	if (!m_isBlendMenu) {
		if (Input::IsPressed(Input::Button::X, m_pad)) {
			UseItem();
		}
		return;
	}
	if (Input::IsPressed(Input::Button::Y, m_pad)) {
		Cancel();
	}

	if (Input::IsPressed(Input::Button::A, m_pad)) {
		Cancel();
	}

	if (Input::IsPressed(Input::Button::B, m_pad)) {

		if (m_slots[m_selectIndex]->m_type != BlendManager::Type::Invalid)
			if (m_slots[m_selectIndex]->GetHoldNum() > 0) {

				Select();
			}
	}
	if (Input::IsPressed(Input::Button::X, m_pad)) {
		BlendItem();
	}
}

void ItemCursor::NormalizeIndex()
{
	// 見た目上の選択インデックスを更新
	m_showSelectIndex = m_selectIndex;
	
	// 内部の選択インデックスをクランプ
	m_selectIndex = MyMath::Clamp(m_selectIndex, 0, kSlotMax - 1);

	// ↓内部インデックスをクランプする前に見た目インデックスを更新する理由↓

	// スロットの外側を選択しようとしたときにカーソルの位置が一瞬だけ外側に行くことで
	// スロット範囲外は選択できないということをわからせるため
}

void ItemCursor::UseItem()
{
	switch (m_slots[m_selectIndex]->m_type)
	{
	case BlendManager::Type::Apple:
	//m_pItemObjectManager->CallItem<HealBottle>(m_pPlayer);
		m_pItemObjectManager->CallItem<HealBottle>(m_pPlayer);
		break;
	case BlendManager::Type::Beer:
		m_pItemObjectManager->CallItem<HealBottle>(m_pPlayer);
		break;
	case BlendManager::Type::Bread:
		m_pItemObjectManager->CallItem<HealBottle>(m_pPlayer);
		break;
	case BlendManager::Type::Cheese:
		m_pItemObjectManager->CallItem<HealBottle>(m_pPlayer);
		break;
	case BlendManager::Type::CheeseBread:
		m_pItemObjectManager->CallItem<HealBottle>(m_pPlayer);
	default:
		break;
	}
	// 選択中のアイテムを1つ減らす
	m_slots[m_selectIndex]->Sub();
}

void ItemCursor::Draw()
{

	int handle = FontManager::GetInstance().GetFontHandle(kFontName, kFontSize, kFontThickness);

	for (int i = 0; i < kSlotMax;i++) {
		int holdNum = m_slots[i]->GetHoldNum();
		// スロットの描画処理を行う
		m_slots[i]->Draw();
		if (m_slots[i]->m_select) {
			continue;
		}
			//DrawRotaGraph(graphPos.x, graphPos.y, kCursorScale, 0, m_itemHandles[static_cast<int>(m_slots[i]->m_type)], TRUE);
		if (!holdNum)continue;
		
		Vector3 textPos = GetSelectPos(i) + kHoldNumTextOffset;
		// 所持数のテキストを用意
		std::string numText = std::to_string(holdNum);
		// 文字数を取得
		int length=numText.length();
		textPos.x -= kHoldNumTextOffset.x * length;
		std::string holdText = "x"+numText;

		DrawStringToHandle(textPos.x, textPos.y, holdText.c_str(), Color::kWhite, handle);
	}
		DrawRotaGraph(m_cursorPosition.x, m_cursorPosition.y, kCursorScale, 0, m_cursorHandle, TRUE);
		for (auto& selected : m_selected) {
			printfDx("selected : %d\n", selected);
		}
}

Vector3 ItemCursor::GetSelectPos(int selectIndex)
{
	Vector3 result = Vector3::zero;

	result.x= kSlotCenterPos.x + (kSlotDistance * (-kSlotMax * 0.5f + selectIndex + 0.5f));
	result.y = kSlotCenterPos.y;
	return result;
}

bool ItemCursor::AddItem(const BlendManager::Type& type)
{
	// 同じアイテムをすでに所持しているときは所持数に加算する
	for (int i = 0; i < m_slots.size(); i++) {
		if (m_slots[i]->m_type != type)continue;
		// 所持数に加算
		m_slots[i]->Add();
		// 追加できたのでtrue
		return true;
	}
	// 同じアイテムを所持していないとき
	// nullptrの要素を探して追加
	for (int i = 0; i < m_slots.size(); i++) {
		if (m_slots[i]->m_type!=BlendManager::Type::Invalid)continue;
		// アイテム情報を生成し追加
		m_slots[i]->m_type = type;
		m_slots[i]->Add();
		// 追加できたのでtrue
		return true;
	}

	// 追加できなかったのでfalse
	return false;
}

bool ItemCursor::SubItem(const BlendManager::Type& type)
{

	// そのアイテムをすでに所持しているときは所持数を減らす
	for (int i = 0; i < m_slots.size(); i++) {
		if (m_slots[i]->m_type != type)continue;
		// 所持数を減らす
		m_slots[i]->Sub();

		if (m_slots[i]->GetHoldNum() <= 0) {
			Cancel(type);
		}
		// 減少できたのでtrue
		return true;
	}
	// 同じアイテムを所持していないときfalse
	return false;
}

void ItemCursor::Select()
{
	// 選択しているスロットに格納されているアイテムの種類が不正値なら即時return
	if (m_slots[m_selectIndex]->m_type == BlendManager::Type::Invalid)return;

	// 
	int selectedIndex = -1;
	for (int i = 0; i < m_selected.size(); i++) {
		if (m_selected[i] == m_slots[m_selectIndex]->m_type) {
			selectedIndex = i;
			break;
		}
	}
	if(selectedIndex<0)
	for (int i = 0; i < m_selected.size(); i++) {
		 
		if (m_selected[i] != BlendManager::Type::Invalid)continue;

		selectedIndex = i;
		break;
	}
	// 最大数選択済みなら処理しない
	if (selectedIndex < 0)return;

	ChangeSelectFlag(selectedIndex);
}

void ItemCursor::ChangeSelectFlag(size_t index)
{
	bool selected = m_slots[m_selectIndex]->m_select;
	if (selected) {
		m_selected[index] = BlendManager::Type::Invalid;
	}
	else {
		m_selected[index] = m_slots[m_selectIndex]->m_type;
	}
	m_slots[m_selectIndex]->m_select ^= 1;
}

void ItemCursor::Cancel()
{
	// 無選択状態にする
	m_selected.fill(BlendManager::Type::Invalid);
	for (auto& slot : m_slots) {
		slot->m_select = false;
	}
}

void ItemCursor::Cancel(const BlendManager::Type& type)
{
	for (auto& select : m_selected) {
		if (select != type)continue;
		select = BlendManager::Type::Invalid;
		return;
	}
}

bool ItemCursor::BlendItem()
{
	BlendManager::Type blendResult = BlendManager::GetInstnce().Blend(m_selected[0], m_selected[1]);
	// 合成結果が不正値なら処理しない
	if (blendResult == BlendManager::Type::Invalid) {
		Cancel();
		m_selected.fill(BlendManager::Type::Invalid);
		return false;
	}

	// 合成材料のアイテムを1つ減らす
	SubItem(m_selected[0]);
	SubItem(m_selected[1]);
	// 合成結果のアイテムを1つ増やす
	AddItem(blendResult);

	return true;
}
