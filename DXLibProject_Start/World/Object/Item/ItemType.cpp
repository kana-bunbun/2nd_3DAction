#include "ItemType.h"

namespace {
	constexpr int kTypeMax = static_cast<int>(ItemBase::Type::Max);
	constexpr ItemBase::Type kBlendRecipe[kTypeMax][kTypeMax] = {
		{ItemBase::Type::Invalid},		//Appleの組み合わせ
		{},		//Beerの組み合わせ
		{},		//Breadの組み合わせ
		{},		//Cheeseの組み合わせ
		{},		//CheeseBreadの組み合わせ

	};
}

const ItemBase::Type& ItemBase::Blend(const ItemBase::Type& base, const ItemBase::Type& add)
{
	ItemBase::Type result = ItemBase::Type::Invalid;

	return result;
}
