#ifndef _FRAME_H_
#define _FRAME_H_
#include <boost/smart_ptr.hpp>
#include "operandstack.h"
#include "localvars.h"
#include "threadprivate.h"
#include "def.h"
using namespace boost;

class Frame;
class ThreadPrivate;
typedef shared_ptr<Frame> FramePtr;
class Method;

class Frame
{
private:
	FramePtr next;
	LocalVarsPtr localVars;
	OperandStackPtr operandStack;
	shared_ptr<ThreadPrivate> threadPrivate;
	shared_ptr<Method> method;
	Frame(uint32_t maxLocals,uint32_t maxStack,shared_ptr<ThreadPrivate> tp);
public:
	void setNext(FramePtr next){
		this->next = next;
	}

	FramePtr getNext(){
		return this->next;
	}

	LocalVarsPtr getLocalVars(){
		return localVars;
	}

	OperandStackPtr getOperandStack(){
		return operandStack;
	}
	static FramePtr build(uint32_t maxLocals,uint32_t maxStack,shared_ptr<ThreadPrivate> tp);

	void display();

	shared_ptr<ThreadPrivate> getThreadPrivate();

	void setMethod(shared_ptr<Method> method);
	shared_ptr<Method> getMethod();
};

#endif