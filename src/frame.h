#ifndef _FRAME_H_
#define _FRAME_H_
#include <boost/smart_ptr.hpp>
#include "operandstack.h"
#include "localvars.h"
#include "def.h"
using namespace boost;

class Frame;
typedef shared_ptr<Frame> FramePtr;

class Frame
{
private:
	FramePtr next;
	LocalVarsPtr localVars;
	OperandStackPtr operandStack;
	Frame(uint32_t maxLocals,uint32_t maxStack);
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
	static FramePtr build(uint32_t maxLocals,uint32_t maxStack);
};

#endif