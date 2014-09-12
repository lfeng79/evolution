#include "Nodes.h"
#include <stdexcept>

namespace Evolution
{
	ExpressionNode::ExpressionNode(const Function& function, const std::list<INode*>& children)
	{
		m_function = function;

		if(m_function.ParamCount() != children.size())
			throw std::runtime_error("The children count does not match the parameter count required by function: " + function.Name() + ".");

		m_children = children;
	}

	ExpressionNode::~ExpressionNode()
	{
		for (std::list<INode*>::iterator it = m_children.begin(); it != m_children.end(); it++)
		{
			delete (*it);
		}
	}

	Variant ExpressionNode::evaluate(const std::vector<Variant>& parameters)
	{
		std::vector<Variant> results;
		results.reserve( m_children.size() );
		for (std::list<INode*>::iterator it = m_children.begin(); it != m_children.end(); it++)
		{
			results.push_back( (*it)->evaluate(parameters) );
		}

		return m_function(results);
	}
}