#include"pch.h"
#include "ItemObjectManager.h"
#include "ItemManager.h"
#include "ItemObjectField.h"
#include"../../UI/ItemCursor.h"
#include"../../Map/MapCreate.h"
#include"../../Map/MapManager.h"
#include"../../../Utility/MyRandom.h"
#include"../../../System/Debug/ProfileScope.h"
#include"../../GameObjectManager.h"
namespace {
	constexpr int kDropItemTypeMax = 4;

	ItemData::Type kDropItemType[kDropItemTypeMax] = { ItemData::Type::Honey,ItemData::Type::Jam,ItemData::Type::ChiliPepper,ItemData::Type::Whiskey };

}
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

void ItemManager::CreateFielditemFloor(int createnum)
{
	std::vector<int>roomIDList = MapCreate::GetInstance().GetRooms();
	for (int i = 0; i < createnum; i++) {
		if (!roomIDList.size())break;
		int randomIndex = MyRandom::Int(0, roomIDList.size()-1);
		int randomID = roomIDList[randomIndex];
		ItemData::Type randomType = kDropItemType[MyRandom::Int(0, kDropItemTypeMax)];;
		if (CreateFieldItem(randomType, MapManager::GetInstance().GetWorldPosFromID(randomID))) {
		roomIDList.erase(roomIDList.begin() + randomIndex);
		}
	}
}

bool ItemManager::CreateFieldItem(const ItemData::Type& type, const Vector3& position)
{
	for (int i = 0; i < m_fieldItems.size(); i++) {
		if (m_fieldItems[i]->IsActive())continue;
		m_fieldItems[i]->Setup(type, position);
		return true;
	}
	ItemObjectField* item = GameObjectManager::GetInstance().CreateObject<ItemObjectField>();
	if (!item)return false;
	m_fieldItems.push_back(item);
	item->Setup(type, position);
	item->SetItemCursor(m_pItemCursor.get());
	return true;
}

