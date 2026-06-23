#pragma once
#include"../../Utility/Input.h"
namespace {
	// スロットの個数
	constexpr int kSlotNum = 10;
}
class ItemCursor
{
public:
	ItemCursor();
	~ItemCursor();
	void Init();
	void End();
	void Update(float deltaTime);
	void Draw();

public:
	void SetPad(Input::Pad pad) { m_pad = pad; }
private:
	// 背景画像のグラフィックハンドル
	int m_backGroundHandle;
	Input::Pad m_pad;
	int m_selectNum;
};

