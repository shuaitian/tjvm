#ifndef _THREADPRIVATE_H_
#define _THREADPRIVATE_H_
#include <boost/smart_ptr.hpp>
#include "def.h"
#include "stackframe.h"
#include "frame.h"

using namespace boost;
class ThreadPrivate;

typedef shared_ptr<ThreadPrivate> ThreadPrivatePtr;

class ThreadPrivate
{
private:
	j_int pc;
	StackFramePtr stack;
	ThreadPrivate();
public:
	void setPC(j_int pc){
		this->pc = pc;
	}
	j_int getPC(){
		return this->pc;
	}

	void setStack(StackFramePtr stack){
		this->stack = stack;
	}
	StackFramePtr getStack(){
		return this->stack;
	}

	void pushFrame(FramePtr frame);
	FramePtr popFrame();
	FramePtr currentFrame();
	static ThreadPrivatePtr build();
};

#endif