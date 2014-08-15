#include "Nodes.h"
#include <map>
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

	static std::map<const std::string, ExpressionFunction> BuiltinExpressionFunctions;

	//TODO: improve it by initializer lists
	bool InitBuiltinExpressionFunctions(std::map<const std::string, ExpressionFunction>& builtinExpressionFunctions)
	{
		builtinExpressionFunctions["Add"] = [](const std::vector<Variant>& parameters){ return parameters[0] + parameters[1]; };
		builtinExpressionFunctions["Subtract"] = [](const std::vector<Variant>& parameters){ return parameters[0] - parameters[1]; };
		builtinExpressionFunctions["Multiply"] = [](const std::vector<Variant>& parameters){ return parameters[0] * parameters[1]; };
		builtinExpressionFunctions["Divide"] = [](const std::vector<Variant>& parameters){ return parameters[0] / parameters[1]; };
		builtinExpressionFunctions["IfElse"] = [](const std::vector<Variant>& parameters){ if(parameters[0] > 0) return parameters[1]; else return parameters[2]; };
		builtinExpressionFunctions["IsGreater"] = IsGreaterFunc;

		return true;
	}
	static bool builtinfuctionInitialized = InitBuiltinExpressionFunctions(BuiltinExpressionFunctions);

	ExpressionNode::ExpressionNode(const std::string& name, const std::list<INode*>& children)
	{
		if( BuiltinExpressionFunctions.find(name) == BuiltinExpressionFunctions.end() )
			throw std::runtime_error("Unable to find builtin function: " + name + ".");

		m_name = name;
		m_function = BuiltinExpressionFunctions[name];
		m_children = children;
	}

	ExpressionNode::ExpressionNode(const std::string& name, const ExpressionFunction& function, const std::list<INode*>& children)
	{
		if( BuiltinExpressionFunctions.find(name) != BuiltinExpressionFunctions.end() )
			throw std::runtime_error("Function '" + name + "' already registered as a builtin function.");

		m_name = name;
		m_function = function;
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