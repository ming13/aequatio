#ifndef CALCULATINGEXCEPTIONS_H
#define CALCULATINGEXCEPTIONS_H

/* This module contains all exceptions that can be thrown by expression calculator.
	They are children either of EInternal or ECalculating. */

#include "exceptions.h"

/* ECalculating and its children */

class ECalculating : public Exception
{
public:
	QString message();
};

class EBuiltInRedifinition : public ECalculating
{
public:
	enum ElementType {Constant, Function};
	EBuiltInRedifinition(const QString &elementName, ElementType elementType);
	QString m_elementName;
	ElementType m_elementType;
	QString message();
};


/* EInternal children */


class EIncorrectRpnCode : public EInternal
{
	/* Reason for all current non-due-to-user-input exceptions in calculator
	is incorrect RPN code. No need to be more concrete at this moment.
	There will be not a problem to derive from EIncorrectRpnCode to provide
	more specific info if necessary. */
};


#endif // CALCULATINGEXCEPTIONS_H