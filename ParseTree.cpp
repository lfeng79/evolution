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

	template<typename T>
	static T listAt(const std::list<T> list, unsigned int index)
	{
		unsigned int i = 0;
		T result;
		for(std::list<T>::const_iterator it = list.begin(); it != list.end(); it++)
		{
			if(i == index)
			{
				result = *it;
				break;
			}
			i++;
		}

		if(i < index)
			result = *(list.end());

		return result;
	}

	INode* ParseTree::crossover(const INode* t1, const INode* t2, double probswap, bool isTop)
	{
		INode* result = nullptr;
		double dRandom = static_cast<double>( rand() ) / RAND_MAX;

		if(dRandom < probswap && !isTop)
		{
			result = clone(t2);
		}
		else
		{
			if(typeid(*t1) == typeid(ExpressionNode) && typeid(*t2) == typeid(ExpressionNode))
			{
				const ExpressionNode* expNode1 = static_cast<const ExpressionNode*>(t1);
				Function function = expNode1->ExpFunction();
				std::list<INode*> children;
				for(std::list<INode*>::const_iterator it1 = expNode1->Children().begin(); it1 != expNode1->Children().end(); it1++)
				{
					const ExpressionNode* expNode2 = static_cast<const ExpressionNode*>(t2);
					children.push_back( crossover(*it1, listAt( expNode2->Children(), rand() % expNode2->Children().size() ), probswap, false) );
				}
				
				result = new ExpressionNode(function, children);
			}
			else
			{
				result = clone(t1);
			}
		}

		return result;
	}

	INode* ParseTree::clone(const INode* t)
	{
		return mutate(t, 0, 0);
	}
}