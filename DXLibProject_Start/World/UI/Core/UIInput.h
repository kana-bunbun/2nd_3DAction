#pragma once

/// <summary>
/// Sceneで入力した結果を構造体にまとめる
/// その結果をUIに渡すことで入力処理をUIに持たせず処理させることができる
/// </summary>
struct UIInput
{
public:
	bool up=false;
	bool down=false;
	bool right=false;
	bool left=false;
	bool decide=false;
	bool cancel=false;
};

