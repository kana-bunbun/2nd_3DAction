#pragma once
class CharaGauge
{
public:
	CharaGauge()=default;
	~CharaGauge()=default;

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	// キャラクターの顔画像
	int m_faceHandle;
	// 顔画像の背景画像
	int m_faceBackHandle;
	// ゲージの背景画像
	int m_backHandle;

};

