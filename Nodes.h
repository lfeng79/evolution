#pragma once

#include "INode.h"
#include <list>
#include <functional>
#include <string>

namespace Evolution
{
	typedef std::function<Variant (const std::vector<Variant>& parameters)> ExpressionFunctionImp;

	class ExpressionFunction
	{
	public:
		ExpressionFunction() : m_paramCount(0) {}

		ExpressionFunction(const std::string& name, unsigned int paramCount, const ExpressionFunctionImp imp) :
			m_name(name), m_paramCount(paramCount), m_imp(imp) {}

		ExpressionFunction(const ExpressionFunction& expressionFunction) :
			m_name( expressionFunction.Name() ), m_paramCount( expressionFunction.ParamCount() ), m_imp( expressionFunction.Imp() ) {}

		ExpressionFunction& operator=(const ExpressionFunction& expressionFunction)
		{
			m_name = expressionFunction.Name();
			m_paramCount = expressionFunction.ParamCount();
			m_imp = expressionFunction.Imp();

			return *this;
		}

		Variant operator()(const std::vector<Variant>& parameters)
		{
			return m_imp(parameters);
		}

		std::string Name() const { return m_name; }
		unsigned int ParamCount() const { return m_paramCount; }
		ExpressionFunctionImp Imp() const { return m_imp; }

	private:
		std::string m_name;
		unsigned int m_paramCount;
		ExpressionFunctionImp m_imp; 
	};

	extern std::vector<ExpressionFunction> BuiltinExpressionFunctions;

	class ExpressionNode : public INode
	{
	public:
		ExpressionNode(const std::string& functionName, const std::list<INode*>& children);
		ExpressionNode(const ExpressionFunction& function, const std::list<INode*>& children);
		Variant evaluate(const std::vector<Variant>& parameters) override;

	private:
		std::list<INode*> m_children;
		ExpressionFunction m_function;
	};

	class ParamNode : public INode
	{
	public:
		ParamNode(unsigned int index) : m_index(index) {}
		Variant evaluate(const std::vector<Variant>& parameters) override
		{
			return parameters.at(m_index);
		}

	private:
		unsigned int m_index;
	};

	class ConstNode : public INode
	{
	public:
		ConstNode(const Variant& value) : m_value(value) {}
		Variant evaluate(const std::vector<Variant>& parameters) override
		{
			return m_value;
		}

	private:
		Variant m_value;
	};
}
