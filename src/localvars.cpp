#include "localvars.h"
#include "def.h"
#include <string.h>
#include <stdio.h>

void LocalVars::display(){
	printf("[ ");
	for(uint32_t i =0;i<size;i++){
		printf("%d ",slots[i].num);
	}
	printf("]");
}

LocalVars::LocalVars(uint32_t maxLocals):
	slots(new Slot[maxLocals]),
	size(maxLocals)
{
	
}

LocalVarsPtr LocalVars::build(uint32_t maxLocals){
	LocalVarsPtr ret(new LocalVars(maxLocals));
	return ret;
}

Slot& LocalVars::operator[](uint32_t index){
	if(index < 0 || index >= size){
		//TODO exception;
		printf("LocalVars::operator[] invalid parameter,[index < 0]");
		exit(-1);
	}

	return slots[index];
}

LocalVars::~LocalVars(){
	delete[] slots;
}

void LocalVars::printErrorExit(const char* str){
	printf("LocalVars::%s\n",str);
	exit(-1);
}

void LocalVars::setInt(uint32_t index,j_int val){
	if(index < 0 || index >= size){
		printErrorExit("setInt");
	}
	
	slots[index].num = val;
}
j_int LocalVars::getInt(uint32_t index){
	if(index < 0 || index >= size){
		printErrorExit("setInt");
	}

	return slots[index].num;
}
void LocalVars::setFloat(uint32_t index,j_float val){
	if(index < 0 || index >= size){
		printErrorExit("setFloat");
	}
	void *src = &val;
	void *dest = &(slots[index].num);
	memcpy(dest,src,sizeof(val));
}
j_float LocalVars::getFloat(uint32_t index){
		if(index < 0 || index >= size){
		printErrorExit("getFloat");
	}
	j_float ret = 0;
	void *dest = &ret;
	void *src = &(slots[index].num);
	memcpy(dest,src,sizeof(ret));
	return ret;
}
void LocalVars::setLong(uint32_t index,j_long val){
	if(index < 0 || index >= size-1){
		printErrorExit("setLong");
	}

	slots[index].num = (int32_t)val;
	slots[index+1].num = (int32_t)(val >> 32);
}
j_long LocalVars::getLong(uint32_t index){
	if(index < 1 || index >= size){
		printErrorExit("getLong");
	}

	int32_t high = slots[index+1].num;
	int32_t low = slots[index].num;
	return ((j_long)high << 32) | low;
}
void LocalVars::setDouble(uint32_t index,j_double val){
	if(index < 0 || index >= size-1){
		printErrorExit("setDouble");
	}

	j_float* hs = (j_float*)&val;
	void *hd = &(slots[index]).num;
	memcpy(hd,hs,sizeof(j_float));

	j_float* ls = hs+1;
	void *ld = &(slots[index+1]).num;
	memcpy(ld,ls,sizeof(j_float));

}
j_double LocalVars::getDouble(uint32_t index){
	if(index < 1 || index >= size){
		printErrorExit("getDouble");
	}

	j_double ret = 0;
	j_float *hs = (j_float*)&(slots[index+1]).num;
	j_float *hd = (j_float*)&ret;
	memcpy(hd + 1,hs,sizeof(j_float));

	j_float *ls = (j_float*)&(slots[index]).num;
	j_float *ld = hd;
	memcpy(ld,ls,sizeof(j_float));
	
	return ret;
}
void LocalVars::setRef(uint32_t index,ObjectPtr ref){
	if(index < 0 || index >= size){
		printErrorExit("setRef");
	}
	slots[index].ref = ref;
}
ObjectPtr LocalVars::getRef(uint32_t index){
	if(index < 0 || index >= size){
		printErrorExit("getRef");
	}
	return slots[index].ref;
}

