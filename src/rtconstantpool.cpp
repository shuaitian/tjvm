#include "rtconstantpool.h"

RtConstantPool::Pointer RtConstantPool::build(ConstantPoolPtr pool){
	Pointer ret(new RtConstantPool());
	return ret;
}