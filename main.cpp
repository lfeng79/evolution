#include "ParseTree.h"

int main(int argc, char *argv[])
{
	using namespace Evolution;

	for(int i = 0; i < 10; i++)
	{
		std::vector<Variant> parameters;
		parameters.reserve(2);
		parameters.push_back(1);
		parameters.push_back(2);

		INode* firstGen = ParseTree::makeRandomTree(2);
		Variant result1 = firstGen->evaluate(parameters);

		INode* nextGen = ParseTree::mutate(firstGen, 2);
		delete firstGen;
		Variant result2 = nextGen->evaluate(parameters);

		INode* father = ParseTree::makeRandomTree(2);
		Variant result3 = father->evaluate(parameters);
		INode* mother = ParseTree::makeRandomTree(2);
		Variant result4 = mother->evaluate(parameters);

		INode* child = ParseTree::crossover(father, mother);
		Variant result5 = child->evaluate(parameters);

		INode* clone = ParseTree::clone(father);
		Variant result6 = clone->evaluate(parameters);

		delete father;
		delete mother;
	}

	return 0;
}

