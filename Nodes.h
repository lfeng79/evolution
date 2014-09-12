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
		~ExpressionNode();
		Variant evaluate(const std::vector<Variant>& parameters) override;

		const std::list<INode*>& Children() const { return m_children; }
		Function ExpFunction() const { return m_function; }

	private:
		std::list<INode*> m_children;
		Function m_function;
	};

	class ParamNode : public INode
	{
	public:
		ParamNode(unsigned int index) : m_index(index) {}
		ParamNode(const ParamNode& paramNode) : m_index(paramNode.m_index) {}
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
		ConstNode(const ConstNode& constNode) : m_value(constNode.m_value) {}
		Variant evaluate(const std::vector<Variant>& parameters) override
		{
			return m_value;
		}

	private:
		Variant m_value;
	};
}
