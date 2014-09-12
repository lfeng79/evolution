#pragma once
#include "INode.h"

namespace Evolution
{
	class ParseTree
	{
	public:
		static INode* makeRandomTree(unsigned int parameterCount, unsigned int maxDepth = 4, double fpr = 0.5, double ppr = 0.6);
		static INode* mutate(const INode* t, unsigned int parameterCount, double probchange = 0.1);
		static INode* crossover(INode* t1, INode* t2, double probswap = 0.7, unsigned int top = 1);
	};
}