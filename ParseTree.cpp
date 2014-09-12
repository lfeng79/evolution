#include "ParseTree.h"
#include "Nodes.h"
#include <stdlib.h>
#include <time.h>

namespace Evolution
{
	static bool InitializeRandomSeed()
	{
		srand( static_cast<unsigned int>(time(nullptr)) );
		return true;
	}

	INode* ParseTree::makeRandomTree(unsigned int parameterCount, unsigned int maxDepth, double fpr, double ppr)
	{
		// initialize random seed
		static bool randomSeedInitialized = InitializeRandomSeed();

		INode* node = nullptr;

		/* generate random number between 0 and 1: */
		double dRandom = static_cast<double>( rand() ) / RAND_MAX;

		if(dRandom < fpr && maxDepth > 0)
		{
			Function function = BuiltinFunctions.at( rand() % BuiltinFunctions.size() );
			std::list<INode*> children;
			for(unsigned int i = 0; i < function.ParamCount(); i++)
			{
				children.push_back( makeRandomTree(parameterCount, maxDepth-1, fpr, ppr) );
			}

			node = new ExpressionNode(function, children);
		}
		else if(dRandom < ppr)
		{
			node = new ParamNode(rand() % parameterCount);
		}
		else
		{
			node = new ConstNode(rand() % 10);
		}

		return node;
	}
}