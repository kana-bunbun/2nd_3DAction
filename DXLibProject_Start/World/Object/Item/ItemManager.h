#pragma once
#include<memory>
#include"../../../Camera/Camera.h"
class ItemCursor;
class ItemObjectManager;
class ItemManager
{
public:
	static ItemManager& GetInstance();
	~ItemManager();
	
	void Init();
	void End();
	void Update();
	void Draw();


public:
	ItemCursor* GetItemCursor() { return m_pItemCursor.get(); }
	void SetCameraView(const Camera::CameraView& view) { m_view = view; }
	const Camera::CameraView& GetCameraView() { return m_view; }
private:
	ItemManager();
	ItemManager& operator=(const ItemManager&) = delete;
	ItemManager(const ItemManager&) = delete;
	ItemManager& operator=(ItemManager&&)=delete;
	ItemManager(const ItemManager&&) = delete;
private:
	std::unique_ptr<ItemObjectManager>m_pItemObjectManager;
	// アイテムカーソル
	std::unique_ptr<ItemCursor> m_pItemCursor;
	Camera::CameraView m_view;
};

