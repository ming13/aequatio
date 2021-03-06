#include "besttrial.h"

#include <ctime>

namespace BuiltIn {
namespace Optimization {

namespace
{
	BestTrial instance;
}

BestTrial::BestTrial() :
	Function("best_trial")
{
}

Rpn::Operand BestTrial::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	// Initialize algorithm variables
	m_calculator = calculator;
	m_functionName = actualArguments.at(0).value.value<QString>();
	m_sourcePoint = Rpn::Vector::toOneDimensional(actualArguments.at(1).value.value<Rpn::Vector>());
	m_decreaseCoefficient = actualArguments.at(2).value.value<Number>();
	m_stepsCount = actualArguments.at(3).value.value<Number>();
	m_maximumIterationsCount = actualArguments.at(4).value.value<Number>();
	m_minimumStepSize = actualArguments.at(5).value.value<Number>();
	m_stepSize = 1;

	// Check values of variables for currect algorithm work
	if (m_calculator->functionArguments(m_functionName).size() != m_sourcePoint.size()) {
		THROW(EWrongArgumentsCount(QObject::tr("Source point"), m_calculator->functionArguments(m_functionName).size()));
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

QList<Rpn::Argument> BestTrial::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments
		<< Rpn::Argument(Rpn::OperandFunctionName, QString(), QVariant::fromValue(Rpn::ArbitraryArgumentsCount))
		<< Rpn::Argument(Rpn::OperandVector)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType BestTrial::returnValueType()
{
	return Rpn::OperandVector;
}

QList<Number> BestTrial::findMinimum()
{
	int iterationCount = 0;

	forever {
		QList<QList<Number> > randomPoints;
		for (int i = 0; i < m_stepsCount; i++) {
			randomPoints << MathUtils::generateRandomNumbers(m_sourcePoint.size(), -1, 1);
		}

		QList<QList<Number> > currentPoints;
		for (int i = 0; i < m_stepsCount; i++) {
			currentPoints << MathUtils::addVectorToVector(
				m_sourcePoint,
				MathUtils::multiplyVectorByNumber(
					MathUtils::divideVectorByNumber(randomPoints.at(i), MathUtils::vectorNorm(randomPoints.at(i))),
					m_stepSize
				)
			);
		}

		QList<Number> currentPoint = getPointOfFunctionMinimum(currentPoints);

		if (calculateFunction(currentPoint) < calculateFunction(m_sourcePoint)) {
			m_sourcePoint = currentPoint;
			iterationCount++;

			if (iterationCount < m_maximumIterationsCount) {
				continue;
			}
			else {
				// Exit condition
				return m_sourcePoint;
			}
		}


	if (m_stepSize <= m_minimumStepSize) {
			// Exit condition
			return m_sourcePoint;
		}
		else {
			m_stepSize *= m_decreaseCoefficient;
		}
	}
}

// Returns point in which function has minimum value
QList<Number> BestTrial::getPointOfFunctionMinimum(QList<QList<Number> > points)
{
	QList<Number> result = points.first();

	foreach (QList<Number> point, points) {
		if (calculateFunction(point) < calculateFunction(result)) {
			result = point;
		}
	}

	return result;
}

Number BestTrial::calculateFunction(QList<Number> arguments)
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
