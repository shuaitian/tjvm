#include "slot.h"
#include <string.h>
#include <stdio.h>

void SlotUtil::setInt(shared_ptr<vector<Slot> > slots,uint32_t index,j_int val){
	if(index < 0 || index >= slots->size()){
		printErrorExit("setInt");
	}
	
	(*slots)[index].num = val;
}
j_int SlotUtil::getInt(shared_ptr<vector<Slot> > slots,uint32_t index){
	if(index < 0 || index >= slots->size()){
		printErrorExit("setInt");
	}

	return (*slots)[index].num;
}
void SlotUtil::setFloat(shared_ptr<vector<Slot> > slots,uint32_t index,j_float val){
	if(index < 0 || index >= slots->size()){
		printErrorExit("setFloat");
	}
	void *src = &val;
	void *dest = &((*slots)[index].num);
	memcpy(dest,src,sizeof(val));
}
j_float SlotUtil::getFloat(shared_ptr<vector<Slot> > slots,uint32_t index){
		if(index < 0 || index >= slots->size()){
		printErrorExit("getFloat");
	}
	j_float ret = 0;
	void *dest = &ret;
	void *src = &((*slots)[index].num);
	memcpy(dest,src,sizeof(ret));
	return ret;
}
void SlotUtil::setLong(shared_ptr<vector<Slot> > slots,uint32_t index,j_long val){
	uint32_t size = static_cast<uint32_t>(slots->size());
	if(index < 0 || index >= size-1){
		printErrorExit("setLong");
	}

	(*slots)[index].num = (int32_t)val;
	(*slots)[index+1].num = (int32_t)(val >> 32);
}
j_long SlotUtil::getLong(shared_ptr<vector<Slot> > slots,uint32_t index){
	if(index < 1 || index >= slots->size()){
		printErrorExit("getLong");
	}

	int32_t high = (*slots)[index+1].num;
	int32_t low = (*slots)[index].num;
	return ((j_long)high << 32) | low;
}
void SlotUtil::setDouble(shared_ptr<vector<Slot> > slots,uint32_t index,j_double val){
	if(index < 0 || index >= slots->size()-1){
		printErrorExit("setDouble");
	}

	j_float* hs = (j_float*)&val;
	void *hd = &((*slots)[index]).num;
	memcpy(hd,hs,sizeof(j_float));

	j_float* ls = hs+1;
	void *ld = &((*slots)[index+1]).num;
	memcpy(ld,ls,sizeof(j_float));

}
j_double SlotUtil::getDouble(shared_ptr<vector<Slot> > slots,uint32_t index){
	if(index < 1 || index >= slots->size()){
		printErrorExit("getDouble");
	}

	j_double ret = 0;
	j_float *hs = (j_float*)&((*slots)[index+1]).num;
	j_float *hd = (j_float*)&ret;
	memcpy(hd + 1,hs,sizeof(j_float));

	j_float *ls = (j_float*)&((*slots)[index]).num;
	j_float *ld = hd;
	memcpy(ld,ls,sizeof(j_float));
	
	return ret;
}
void SlotUtil::setRef(shared_ptr<vector<Slot> > slots,uint32_t index,shared_ptr<Object> ref){
	if(index < 0 || index >= slots->size()){
		printErrorExit("setRef");
	}
	(*slots)[index].ref = ref;
}
shared_ptr<Object> SlotUtil::getRef(shared_ptr<vector<Slot> > slots,uint32_t index){
	if(index < 0 || index >= slots->size()){
		printErrorExit("getRef");
	}
	return (*slots)[index].ref;
}

void SlotUtil::printErrorExit(const char* str){
	printf("LocalVars::%s\n",str);
	exit(-1);
}
