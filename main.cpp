#include "ParseTree.h"

int main(int argc, char *argv[])
{
	using namespace Evolution;

	INode* rootNode = ParseTree::makeRandomTree(2);

	std::vector<Variant> parameters;
	parameters.reserve(2);
	parameters.push_back(1);
	parameters.push_back(2);

	Variant result = rootNode->evaluate(parameters);

	return 0;
}

