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
	// initialize random seed
	static bool randomSeedInitialized = InitializeRandomSeed();

	INode* ParseTree::makeRandomTree(unsigned int parameterCount, unsigned int maxDepth, double fpr, double ppr)
	{
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

	INode* ParseTree::mutate(const INode* t, unsigned int parameterCount, double probchange)
	{
		INode* result = nullptr;
		double dRandom = static_cast<double>( rand() ) / RAND_MAX;

		if(dRandom < probchange)
		{
			result = makeRandomTree(parameterCount);
		}
		else
		{
			if(typeid(*t) == typeid(ExpressionNode))
			{
				const ExpressionNode* expNode = static_cast<const ExpressionNode*>(t);
				Function function = expNode->ExpFunction();
				std::list<INode*> children;
				for(std::list<INode*>::const_iterator it = expNode->Children().begin(); it != expNode->Children().end(); it++)
				{
					children.push_back( mutate(*it, parameterCount, probchange) );
				}
				
				result = new ExpressionNode(function, children);
			}
			else if(typeid(*t) == typeid(ParamNode))
			{
				result = new ParamNode( *static_cast<const ParamNode*>(t) );
			}
			else if(typeid(*t) == typeid(ConstNode))
			{
				result = new ConstNode( *static_cast<const ConstNode*>(t) );
			}
		}

		return result;
	}

	INode* ParseTree::crossover(INode* t1, INode* t2, double probswap, unsigned int top)
	{

		/*def crossover(t1,t2,probswap=0.7,top=1):
			if random( )<probswap and not top:
			return deepcopy(t2)
			else:
			result=deepcopy(t1)
			if isinstance(t1,node) and isinstance(t2,node):
			result.children=[crossover(c,choice(t2.children),probswap,0)
			for c in t1.children]
			return result*/

		return nullptr;
	}
}