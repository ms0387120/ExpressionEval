#ifndef Implement_h
#define Implement_h

#include "readonly/ExpressionEval.h"

class Implement : public ExpressionEval
{
public:
    // convert
	void infix2Prefix(Expression &prefix, const Expression &infix); 
	void infix2Postfix(Expression &postfix, const Expression &infix);
	// evaluate
	int evalPrefix(const Expression &prefix);
	int evalPostfix(const Expression &postfix);
	
};

#endif
