#ifndef CONJUGATEGRADIENT_H
#define CONJUGATEGRADIENT_H

#include "../builtinfunction.h"

namespace BuiltInFunctions {
namespace Optimization {

class ConjugateGradient : public BuiltInFunction
{
public:
	ConjugateGradient() : BuiltInFunction("conjugate_gradient") {}
	RpnOperand calculate(FunctionCalculator* calculator, QList<RpnOperand> actualArguments);
	QList<RpnArgument> requiredArguments();
private:
	FunctionCalculator *m_calculator;
	QString m_functionName;
	Number m_accuracy;
	QList<Number> m_initialPoint;

	QList<Number> findMinimum();
	QList<Number> searchWithDirections(const QList<QList<Number> > directions,
		const QList<Number> &initialPoint, QList<Number> &finishingPoint, bool &found);
	Number findStep(QList<Number> point, QList<Number> direction);
	QList<QList<Number> > initialDirections(int dimensionsCount);
	bool isDirectionsLinearlyIndependend(const QList<QList<Number> > &directions);
	Number function(const QList<Number> arguments);
};

} // namespace
} // namespace

#endif // CONJUGATEGRADIENT_H