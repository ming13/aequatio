#include "basicfunctions.h"

namespace BuiltIn {
namespace BasicFunctions{

namespace
{
	Plus instancePlus;
}

Plus::Plus() :
	Function(Rpn::FunctionPlus)
{
}

Rpn::Operand Plus::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = actualArguments.at(0).value.value<Number>() + actualArguments.at(1).value.value<Number>();

	return result;
}

QList<Rpn::Argument> Plus::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber) << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Plus::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Minus instanceMinus;
}

Minus::Minus() :
	Function(Rpn::FunctionMinus)
{
}

Rpn::Operand Minus::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = actualArguments.at(0).value.value<Number>() - actualArguments.at(1).value.value<Number>();

	return result;
}

QList<Rpn::Argument> Minus::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber) << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Minus::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Multiply instanceMultiply;
}

Multiply::Multiply() :
	Function(Rpn::FunctionMultiply)
{
}

Rpn::Operand Multiply::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = actualArguments.at(0).value.value<Number>() * actualArguments.at(1).value.value<Number>();

	return result;
}

QList<Rpn::Argument> Multiply::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber) << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Multiply::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Divide instanceDivide;
}

Divide::Divide() :
	Function(Rpn::FunctionDivide)
{
}

Rpn::Operand Divide::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = actualArguments.at(0).value.value<Number>() / actualArguments.at(1).value.value<Number>();

	return result;
}

QList<Rpn::Argument> Divide::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber) << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Divide::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Power instancePower;
}

Power::Power() :
	Function(Rpn::FunctionPower)
{
}

Rpn::Operand Power::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qPow(actualArguments.at(0).value.value<Number>(), actualArguments.at(1).value.value<Number>());

	return result;
}

QList<Rpn::Argument> Power::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber) << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Power::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	UnaryMinus instanceUnaryMinus;
}

UnaryMinus::UnaryMinus() :
	Function(Rpn::FunctionUnaryMinus)
{
}

Rpn::Operand UnaryMinus::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = -actualArguments.at(0).value.value<Number>();

	return result;
}

QList<Rpn::Argument> UnaryMinus::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType UnaryMinus::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Sine instanceSine;
}

Sine::Sine() :
	Function("sin")
{
}

Rpn::Operand Sine::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qSin(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> Sine::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Sine::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Cosine instanceCosine;
}

Cosine::Cosine() :
	Function("cos")
{
}

Rpn::Operand Cosine::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qCos(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> Cosine::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Cosine::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Tangent instanceTangent;
}

Tangent::Tangent() :
	Function("tan")
{
}

Rpn::Operand Tangent::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qTan(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> Tangent::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Tangent::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Arcsine instanceArcsine;
}

Arcsine::Arcsine() :
	Function("asin")
{
}

Rpn::Operand Arcsine::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qAsin(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> Arcsine::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Arcsine::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Arccosine instanceArccosine;
}

Arccosine::Arccosine() :
	Function("acos")
{
}

Rpn::Operand Arccosine::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qAcos(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> Arccosine::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Arccosine::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	Arctangent instanceArctangent;
}

Arctangent::Arctangent() :
	Function("atan")
{
}

Rpn::Operand Arctangent::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qAtan(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> Arctangent::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Arctangent::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	AbsoluteValue instanceAbsoluteValue;
}

AbsoluteValue::AbsoluteValue() :
	Function("abs")
{
}

Rpn::Operand AbsoluteValue::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qAbs(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> AbsoluteValue::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType AbsoluteValue::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	SquareRoot instanceSquareRoot;
}

SquareRoot::SquareRoot() :
	Function("sqrt")
{
}

Rpn::Operand SquareRoot::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qSqrt(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> SquareRoot::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType SquareRoot::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	NaturalLogarithm instanceNaturalLogarithm;
}

NaturalLogarithm::NaturalLogarithm() :
	Function("ln")
{
}

Rpn::Operand NaturalLogarithm::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qLn(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> NaturalLogarithm::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType NaturalLogarithm::returnValueType()
{
	return Rpn::OperandNumber;
}


namespace
{
	ExponentialFunction instanceExponentialFunction;
}

ExponentialFunction::ExponentialFunction() :
	Function("exp")
{
}

Rpn::Operand ExponentialFunction::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	Q_UNUSED(calculator);

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = qExp(actualArguments.at(0).value.value<Number>());

	return result;
}

QList<Rpn::Argument> ExponentialFunction::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments << Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType ExponentialFunction::returnValueType()
{
	return Rpn::OperandNumber;
}

} // namespace
} // namespace
