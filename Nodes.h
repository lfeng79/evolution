#pragma once

#include "INode.h"
#include <list>
#include <functional>
#include <string>

namespace Evolution
{
	typedef std::function<Variant (const std::vector<Variant>& parameters)> ExpressionFunction;

	class ExpressionNode : public INode
	{
	public:
		ExpressionNode(const std::string& name, const std::list<INode*>& children);
		ExpressionNode(const std::string& name, const ExpressionFunction& function, const std::list<INode*>& children);
		Variant evaluate(const std::vector<Variant>& parameters) override;

	private:
		std::list<INode*> m_children;
		std::string m_name;
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
