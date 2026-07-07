#pragma once
struct ItemData
{
public:
	enum class Type {
		Invalid = -1,
		Apple,
		Beer,
		Bread,
		Cheese,
		CheeseBread,
		Max,
	};
	Type m_type;
};