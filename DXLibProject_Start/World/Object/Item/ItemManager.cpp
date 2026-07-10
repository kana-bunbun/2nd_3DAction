#include "ItemObjectManager.h"
#include "ItemManager.h"
#include"../../UI/ItemCursor.h"

ItemManager::ItemManager():
	m_pItemCursor(nullptr)

{
	m_pItemCursor = std::make_unique<ItemCursor>();
	m_pItemObjectManager = std::make_unique<ItemObjectManager>();
	m_pItemCursor->SetItemObjectManager(m_pItemObjectManager.get());
}

ItemManager& ItemManager::GetInstance()
{
	// TODO: return ステートメントをここに挿入します
	static ItemManager instance;
	return instance;
}

ItemManager::~ItemManager()
{

}

void ItemManager::Init()
{
	// アイテムスロットの開始処理
	m_pItemCursor->Init();
}

void ItemManager::End()
{
	// アイテムスロットの終了処理
	m_pItemCursor->End();
	// アイテムオブジェクトの終了処理
	m_pItemObjectManager->End();
}

void ItemManager::Update()
{
	// アイテムスロットの更新処理
	m_pItemCursor->Update();
	// アイテムオブジェクトの更新処理
	m_pItemObjectManager->Update();
}

void ItemManager::Draw()
{
	// アイテムスロットの更新処理
	m_pItemCursor->Draw();

	m_pItemObjectManager->Draw();
}
