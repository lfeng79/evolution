#pragma once
#include "Variant.h"
#include <vector>

namespace Evolution
{
	class INode
	{
	public:
		virtual Variant evaluate(const std::vector<Variant>& parameters) = 0;
	};
}