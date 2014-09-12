#pragma once
#include "INode.h"

namespace Evolution
{
	class ParseTree
	{
	public:
		static INode* makeRandomTree(unsigned int parameterCount, unsigned int maxDepth = 4, double fpr = 0.5, double ppr = 0.6);
	};
}