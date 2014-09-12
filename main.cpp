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
		Variant result2 = nextGen->evaluate(parameters);
	}

	return 0;
}

