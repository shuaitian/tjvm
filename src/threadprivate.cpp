#include "threadprivate.h"


ThreadPrivate::ThreadPrivate():
	pc(0),
	stack(StackFrame::build(1024))	
{
	
}

ThreadPrivatePtr ThreadPrivate::build(){
	ThreadPrivatePtr ret(new ThreadPrivate());
	return ret;
}

void ThreadPrivate::pushFrame(FramePtr frame){
	this->stack->push(frame);
}
FramePtr ThreadPrivate::popFrame(){
	return this->stack->pop();
}
FramePtr ThreadPrivate::currentFrame(){
	return this->stack->top();
}