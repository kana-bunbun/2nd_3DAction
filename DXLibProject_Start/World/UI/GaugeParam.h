#pragma once
#include"../../Utility/Game.h"
#include"../../Utility/Vector3.h"

namespace GaugeParam {
	constexpr float kPlayerGaugeScale = 0.3f * Game::kWindowScale;
	constexpr float kDragonGaugeScale = kPlayerGaugeScale * 0.8f;

	const char* const kFilePath = "Resource\\UI\\";

	const char* const kPlayer = "Player";
	const char* const kDragon = "Doragon";
	const char* const kFacePath = "Face.png";
	const char* const kBackPath = "GaugeBack.png";
	const char* const kFaceBackPath = "FaceBack.png";

	// 顔画像の描画をする際の単位スケール
	constexpr float kScale = 1.2f;
	constexpr float kPlayerFaceScale = 0.77f * kScale;
	constexpr float kDragonFaceScale = kPlayerFaceScale * 0.9f;
	// 背景として描画する円の大きさ
	constexpr float kPlayerRadius = 310 * kPlayerFaceScale * GaugeParam::kPlayerGaugeScale;
	constexpr float kDragonRadius = kPlayerRadius;
	// 背景の枠として描画する円の大きさ
	// ゲージを描画する座標
	constexpr Vector3 kPlayerGaugePos = { Game::kScreenWidth - (1200 * GaugeParam::kPlayerGaugeScale), Game::kScreenHeight - (250 * GaugeParam::kPlayerGaugeScale), 0 };
	constexpr Vector3 kPlayerFacePos = Vector3(kPlayerGaugePos.x, kPlayerGaugePos.y-35*Game::kWindowScale, kPlayerGaugePos.z);
	constexpr Vector3 kDragonGaugePos = Vector3(kPlayerGaugePos.x+50*Game::kWindowScale, kPlayerGaugePos.y - 160 * Game::kWindowScale, kPlayerGaugePos.z);
	constexpr Vector3 kDragonFacePos = Vector3(kDragonGaugePos.x, kDragonGaugePos.y - 28 * Game::kWindowScale, kDragonGaugePos.z);
	// ゲージ同士の距離
	constexpr float kDiffer = -150 * GaugeParam::kPlayerGaugeScale;
}