#include "Nodes.h"

int main(int argc, char *argv[])
{
	using namespace Evolution;

	ConstNode constNode(1);
	std::list<INode*> nodes;
	nodes.push_back(&constNode);
	Evolution::ExpressionNode node("Add", nodes);

	return 0;
}
