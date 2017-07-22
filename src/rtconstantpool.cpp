#include "rtconstantpool.h"
#include "classloader.h"
#include "class.h"

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
	shared_ptr<ClassRef> ret = pool->readClassRefByIndex(index);
	return ret;
}
shared_ptr<FieldRef> RtConstantPool::getFieldRef(u2 index){
	shared_ptr<FieldRef> ret =  pool->readFieldRefByIndex(index);
	return ret;
}
shared_ptr<MethodRef> RtConstantPool::getMethodRef(u2 index){
	shared_ptr<MethodRef> ret = pool->readMethodRefByIndex(index);

	return ret;
}
shared_ptr<InterfaceMethodRef> RtConstantPool::getInterfaceMethodRef(u2 index){
	shared_ptr<InterfaceMethodRef> ret = pool->readInterfaceMethodRefByIndex(index);

	return ret;
}

string_ref RtConstantPool::getUTF8(u2 index){
	return pool->readUTF8ByIndex(index);
}

void RtConstantPool::setClass(shared_ptr<Class> clazz){
	this->clazz = clazz;
}
shared_ptr<Class> RtConstantPool::getClass(){
	return this->clazz;
}

shared_ptr<Class> RtConstantPool::resolveClass(shared_ptr<ClassRef> classRef){
	shared_ptr<ClassLoader> loader = clazz->getClassLoader();
	shared_ptr<Class> ret = loader->loadClass(classRef->name);
	if(!ret->isAccessibleTo(clazz)){
		//TODO throw exception
		printf("error IllegalAccessError\n");
	}
	return ret;
}

shared_ptr<Field> RtConstantPool::resolveField(shared_ptr<FieldRef> fieldRef){
	shared_ptr<ClassLoader> loader = clazz->getClassLoader();
	shared_ptr<Class> c = loader->loadClass(fieldRef->className);
	shared_ptr<Field> field = c->lookupField(fieldRef->name,fieldRef->descriptor);
	if(!field){
		//TODO throw exception
		printf("error NoSuchFieldError[%s,%s]\n",fieldRef->className.c_str(),fieldRef->name.c_str());
		exit(0);
	}

	if(!field->isAccessibleTo(clazz)){
		//TODO throw exception
		printf("error IllegalAccessError\n");
		exit(0);
	}
	return field;
}

void RtConstantPool::display(){
	pool->display();
}
