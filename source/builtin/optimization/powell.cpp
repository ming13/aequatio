#include "powell.h"

namespace BuiltIn {
namespace Optimization {

namespace
{
	Powell instance;
}

Powell::Powell() :
	Function("powell")
{
}

Rpn::Operand Powell::calculate(FunctionCalculator *calculator, QList<Rpn::Operand> actualArguments)
{
	// Initialize algorithm variables
	m_calculator = calculator;
	m_functionName = actualArguments.at(0).value.value<QString>();
	m_sourcePoint = actualArguments.at(1).value.value<Number>();
	m_stepSize = actualArguments.at(2).value.value<Number>();
	m_firstAccuracyCoefficient = actualArguments.at(3).value.value<Number>();
	m_secondAccuracyCoefficient = actualArguments.at(4).value.value<Number>();

	// Check values of variables for currect algorithm work
	if (m_stepSize <= 0) {
		THROW(EWrongArgument(QObject::tr("step size"), QObject::tr("more than 0")) )
	}

	Rpn::Operand result;
	result.type = Rpn::OperandNumber;
	result.value = QVariant::fromValue(findMinimum());
	return result;
}

QList<Rpn::Argument> Powell::requiredArguments()
{
	QList<Rpn::Argument> arguments;
	arguments
		// 1 is argument count in function that is passed as and argument
		<< Rpn::Argument(Rpn::OperandFunctionName, QString(), QVariant::fromValue(1))
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber)
		<< Rpn::Argument(Rpn::OperandNumber);

	return arguments;
}

Rpn::OperandType Powell::returnValueType()
{
	return Rpn::OperandNumber;
}

Number Powell::findMinimum()
{
	bool needInitializePoints = true;

	forever {
		Number secondPoint, thirdPoint;

		if (needInitializePoints) {
			secondPoint = m_sourcePoint + m_stepSize;

			if (calculateFunction(m_sourcePoint) > calculateFunction(secondPoint)) {
				thirdPoint = m_sourcePoint + 2 * m_stepSize;
			}
			else {
				thirdPoint = m_sourcePoint - m_stepSize;
			}
		}

		Number minimumPoint = getMinimumPoint(m_sourcePoint, secondPoint, thirdPoint);

		Number numerator =
			(qPow(secondPoint, 2) - qPow(thirdPoint, 2)) * calculateFunction(m_sourcePoint) +
			(qPow(thirdPoint, 2) - qPow(m_sourcePoint, 2)) * calculateFunction(secondPoint) +
			(qPow(m_sourcePoint, 2) - qPow(secondPoint, 2)) * calculateFunction(thirdPoint);

		Number denominator =
			((secondPoint - thirdPoint) * calculateFunction(m_sourcePoint)) +
			((thirdPoint - m_sourcePoint) * calculateFunction(secondPoint)) +
			((m_sourcePoint - secondPoint) * calculateFunction(thirdPoint));

		if (MathUtils::isNull(denominator)) {
			m_sourcePoint = minimumPoint;

			needInitializePoints = true;
			continue;
		}

		Number quadraticPoint = (0.5 * numerator) / denominator;

		if ( (qAbs((calculateFunction(minimumPoint) - calculateFunction(quadraticPoint)) / calculateFunction(quadraticPoint))
			< m_firstAccuracyCoefficient) && (qAbs((minimumPoint - quadraticPoint) / quadraticPoint) < m_secondAccuracyCoefficient) ) {
			// Exit condition
			return quadraticPoint;
		}
		else if ((quadraticPoint > m_sourcePoint) && (quadraticPoint < thirdPoint)) {
			QList<Number> points;
			points << m_sourcePoint << secondPoint << thirdPoint;
			qSort(points);

			if (minimumPoint > quadraticPoint) {
				secondPoint = quadraticPoint;
			}
			else {
				secondPoint = minimumPoint;
			}

			points.removeOne(secondPoint);
			m_sourcePoint = points[0];
			thirdPoint = points[1];

			needInitializePoints = false;
		}
		else {
			m_sourcePoint = quadraticPoint;

			needInitializePoints = true;
		}
	}
}

Number Powell::getMinimumPoint(Number first, Number second, Number third)
{
	Number minimumNumber = first;
	if (calculateFunction(minimumNumber) > calculateFunction(second)) {
		minimumNumber = second;
	}
	if (calculateFunction(minimumNumber) > calculateFunction(third)) {
		minimumNumber = third;
	}

	return minimumNumber;
}

Number Powell::calculateFunction(Number argument)
{
	QList<Rpn::Operand> functionArguments;
	Rpn::Operand functionArgument(Rpn::OperandNumber, argument);
	functionArguments << functionArgument;

	Rpn::Operand result = m_calculator->calculate(m_functionName, functionArguments);
	return result.value.value<Number>();
}

} // namespace
} // namespace
