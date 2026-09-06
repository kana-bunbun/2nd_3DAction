#include "pch.h"
#include "Vector2.h"
#include <cmath>
#include "../Utility/MyMath.h"

const Vector2 Vector2::zero{ 0.0f, 0.0f };
const Vector2 Vector2::XAxis{ 1.0f, 0.0f };
const Vector2 Vector2::YAxis{ 0.0f, 1.0f };

Vector2 Vector2::operator-() const
{

	return Vector2( -x, -y);
}

Vector2 Vector2::operator+(const Vector2& vec) const
{

	return Vector2( x + vec.x, y + vec.y );
}

Vector2 Vector2::operator-(const Vector2& vec) const
{

	return Vector2(x - vec.x, y - vec.y);
}

Vector2 Vector2::operator*(float scale) const
{

	return Vector2(x * scale, y * scale);
}

Vector2 Vector2::operator/(float scale) const
{

	if (scale == 0) {

		assert( 0 && "0œŽZ: Vector2");
		return Vector2();
	}

	return Vector2(x / scale, y / scale);

}

Vector2& Vector2::operator+=(const Vector2& vec)
{

	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& vec)
{

	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2& Vector2::operator*= (float scale)
{

	x *= scale;
	y *= scale;
	return *this;
}


Vector2& Vector2::operator/= (float scale)
{

	if (scale == 0) {

		assert(0 && "0œŽZ:Vector3");
	}
	x /= scale;
	y /= scale;
	return *this;
}

bool Vector2::operator==(const Vector2& vec) const
{

	return	MyMath::NearlyEqual(x, vec.x) &&
			MyMath::NearlyEqual(y, vec.y);
}

bool Vector2::operator!=(const Vector2& vec) const
{

	// return x != vec.x || y != vec.y;
	return !(*this == vec);

}

float Vector2::GetLength() const
{

	float length = sqrt(x * x + y * y);
	return length;
}

float Vector2::GetSqLength() const
{

	float length = x * x + y * y;
	return length;
}

Vector2 Vector2::GetNormalize() const
{

	Vector2 res;

	// ƒ[ƒƒxƒNƒgƒ‹‚©‚Ç‚¤‚©ƒ`ƒFƒbƒN
	float size = this->GetSqLength();

	if (size == 0.0f) {

		assert(0 && "0œŽZ:Vector3");
		return res;
	}

	size = this->GetLength();

	res.x = x / size;
	res.y = y / size;

	return res;
}

bool Vector2::IsLengthNearlyZero() const
{
	return GetSqLength() < MyMath::Epsilon;
}

float Vector2::Dot(const Vector2& vec) const
{

	return x * vec.x + y * vec.y;
}

VECTOR Vector2::ToVECTOR() const
{

	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);

	vec.x = x;
	vec.y = y;
	vec.z = 0.0f;

	return vec;
}

