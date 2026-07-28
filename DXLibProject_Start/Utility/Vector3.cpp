#include "Vector3.h"
#include<DxLib.h>
#include<math.h>
#include"MyMath.h"
#include<cassert>
const Vector3 Vector3::zero{ 0.0f, 0.0f, 0.0f };
const Vector3 Vector3::XAxis{ 1.0f, 0.0f, 0.0f };
const Vector3 Vector3::YAxis{ 0.0f, 1.0f, 0.0f };
const Vector3 Vector3::ZAxis{ 0.0f, 0.0f, 1.0f };

Vector3 Vector3::operator=(float value) const
{
	return Vector3(value, value, value);
}
Vector3 Vector3::operator-()const {
	return Vector3(-x, -y, -z);
}
Vector3 Vector3::operator+(const Vector3& vec)const {
	return Vector3(x+vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator+(const VECTOR& vec) const
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3& Vector3::operator+=(const VECTOR& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}
Vector3 Vector3::operator-(const VECTOR& vec) const
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}
Vector3& Vector3::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}
Vector3& Vector3::operator-=(const VECTOR& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}
Vector3 Vector3::operator*(float value) const
{
	return Vector3(x * value, y * value, z * value);
}

Vector3& Vector3::operator*=(float value) 
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vector3 Vector3::operator/(float value) const
{
	// 0œZ‚ğ‚µ‚È‚¢‚æ‚¤‚É‚·‚é
	if (!value) {
		assert(0 && "Vector3 : 0œZ");
		return Vector3();
	}
	return Vector3(x / value, y / value, z / value);
}

Vector3& Vector3::operator/=(float value)
{
	// 0œZ‚ğ‚µ‚È‚¢‚æ‚¤‚É‚·‚é
	if (!value) {
		assert(0 && "Vector3 : 0œZ");
	}
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

bool Vector3::operator==(const Vector3& vec) const
{
	// ‚¢‚¸‚ê‚©‚Ì•ûŒü‚Ì’l‚Ì‚¤‚¿1‚Â‚Å‚àˆÙ‚È‚é‚à‚Ì‚ª‚ ‚ê‚Îfalse
	if (x != vec.x)return false;
	if (y != vec.y)return false;
	if (z != vec.z)return false;

	return true;
}

bool Vector3::operator!=(const Vector3& vec) const
{
	// 2‚Â‚ÌƒxƒNƒgƒ‹‚ª“™‚µ‚¯‚ê‚Îfalse
	if (*this == vec)return false;
	return true;
}


float Vector3::GetLength() const
{
	float length = sqrt(GetSqLength());
	return length;
}

float Vector3::GetSqLength() const
{
	float length = (x * x) + (y * y)+(z * z);
	return length;
}

Vector3 Vector3::Normalize() const
{
	Vector3 res;
	float size = this->GetSqLength();
	if (!size) {
		assert(0 && "Vector3 : 0œZ");
		return res;
	}

	size = GetLength();
	res = *this / size;
	return res;
}

bool Vector3::IsLengthNearlyZero() const
{
	return GetSqLength() < MyMath::Epsilon * MyMath::Epsilon;
}

float Vector3::Dot(const Vector3& vec) const
{
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

VECTOR Vector3::ToVECTOR() const
{
	
	VECTOR vec=VGet(0.0f, 0.0f, 0.0f);
	// Še•ûŒü‚Ì’l‚ğİ’è
	vec.x = x;
	vec.y = y;
	vec.z = z;
	// İ’è‚µ‚½’l‚ğ•Ô‚·
	return vec;
}
