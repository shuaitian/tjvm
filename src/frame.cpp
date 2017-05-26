#include "frame.h"

Frame::Frame(uint32_t maxLocals,uint32_t maxStack):
	localVars(LocalVars::build(maxLocals)),
	operandStack(OperandStack::build(maxStack))
{

}

FramePtr Frame::build(uint32_t maxLocals,uint32_t maxStack){
	FramePtr ret(new Frame(maxLocals,maxStack));
	return ret;
}