#include "adaptiverandom.h"

#include <ctime>

namespace BuiltIn {
namespace Optimization {

namespace
{
	AdaptiveRandom instance;
}

AdaptiveRandom::AdaptiveRandom() :
	Function("adaptive_random")
{
}

Rpn::Operand AdaptiveRandom::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	// Initialize algorithm variables
	m_calculator = calculator;
	m_functionName = actualArguments.at(0).value.value<QString>();
	m_sourcePoint = Rpn::Vector::toOneDimensional(actualArguments.at(1).value.value<Rpn::Vector>());
	m_accelerationCoefficient = actualArguments.at(2).value.value<Number>();
	m_decreaseCoefficient = actualArguments.at(3).value.value<Number>();
	m_wrongStepsCount = actualArguments.at(4).value.value<Number>();
	m_maximumIterationsCount = actualArguments.at(5).value.value<Number>();
	m_minimumStepSize = actualArguments.at(6).value.value<Number>();
	m_stepSize = 1;

	// Check values of variables for currect algorithm work
	if (m_calculator->functionArguments(m_functionName).size() != m_sourcePoint.size()) {
		THROW(EWrongArgumentsCount(QObject::tr("Source point"), m_calculator->functionArguments(m_functionName).size()));
	}
	if (m_accelerationCoefficient <= 1) {
		THROW(EWrongArgument(QObject::tr("acceleration coefficient"), QObject::tr("more than 1")) )
	}
	if ((m_decreaseCoefficient <= 0) || (m_decreaseCoefficient >= 1)) {
		THROW(EWrongArgument(QObject::tr("decrease coefficient"), QObject::tr("more than 0 and less than 1")) )
	}

	// Initialize random, random number generator from MathUtils needs it
	srand(time(NULL));

	Rpn::Operand result;
	result.type = Rpn::OperandVector;
	result.value = QVariant::fromValue(Rpn::Vector::fromOneDimensional(findMinimum()));
	return result;
}

QList<Rpn::Argument> AdaptiveRandom::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments
		<< Rpn::Argument(Rpn::OperandFunctionName, QString(), QVariant::fromValue(Rpn::ArbitraryArgumentsCount))
		<< Rpn::Argument(Rpn::OperandVector)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType AdaptiveRandom::returnValueType()
{
	return Rpn::OperandVector;
}

QList<Number> AdaptiveRandom::findMinimum()
{
	int failCount = 1;
	int iterationCount = 0;

	forever {
		QList<Number> randomPoint = MathUtils::generateRandomNumbers(m_sourcePoint.size(), -1, 1);

		QList<Number> currentPoint = MathUtils::addVectorToVector(
			m_sourcePoint,
			MathUtils::multiplyVectorByNumber(
				MathUtils::divideVectorByNumber(randomPoint, MathUtils::vectorNorm(randomPoint)),
				m_stepSize
			)
		);

		if (calculateFunction(currentPoint) < calculateFunction(m_sourcePoint)) {
			QList<Number> newPoint = MathUtils::addVectorToVector(
				m_sourcePoint,
				MathUtils::multiplyVectorByNumber(
					MathUtils::subtractVectorFromVector(currentPoint, m_sourcePoint),
					m_accelerationCoefficient
				)
			);

			if (calculateFunction(newPoint) < calculateFunction(m_sourcePoint)) {
				m_sourcePoint = newPoint;
				m_stepSize *= m_accelerationCoefficient;
				iterationCount++;

				if (iterationCount < m_maximumIterationsCount) {
					failCount = 1;
					continue;
				}
				else {
					// Exit condition
					return m_sourcePoint;
				}
			}
		}

		if (failCount < m_wrongStepsCount) {
			failCount++;
		}
		else if (m_stepSize <= m_minimumStepSize) {
			// Exit condition
			return m_sourcePoint;
		}
		else {
			m_stepSize *= m_decreaseCoefficient;
			failCount = 1;
		}
	}
}

Number AdaptiveRandom::calculateFunction(QList<Number> arguments)
{
	QList<Rpn::Operand> functionArguments;

	foreach (Number argument, arguments) {
		Rpn::Operand functionArgument(Rpn::OperandNumber, argument);
		functionArguments << functionArgument;
	}

	Rpn::Operand result = m_calculator->calculate(m_functionName, functionArguments);
	return result.value.value<Number>();
}

} // namespace
} // namespace
