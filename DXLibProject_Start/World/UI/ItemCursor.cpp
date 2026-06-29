#include "ItemCursor.h"
#include"../../Utility/Game.h"
#include"../../Utility/Vector3.h"
#include"../../Utility/MyMath.h"
#include"../../System/FontManager.h"
#include"../../Utility/Color.h"
#include"../../System/TimeManager.h"
#include"../Object/Item/BlendManager.h"
#include"ItemSlot.h"
#include<string>
#include<array>
namespace {

	// スロット表示する際の中心座標
	constexpr Vector3 kSlotCenterPos = { Game::kScreenWidth /  3.0f,Game::kScreenHeight * 0.9f,0.0f };
	// スロットのスケール
	constexpr float kSlotScale = 0.05f * Game::kWindowScale;
	constexpr float kSlotDistance = 100.0f * Game::kWindowScale;

	constexpr float kCursorScale = 1.3f * Game::kWindowScale;
	constexpr float kCursorLerpSpeed = 30.0f;
	const char* const kBackGroundPath = "Resource\\Graph\\Icon Background.png";
	const char* const kCursorPath = "Resource\\Graph\\ItemCursor.png";
	const char* const kItemPath[static_cast<int>(BlendManager::Type::Max)] =
	{
		"Resource\\Graph\\Item_Apple.png",
		"Resource\\Graph\\Item_Beer.png",
		"Resource\\Graph\\Item_Bread.png",
		"Resource\\Graph\\Item_Cheese.png",
	};



	constexpr Vector3 kHoldNumOffset = { 15*Game::kWindowScale,10 * Game::kWindowScale,0.0f };
	//const char* const kFontName = "OCRB";
	const char* const kFontName = "Bauhaus 93";
	constexpr int kThickness = 5*Game::kWindowScale;
	constexpr int kSize = 20 * Game::kWindowScale;
}
ItemCursor::ItemCursor():
	m_selectIndex(0),
	m_showSelectIndex(m_selectIndex),
	m_cursorHandle(-1),
	m_cursorPosition(GetSelectPos(0)),
	m_pad(Input::Pad::Invalid)
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
	m_itemBase = BlendManager();
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
	// 選択中インデックスの更新処理
	NormalizeIndex();

}

void ItemCursor::UpdateCursor()
{
	// 目標のスロット座標までカーソルの位置を補間
	Vector3 desirePos = GetSelectPos(m_showSelectIndex);
	Vector3 differ = desirePos - m_cursorPosition;
	float deltaTime = TimeManager::GetRawDeltaTime();
	float lerpValue = MyMath::Clamp(deltaTime * kCursorLerpSpeed, 0.0f, 1.0f);
	if (differ.GetSqLength() < MyMath::Epsilon) {
		m_cursorPosition = desirePos;
	}
	else {
		m_cursorPosition += differ * lerpValue;
	}

}

void ItemCursor::UpdateToInput()
{
	// コントローラーが割り当てられているとき処理を行う
	if (m_pad == Input::Pad::Invalid)return;
	// 入力に応じて選択中のインデックスを更新
	if (Input::IsPressed(Input::Button::Left, m_pad)) {
		m_selectIndex--;
	}
	if (Input::IsPressed(Input::Button::Right, m_pad)) {
		m_selectIndex++;
	}
	if (!m_isBlendMenu)return;
	if (Input::IsPressed(Input::Button::Y, m_pad)) {
		if (m_isBlendMenu) {
			//ChangePadState(PadManager::PadState::Player);
			Select(m_slots[m_selectIndex]->m_type);
		}
		else {
			//ChangePadState(PadManager::PadState::ItemMenu);
		}
		m_isBlendMenu ^= 1;
	}

	if (Input::IsPressed(Input::Button::A, m_pad) && m_isBlendMenu) {
		Cancel();
		m_isBlendMenu = false;
	}

	if (Input::IsPressed(Input::Button::B, m_pad)&&m_isBlendMenu) {

		if (m_slots[m_selectIndex]->m_type!= BlendManager::Type::Invalid)
		if (m_slots[m_selectIndex]->GetHoldNum() > 0)
		m_slots[m_selectIndex]->m_select ^= 1;

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
	std::vector<int> selected;
	// 選択中のアイテムの配列を取得
	for (int i = 0; i < m_slots.size();i++) {
		if (m_slots[i]->m_type == BlendManager::Type::Invalid)continue;
		if (!m_slots[i]->m_select)continue;
		if (m_slots[i]->GetHoldNum()<=0)continue;
		selected.push_back(i);
	}
	// 何も選択していなければreturn
	if (selected.empty())return;
	for (int& select : selected) {
		m_slots[select]->Sub();
		m_slots[select]->m_select = false;
	}
}

void ItemCursor::Draw()
{

	int handle = FontManager::GetInstance().GetFontHandle(kFontName, kSize, kThickness);

	for (int i = 0; i < kSlotMax;i++) {
		int holdNum = m_slots[i]->GetHoldNum();
		// スロットの描画処理を行う
		m_slots[i]->Draw();
		if (m_slots[i]->m_select) {
			continue;
		}
			//DrawRotaGraph(graphPos.x, graphPos.y, kCursorScale, 0, m_itemHandles[static_cast<int>(m_slots[i]->m_type)], TRUE);
		if (!holdNum)continue;
		
		Vector3 textPos = GetSelectPos(i) + kHoldNumOffset;
		// 所持数のテキストを用意
		std::string numText = std::to_string(holdNum);
		// 文字数を取得
		int length=numText.length();
		textPos.x -= kHoldNumOffset.x * length;
		std::string holdText = "x"+numText;

		DrawStringToHandle(textPos.x, textPos.y, holdText.c_str(), Color::kWhite, handle);
	}
		DrawRotaGraph(m_cursorPosition.x, m_cursorPosition.y, kCursorScale, 0, m_cursorHandle, TRUE);

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

bool ItemCursor::Select(const BlendManager::Type& type)
{
	// すでに選択済みなら
	if (IsSelected()) {
		bool selected = false;

		selected = BlendItem(m_selected[0], m_selected[1]);

	}

	for (int i = 0; i < kSelectMax; i++) {
		if (m_selected[i] != BlendManager::Type::Invalid)continue;
		m_selected[i] = type;
		return true;
	}

	return false;
}

bool ItemCursor::IsSelected()
{
	bool selected = true;
	for (int i = 0; i < kSelectMax; i++) {
		if (m_selected[i] != BlendManager::Type::Invalid)continue;
		selected = false;
		break;
	}

	return selected;
}

bool ItemCursor::CheckEmptySlot()
{
	for (int i = 0; i < kSelectMax; i++) {
		if (m_slots[i]->m_type != BlendManager::Type::Invalid)continue;
		return true;
	}

	return false;
}

void ItemCursor::Cancel()
{
	for (int i = 0; i < m_slots.size(); i++) {
		// 選択フラグをfalse
		m_slots[i]->m_select = false;
	}
}

bool ItemCursor::BlendItem(const BlendManager::Type& base, const BlendManager::Type& add)
{
	BlendManager::Type blendResult = m_itemBase.Blend(base, add);
	// 合成結果が不正値なら処理しない
	if (blendResult == BlendManager::Type::Invalid) {

		m_selected.fill(BlendManager::Type::Invalid);
		return false;
	}

	return true;
}
