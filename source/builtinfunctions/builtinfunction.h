#ifndef BUILTINFUNCTION_H
#define BUILTINFUNCTION_H

#include "../rpncode.h"
#include "../calculatingexceptions.h"
#include "mathutils.h"

#define _USE_MATH_DEFINES
#include <qmath.h>

// Template and interface class for calculation sub-classes
class BuiltInFunction
{
public:
	// Class for separate calculation mechanism
	class FunctionCalculator
	{
	public:
		virtual RpnOperand calculate(QString functionName, QList<RpnOperand> actualArguments) = 0;
		virtual QList<RpnArgument> functionArguments(const QString &name) = 0;
	};

	// Common constructor for registration of sub-classes
	BuiltInFunction(QString functionName)
	{
		functions().insert(functionName, this);
	}

	// Hash of existing functions
	static QHash<QString, BuiltInFunction*> &functions()
	{
		static QHash<QString, BuiltInFunction*> functionsHash;
		return functionsHash;
	}

	// Calculating everything
	virtual RpnOperand calculate(FunctionCalculator* calculator, QList<RpnOperand> actualArguments) = 0;
	// Arguments for calling function
	virtual QList<RpnArgument> requiredArguments() = 0;
};

#endif // BUILTINFUNCTION_H