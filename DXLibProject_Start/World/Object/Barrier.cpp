#include "Barrier.h"
#include"../../Utility/Color.h"
namespace {
	// 透明度を変える速さ
	constexpr float kSpeed = 0.1f;
	// 透明度の最大値
	constexpr float kMaxAlpha = 0.7f;
	// 時間の最大値
	constexpr float kMaxTime = 2.0f;
	constexpr float kRadius = 160;
}

Barrier::Barrier(const Vector3& offset):
	m_alpha(0),
	m_time(0),
	m_speed(1),
	m_offset(offset)
{
	m_collision = std::make_unique<Collision::Sphere>(
		m_transform.position,
		kRadius
	);

	MATERIALPARAM Material;
	// マテリアルの設定
	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(0.5f, 0.5f, 1.0f, 0.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);


}

Barrier::~Barrier()
{

}

void Barrier::Init()
{
	m_time = kMaxTime;
}

void Barrier::Update()
{
	m_alpha = CheckAlpha();
	m_time -= kSpeed * m_speed;
	m_time = MyMath::Clamp(m_time, 0.0f, kMaxTime);
}

void Barrier::Draw()
{

	MATERIALPARAM Material;
	// マテリアルの設定
	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(0.5f, 0.5f, 1.0f, 0.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);
	// 透明度を設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_alpha);
	DrawSphere3D(m_transform.position.ToVECTOR(), kRadius, 10, Color::kCyan, 0xffffff, TRUE);
	// 透明度を元に戻す
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	Material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	SetMaterialParam(Material);
}

void Barrier::ResolveCollision(GameObject& other, const Collision::Result & result)
{

}

float Barrier::CheckAlpha()
{
	float res = 0;
	res = -(m_time - 1) * (m_time - 1) + 1;
	res = MyMath::Clamp(res, 0.0f, kMaxAlpha);
	return res;
}
