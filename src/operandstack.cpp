#include "operandstack.h"
#include "bytearray.h"
#include <stdio.h>
#include <string.h>

OperandStack::OperandStack(uint32_t ms):
	size(0),
	slots(new Slot[ms]),
	maxStack(ms)
{
	
}
OperandStackPtr OperandStack::build(uint32_t maxStack){
	OperandStackPtr ret(new OperandStack(maxStack));
	return ret;
}

OperandStack::~OperandStack(){
	delete[] slots;
}

void OperandStack::pushInt(j_int val){
	if(size >= maxStack){
		printf("OperandStack::pushInt");
		exit(-1);
	}
	slots[size++].num = val;
}
j_int OperandStack::popInt(){
	if(size <= 0){
		printf("OperandStack::popInt");
		exit(-1);
	}
	return slots[--size].num;
}
void OperandStack::pushFloat(j_float val){
	if(size >= maxStack){
		printf("OperandStack::pushFloat");
		exit(-1);
	}
	void *src = &val;
	void *dest = &(slots[size++].num);
	memcpy(dest,src,sizeof(val));
}
j_float OperandStack::popFloat(){
	if(size <= 0){
		printf("OperandStack::popFloat");
		exit(-1);
	}
	j_float ret = 0;
	void *dest = &ret;
	void *src = &(slots[--size].num);
	memcpy(dest,src,sizeof(ret));
	return ret;
}
void OperandStack::pushLong(j_long val){
	if(size >= maxStack){
		printf("OperandStack::pushLong");
		exit(-1);
	}

	slots[size++].num = (int32_t)val;
	slots[size++].num = (int32_t)(val >> 32);
}
j_long OperandStack::popLong(){
	if(size <= 0){
		printf("OperandStack::popLong");
		exit(-1);
	}
	int32_t high = slots[--size].num;
	int32_t low = slots[--size].num;

	return ((j_long)high << 32) | low;
}
void OperandStack::pushDouble(j_double val){
	if(size >= maxStack){
		printf("OperandStack::pushDouble");
		exit(-1);
	}
	
	j_float* hs = (j_float*)&val;
	void *hd = &(slots[size++]).num;
	memcpy(hd,hs,sizeof(j_float));

	j_float* ls = hs+1;
	void *ld = &(slots[size++]).num;
	memcpy(ld,ls,sizeof(j_float));
	
}
j_double OperandStack::popDouble(){
	if(size <= 0){
		printf("OperandStack::popDouble");
		exit(-1);
	}

	j_double ret = 0;
	j_float *hs = (j_float*)&(slots[--size]).num;
	j_float *hd = (j_float*)&ret;
	memcpy(hd + 1,hs,sizeof(j_float));

	j_float *ls = (j_float*)&(slots[--size]).num;
	j_float *ld = hd;
	memcpy(ld,ls,sizeof(j_float));
	
	return ret;
}
void OperandStack::pushRef(ObjectPtr ref){
	if(size >= maxStack){
		printf("OperandStack::pushRef");
		exit(-1);
	}

	slots[size++].ref = ref;
}
ObjectPtr OperandStack::popRef(){
	if(size <= 0){
		printf("OperandStack::popRef");
		exit(-1);
	}

	return slots[--size].ref;
}

void OperandStack::pushSlot(Slot slot){
	slots[size++] = slot;
}

Slot OperandStack::popSlot(){
	return slots[--size];
}