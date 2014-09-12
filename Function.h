#pragma once
#include "Variant.h"
#include <functional>
#include <vector>

namespace Evolution
{
	typedef std::function<Variant (const std::vector<Variant>& parameters)> FunctionImp;

	class Function
	{
	public:
		Function() : m_paramCount(0) {}

		Function(const std::string& name, unsigned int paramCount, const FunctionImp imp) :
			m_name(name), m_paramCount(paramCount), m_imp(imp) {}

		Function(const Function& function) :
			m_name( function.m_name ), m_paramCount( function.m_paramCount ), m_imp( function.m_imp ) {}

		Function& operator=(const Function& function)
		{
			if(this == &function)
				return *this;
				
			m_name = function.m_name;
			m_paramCount = function.m_paramCount;
			m_imp = function.m_imp;

			return *this;
		}

		Variant operator()(const std::vector<Variant>& parameters)
		{
			return m_imp(parameters);
		}

		std::string Name() const { return m_name; }
		unsigned int ParamCount() const { return m_paramCount; }

	private:
		std::string m_name;
		unsigned int m_paramCount;
		FunctionImp m_imp; 
	};

	extern std::vector<Function> BuiltinFunctions;
}