#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <boost/smart_ptr.hpp>
#include "methodmember.h"
#include "threadprivate.h"
#include "memberitem.h"
using namespace boost;
class Interpreter;

typedef shared_ptr<Interpreter> InterpreterPtr;
class Interpreter
{
private:
	Interpreter();
	ThreadPrivatePtr threadPrivate;
public:
	void interpret(MemberItemPtr method);
	static InterpreterPtr build();
};

#endif