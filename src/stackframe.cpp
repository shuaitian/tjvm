#include "stackframe.h"
#include <stdio.h>

StackFrame::StackFrame(uint32_t ms):
	size(0),
	maxSize(ms)
{
	
}


StackFramePtr StackFrame::build(uint32_t ms){
	StackFramePtr ret(new StackFrame(ms));
	return ret;
}

void StackFrame::push(FramePtr frame){
	if(this->size >= this->maxSize){
		printf("java.lang.StackOverflowError");
		exit(-1);
	}
	
	if(this->topFrame){
		topFrame->setNext(frame);
	}else{
		topFrame = frame;
	}
	size++;
}


FramePtr StackFrame::pop(){
	if(!this->topFrame){
		//TODO throw exception
		printf("jvm stack is empty");
		exit(-1);
	}

	FramePtr ret = this->topFrame;
	this->topFrame = this->topFrame->getNext();
	(this->size)--;
	return ret;
}

FramePtr StackFrame::top(){
	if(!this->topFrame){
		//TODO throw exception
		printf("jvm stack is empty");
		exit(-1);
	}

	return this->topFrame;
}