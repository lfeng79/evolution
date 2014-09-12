#include "Function.h"

namespace Evolution
{
	static Variant IsGreaterFunc(const std::vector<Variant>& parameters)
	{
		if( parameters[0] > parameters[1] ) 
			return 1; 
		else 
			return 0;
	}

	std::vector<Function> BuiltinFunctions;

	//TODO: improve it by initializer lists
	bool InitBuiltinFunctions(std::vector<Function>& builtinFunctions)
	{
		builtinFunctions.push_back( Function( "Add", 2, [](const std::vector<Variant>& parameters){ return parameters[0] + parameters[1]; } ) );
		builtinFunctions.push_back( Function( "Subtract", 2, [](const std::vector<Variant>& parameters){ return parameters[0] - parameters[1]; } ) );
		builtinFunctions.push_back( Function( "Multiply", 2, [](const std::vector<Variant>& parameters){ return parameters[0] * parameters[1]; } ) );
		builtinFunctions.push_back( Function( "Divide", 2, [](const std::vector<Variant>& parameters){ return parameters[0] / parameters[1]; } ) );
		builtinFunctions.push_back( Function( "IfElse", 3, [](const std::vector<Variant>& parameters){ if(parameters[0] > 0) return parameters[1]; else return parameters[2]; } ) );
		builtinFunctions.push_back( Function( "IsGreater", 2, IsGreaterFunc ) );

		return true;
	}
	static bool builtinfuctionInitialized = InitBuiltinFunctions(BuiltinFunctions);
}