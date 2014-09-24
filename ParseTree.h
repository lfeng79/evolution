#pragma once
#include "INode.h"

namespace Evolution
{
	class ParseTree
	{
	public:
		static INode* makeRandomTree(unsigned int parameterCount, unsigned int maxDepth = 4, double fpr = 0.5, double ppr = 0.6);
		static INode* mutate(const INode* t, unsigned int parameterCount, double probchange = 0.1);
		static INode* crossover(const INode* t1, const INode* t2, double probswap = 0.7, bool isTop = true);
		static INode* clone(const INode* t);
	};
}