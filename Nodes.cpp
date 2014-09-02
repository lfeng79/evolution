#include "Nodes.h"
#include <stdexcept>

namespace Evolution
{
	static Variant IsGreaterFunc(const std::vector<Variant>& parameters)
	{
		if( parameters[0] > parameters[1] ) 
			return 1; 
		else 
			return 0;
	}

	std::vector<ExpressionFunction> BuiltinExpressionFunctions;

	//TODO: improve it by initializer lists
	bool InitBuiltinExpressionFunctions(std::vector<ExpressionFunction>& builtinExpressionFunctions)
	{
		builtinExpressionFunctions.push_back( ExpressionFunction( "Add", 2, [](const std::vector<Variant>& parameters){ return parameters[0] + parameters[1]; } ) );
		builtinExpressionFunctions.push_back( ExpressionFunction( "Subtract", 2, [](const std::vector<Variant>& parameters){ return parameters[0] - parameters[1]; } ) );
		builtinExpressionFunctions.push_back( ExpressionFunction( "Multiply", 2, [](const std::vector<Variant>& parameters){ return parameters[0] * parameters[1]; } ) );
		builtinExpressionFunctions.push_back( ExpressionFunction( "Divide", 2, [](const std::vector<Variant>& parameters){ return parameters[0] / parameters[1]; } ) );
		builtinExpressionFunctions.push_back( ExpressionFunction( "IfElse", 3, [](const std::vector<Variant>& parameters){ if(parameters[0] > 0) return parameters[1]; else return parameters[2]; } ) );
		builtinExpressionFunctions.push_back( ExpressionFunction( "IsGreater", 2, IsGreaterFunc ) );

		return true;
	}
	static bool builtinfuctionInitialized = InitBuiltinExpressionFunctions(BuiltinExpressionFunctions);

	ExpressionNode::ExpressionNode(const std::string& functionName, const std::list<INode*>& children)
	{
		int index = 0;
		for(; index < BuiltinExpressionFunctions.size(); index++)
		{
			if(BuiltinExpressionFunctions[index].Name() == functionName)
				break;
		}
		if(index == BuiltinExpressionFunctions.size())
			throw std::runtime_error("Unable to find builtin function named: " + functionName + ".");

		m_function = BuiltinExpressionFunctions[index];

		if(m_function.ParamCount() != children.size())
			throw std::runtime_error("The children count does not match the parameter count required by function: " + m_function.Name() + ".");

		m_children = children;
	}

	ExpressionNode::ExpressionNode(const ExpressionFunction& function, const std::list<INode*>& children)
	{
		m_function = function;

		if(m_function.ParamCount() != children.size())
			throw std::runtime_error("The children count does not match the parameter count required by function: " + function.Name() + ".");

		m_children = children;
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