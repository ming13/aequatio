#include "neldermead.h"

namespace {
	NelderMead instance;
}

QList<RpnArgument> NelderMead::requiredArguments()
{
	QList<RpnArgument> arguments;
	arguments
		<< RpnArgument(RpnOperandFunctionName) // function
		<< RpnArgument(RpnOperandVector) // initial simplex
		<< RpnArgument(RpnOperandNumber)	// alpha
		<< RpnArgument(RpnOperandNumber)	// beta
		<< RpnArgument(RpnOperandNumber) // gamma
		<< RpnArgument(RpnOperandNumber); // epsilon

	return arguments;
}


RpnOperand NelderMead::calculate(BuiltInFunction::FunctionCalculator *calculator, QList<RpnOperand> actualArguments)
{
	m_calculator = calculator;

	m_functionName = actualArguments[0].value.value<QString>();

	QList<QList<Number> > initialSimplex = RpnVector::toTwoDimensional(actualArguments[1].value.value<RpnVector>());
	if (!isVectorCorrect(initialSimplex)) {
		int targetFunctionArgumentsCount = m_calculator->functionArguments(m_functionName).count();
		THROW(EWrongArgument("initial simplex", QObject::tr("%1 × %2 size")
			.arg(targetFunctionArgumentsCount + 1)
			.arg(targetFunctionArgumentsCount))
		);
	}

	Number alpha = actualArguments[2].value.value<Number>();
	Number beta = actualArguments[3].value.value<Number>();
	Number gamma = actualArguments[4].value.value<Number>();
	Number epsilon = actualArguments[5].value.value<Number>();

	if (epsilon <= 0) {
		THROW(EWrongArgument("epsilon", "greater than zero"));
	}

	RpnVector result = RpnVector::fromOneDimensional(findMinimum(initialSimplex, alpha, beta, gamma, epsilon));

	return RpnOperand(RpnOperandVector, QVariant::fromValue(result));
}


QList<Number> NelderMead::findMinimum(const QList<QList<Number> > &initialSimplex, Number alpha,
	Number beta, Number gamma, Number epsilon)
{
	QList<QList<Number> > simplex = initialSimplex;
	forever {

		// find best, worst and second worst values

		QList<Number> functions;
		foreach (const QList<Number> point, simplex) {
			functions << function(point);
		}

		int best = indexOfMinimal(functions);
		int worst = indexOfMaximal(functions);
		int secondWorst = indexOfSecondMaximal(functions);

		// find center value
		QList<Number> center = findCenter(simplex, worst);

		// check for exit
		if (found(simplex, center, epsilon)) {
			return simplex[best];
		}

		// get reflected value

		QList<Number> reflected = MathUtils::addVectorToVector(
			center,
			MathUtils::multiplyVectorByNumber(
				MathUtils::subtractVectorFromVector(
					center, simplex[worst]),
				alpha));

		// reflected <= best

		if (function(reflected) <= function(simplex[best])) {

			QList<Number> stretched = MathUtils::addVectorToVector(
				center,
				MathUtils::multiplyVectorByNumber(
					MathUtils::subtractVectorFromVector(
						reflected, center),
					gamma)
			);

			if (function(stretched) < function(simplex[best])) {
				simplex[worst] = stretched;
			}
			else {
				simplex[worst] = reflected;
			}
		}

		// second-worst < reflected <= worst

		else if (MathUtils::isBetween(function(reflected), function(simplex[secondWorst]), function(simplex[worst]), true)) {
			QList<Number> squashed = MathUtils::addVectorToVector(
				center,
				MathUtils::multiplyVectorByNumber(
					MathUtils::subtractVectorFromVector(
						simplex[worst], center),
					beta)
			);

			simplex[worst] = squashed;
		}

		// best < reflected <= worst

		else if (MathUtils::isBetween(function(reflected), function(simplex[best]), function(simplex[worst]), true)) {
			simplex[worst] = reflected;
		}

		// reflected > worst
		else {
			QList<Number> bestValue = simplex[best];
			for (int i = 0; i < simplex.count(); ++i) {
				simplex[i] = MathUtils::addVectorToVector(
					bestValue,
					MathUtils::multiplyVectorByNumber(
						MathUtils::subtractVectorFromVector(
							simplex[i], bestValue),
						0.5)
				);
			}
		}
	}
}

Number NelderMead::function(const QList<Number> &arguments)
{
	QList<RpnOperand> functionArguments;
	foreach (Number number, arguments) {
		functionArguments << RpnOperand(RpnOperandNumber, number);
	}

	RpnOperand result = m_calculator->calculate(m_functionName, functionArguments);
	return result.value.value<Number>();
}

int NelderMead::indexOfMinimal(const QList<Number> &values)
{
	if (values.count() <= 0) return -1;

	Number min = values[0];
	int index = 0;

	for (int i = 1; i < values.count(); ++i) {
		if (values[i] < min) {
			min = values[i];
			index = i;
		}
	}

	return index;
}

int NelderMead::indexOfMaximal(const QList<Number> &values)
{
	if (values.count() <= 0) return -1;

	Number max = values[0];
	int index = 0;

	for (int i = 1; i < values.count(); ++i) {
		if (values[i] > max) {
			max = values[i];
			index = i;
		}
	}

	return index;
}

int NelderMead::indexOfSecondMaximal(const QList<Number> &values)
{
	if (values.count() <= 1) return -1;

	Number indexOfMaximal = this->indexOfMaximal(values);

	Number secondMax = values[0];
	int index = 0;

	if (indexOfMaximal == 0) {
		secondMax = values[1];
		index = 1;
	}

	for (int i = 0; i < values.count(); ++i) {
		if ((values[i] > secondMax) && (i != indexOfMaximal)) {
			secondMax = values[i];
			index = i;
		}
	}

	return index;
}

QList<Number> NelderMead::findCenter(const QList<QList<Number> > &simplex, int worstIndex)
{
	int n = simplex[0].count();

	QList<Number> center;
	for (int i = 0; i < n; ++i) {
		center << 0;
	}

	for (int i = 0; i < simplex.count(); ++i) {
		if (i == worstIndex) continue;
		center = MathUtils::addVectorToVector(center, simplex[i]);
	}

	center = MathUtils::multiplyVectorByNumber(center, 1.0 / n);

	return center;
}

bool NelderMead::found(const QList<QList<Number> > &simplex, const QList<Number> &center, Number epsilon)
{
	Number sigma = 0;

	foreach (const QList<Number> point, simplex) {
		Number diff = qPow(function(point) - function(center), 2);
		sigma += diff;
	}
	sigma /= simplex.count();
	sigma = qPow(sigma, 0.5);

	bool result = sigma <= epsilon;

	return result;
}

bool NelderMead::isVectorCorrect(const QList<QList<Number> > vector)
{
	int targetFunctionArgumentCount = m_calculator->functionArguments(m_functionName).count();

	if (vector.count() != targetFunctionArgumentCount + 1) {
		return false;
	}
	foreach(const QList<Number> &point, vector) {
		if (point.count() != targetFunctionArgumentCount) {
			return false;
		}
	}

	return true;
}