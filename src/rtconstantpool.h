#ifndef _RTCONSTANTPOOL_H_
#define _RTCONSTANTPOOL_H_
#include <boost/smart_ptr.hpp>
#include "constantpool.h"
#include "def.h"
#include "cpdef.h"
using namespace boost;
class Class;

class RtConstantPool
{
private:
	shared_ptr<Class> clazz;	
	ConstantPoolPtr pool;
	RtConstantPool(ConstantPoolPtr pool);
public:
	typedef shared_ptr<RtConstantPool> Pointer;
public:
	static Pointer build(ConstantPoolPtr pool);
	int32_t getInt(u2 index);
	int64_t getLong(u2 index);
	float getFloat(u2 index);
	double getDouble(u2 index);
	shared_ptr<ClassRef> getClassRef(u2 index);
	shared_ptr<FieldRef> getFieldRef(u2 index);
	shared_ptr<MethodRef> getMethodRef(u2 index);
	shared_ptr<InterfaceMethodRef> getInterfaceMethodRef(u2 index);
	string_ref getUTF8(u2 index);
	void setClass(shared_ptr<Class> clazz);
	shared_ptr<Class> getClass();
	void display();
private:
	shared_ptr<Class> resolveClass(shared_ptr<ClassRef> classRef);
	shared_ptr<Field> resolveField(shared_ptr<FieldRef> fieldRef);
};

#endif