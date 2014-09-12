#pragma once
#include "INode.h"
#include "Function.h"
#include <list>
#include <string>

namespace Evolution
{
	class ExpressionNode : public INode
	{
	public:
		ExpressionNode(const Function& function, const std::list<INode*>& children);
		Variant evaluate(const std::vector<Variant>& parameters) override;

	private:
		std::list<INode*> m_children;
		Function m_function;
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
