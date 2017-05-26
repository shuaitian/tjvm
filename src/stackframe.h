#ifndef _STACKFRAME_H_
#define _STACKFRAME_H_
#include <boost/smart_ptr.hpp>
#include "frame.h"
#include "def.h"
using namespace boost;

class StackFrame;
typedef shared_ptr<StackFrame> StackFramePtr;

class StackFrame
{
private:
	shared_ptr<Frame> topFrame;
	uint32_t size;
	uint32_t maxSize;
	StackFrame(uint32_t ms);
public:
	static StackFramePtr build(uint32_t ms);
	void push(FramePtr frame);
	FramePtr pop();
	FramePtr top();
};

typedef shared_ptr<StackFrame> StackFramePtr;

#endif