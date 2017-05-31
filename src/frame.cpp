#include "frame.h"
#include <stdio.h>

Frame::Frame(uint32_t maxLocals,uint32_t maxStack,shared_ptr<ThreadPrivate> tp):
	localVars(LocalVars::build(maxLocals)),
	operandStack(OperandStack::build(maxStack)),
	threadPrivate(tp)
{

}

FramePtr Frame::build(uint32_t maxLocals,uint32_t maxStack,shared_ptr<ThreadPrivate> tp){
	FramePtr ret(new Frame(maxLocals,maxStack,tp));
	return ret;
}

void Frame::display(){
	printf("LocalVars:");
	localVars->display();
	printf("\n");
}

shared_ptr<ThreadPrivate> Frame::getThreadPrivate(){
	return this->threadPrivate;
}