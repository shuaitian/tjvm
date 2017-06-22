#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <boost/smart_ptr.hpp>
#include "methodmember.h"
#include "threadprivate.h"
#include "memberitem.h"
using namespace boost;
class Interpreter;
class Method;

typedef shared_ptr<Interpreter> InterpreterPtr;
class Interpreter
{
private:
	Interpreter();
	ThreadPrivatePtr threadPrivate;
public:
	void interpret(shared_ptr<Method> method);
	static InterpreterPtr build();
};

#endif