#ifndef _OPERANDSTACK_H_
#define _OPERANDSTACK_H_
#include <boost/smart_ptr.hpp>
#include "localvars.h"
#include "object.h"
#include "def.h"

using namespace boost;
class OperandStack;
typedef shared_ptr<OperandStack> OperandStackPtr; 
class OperandStack
{
private:
	uint32_t size;
	Slot *slots;
	uint32_t maxStack;
	OperandStack(uint32_t ms);
public:
	void pushInt(j_int val);
	j_int popInt();
	void pushFloat(j_float val);
	j_float popFloat();
	void pushLong(j_long val);
	j_long popLong();
	void pushDouble(j_double val);
	j_double popDouble();
	void pushRef(ObjectPtr ref);
	ObjectPtr popRef();
	void pushSlot(Slot slot);
	Slot popSlot();
	uint32_t getSize();
	
	static OperandStackPtr build(uint32_t maxStack);
	~OperandStack();
};

#endif