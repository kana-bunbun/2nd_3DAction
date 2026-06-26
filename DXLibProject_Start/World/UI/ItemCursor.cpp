#include "ItemCursor.h"
#include"../../Utility/Game.h"
#include"../../Utility/Vector3.h"
#include"../../Utility/MyMath.h"
#include"../../System/FontManager.h"
#include<string>
#include"../../Utility/Color.h"
#include"../../System/TimeManager.h"
#include"../Object/Item/ItemType.h"
namespace {

	// スロット表示する際の中心座標
	constexpr Vector3 kSlotCenterPos = { Game::kScreenWidth /  3.0f,Game::kScreenHeight * 0.9f,0.0f };
	// スロットのスケール
	constexpr float kSlotScale = 0.05f * Game::kWindowScale;
	constexpr float kSlotDistance = 100.0f * Game::kWindowScale;

	constexpr float kCursorScale = 1.3f * Game::kWindowScale;
	constexpr float kCursorLerpSpeed = 30.0f;
	const char* const kBackGroundPath = "Resource\\UI\\Icon Background.png";
	const char* const kCursorPath = "Resource\\UI\\ItemCursor.png";
	const char* const kItemPath[static_cast<int>(ItemBase::Type::Max)] =
	{
		"Resource\\UI\\Item_Apple.png",
		"Resource\\UI\\Item_Beer.png",
		"Resource\\UI\\Item_Bread.png",
		"Resource\\UI\\Item_Cheese.png",
	};



	constexpr Vector3 kHoldNumOffset = { 15*Game::kWindowScale,10 * Game::kWindowScale,0.0f };
	constexpr Vector3 kSelectIconOffset = { 0.0f,-70 * Game::kWindowScale,0.0f };
	const char* const kFontName = "OCRB";
	//const char* const kFontName = "Bauhaus 93";
	constexpr int kThickness = 5*Game::kWindowScale;
	constexpr int kSize = 20 * Game::kWindowScale;
}
ItemCursor::ItemCursor():
	m_backGroundHandle(-1),
	m_selectIndex(0),
	m_showSelectIndex(m_selectIndex),
	m_cursorHandle(-1),
	m_cursorPosition(GetSelectPos(0)),
	m_pad(Input::Pad::Invalid),
	m_itemHandles()
{
	m_backGroundHandle = LoadGraph(kBackGroundPath);
	m_cursorHandle = LoadGraph(kCursorPath);
	m_itemArray.fill(nullptr);
	for (int i = 0; i < m_itemArray.size(); i++) {
		int num = (m_itemArray.size() + i) % m_itemArray.size();
		int type = (static_cast<int>(ItemBase::Type::Max) + i) % static_cast<int>(ItemBase::Type::Max);
		for (int j = 0; j < type * i * i+1; j++) {
		AddItem(static_cast<ItemBase::Type>(type));
		}
	}
	m_itemHandles.fill(-1);
	for (int i = 0; i < m_itemHandles.size(); i++) {
		m_itemHandles[i] = LoadGraph(kItemPath[i]);
	}
}

ItemCursor::~ItemCursor()
{
	DeleteGraph(m_backGroundHandle);
	m_backGroundHandle = -1;
	DeleteGraph(m_cursorHandle);
	m_cursorHandle = -1;
	for (int& handle:m_itemHandles) {
		DeleteGraph(handle);
		handle = -1;
	}
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
			UseItem();
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

		if (m_itemArray[m_selectIndex])
		if (m_itemArray[m_selectIndex]->m_holdNum > 0)
		m_itemArray[m_selectIndex]->m_select ^= 1;
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
	for (int i = 0; i < m_itemArray.size();i++) {
		if (!m_itemArray[i])continue;
		if (!m_itemArray[i]->m_select)continue;
		if (m_itemArray[i]->m_holdNum<=0)continue;
		selected.push_back(i);
	}
	// 何も選択していなければreturn
	if (selected.empty())return;
	for (int& select : selected) {
		m_itemArray[select]->m_holdNum--;
		m_itemArray[select]->m_select = false;
	}
}

void ItemCursor::Draw()
{

	int handle = FontManager::GetInstance().GetFontHandle(kFontName, kSize, kThickness);

	for (int i = 0; i < kSlotMax;i++) {
		Vector3 backGroundPosition = GetSelectPos(i);
		DrawRotaGraph(backGroundPosition.x, backGroundPosition.y, kSlotScale, 0, m_backGroundHandle, TRUE);

		if (!m_itemArray[i])continue;
		int holdNum = m_itemArray[i]->m_holdNum;
		if (!holdNum)continue;
		Vector3 graphPos = backGroundPosition;
		if (m_itemArray[i]->m_select) {
			graphPos += kSelectIconOffset;
			DrawRotaGraph(graphPos.x, graphPos.y, kCursorScale, 0, m_itemHandles[static_cast<int>(m_itemArray[i]->m_type)], TRUE);
			continue;
		}
			DrawRotaGraph(graphPos.x, graphPos.y, kCursorScale, 0, m_itemHandles[static_cast<int>(m_itemArray[i]->m_type)], TRUE);
		
		Vector3 textPos = backGroundPosition + kHoldNumOffset;
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

bool ItemCursor::AddItem(const ItemBase::Type& type)
{
	// 同じアイテムをすでに所持しているときは所持数に加算する
	for (int i = 0; i < m_itemArray.size(); i++) {
		if (!m_itemArray[i])continue;
		if (m_itemArray[i]->m_type != type)continue;
		// 所持数に加算
		m_itemArray[i]->m_holdNum++;
		// 追加できたのでtrue
		return true;
	}
	// 同じアイテムを所持していないとき
	// nullptrの要素を探して追加
	for (int i = 0; i < m_itemArray.size(); i++) {
		if (m_itemArray[i])continue;
		// アイテム情報を生成し追加
		m_itemArray[i] = new Item(type);
		
		// 追加できたのでtrue
		return true;
	}

	// 追加できなかったのでfalse
	return false;
}

void ItemCursor::Cancel()
{
	for (int i = 0; i < m_itemArray.size(); i++) {
		if (!m_itemArray[i])continue;
		// 選択フラグをfalse
		m_itemArray[i]->m_select = false;
	}
}
