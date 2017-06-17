#include "rtconstantpool.h"

RtConstantPool::Pointer RtConstantPool::build(ConstantPoolPtr pool){
	Pointer ret(new RtConstantPool(pool));
	return ret;
}


RtConstantPool::RtConstantPool(ConstantPoolPtr pool){
	this->pool = pool;
}

int32_t RtConstantPool::getInt(u2 index){
	return pool->readIntegerByIndex(index);
}
int64_t RtConstantPool::getLong(u2 index){
	return pool->readLongByIndex(index);
}
float RtConstantPool::getFloat(u2 index){
	return pool->readFloatByIndex(index);
}
double RtConstantPool::getDouble(u2 index){
	return pool->readDoubleByIndex(index);
}
shared_ptr<ClassRef> RtConstantPool::getClassRef(u2 index){
	return pool->readClassRefByIndex(index);
}
shared_ptr<FieldRef> RtConstantPool::getFieldRef(u2 index){
	return pool->readFieldRefByIndex(index);
}
shared_ptr<MethodRef> RtConstantPool::getMethodRef(u2 index){
	return pool->readMethodRefByIndex(index);
}
shared_ptr<InterfaceMethodRef> RtConstantPool::getInterfaceMethodRef(u2 index){
	return pool->readInterfaceMethodRefByIndex(index);
}

string_ref RtConstantPool::getUTF8(u2 index){
	return pool->readUTF8ByIndex(index);
}
