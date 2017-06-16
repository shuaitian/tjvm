#ifndef _CONSTANTITEMREADER_H_
#define _CONSTANTITEMREADER_H_
#include <boost/smart_ptr.hpp>
#include "constantitem.h"
#include "classreader.h"
using namespace boost;


class ConstantItemReader{
private:
	static shared_ptr<ConstantItemReader> self;
	ConstantItemReader();
	shared_ptr<ConstantIntegerItem> readIntegerItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantFloatItem> readFloatItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantLongItem> readLongItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantDoubleItem> readDoubleItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantUTF8Item> readUTF8Item(shared_ptr<ClassReader> classReader); 
	shared_ptr<ConstantStringItem> readStringItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantClassItem> readClassItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantNameAndTypeItem> readNameAndTypeItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantFieldRefItem> readFieldRefItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantMethodRefItem> readMethodRefItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantInterfaceMethodRefItem> readInterfaceMethodRefItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantItem> readMethodHandleItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantItem> readMethodTypeItem(shared_ptr<ClassReader> classReader);
	shared_ptr<ConstantItem> readInvokeDynamicItem(shared_ptr<ClassReader> classReader);
public:
	static shared_ptr<ConstantItemReader> instance();
	shared_ptr<ConstantItem> read(shared_ptr<ClassReader> classReader);
};

#endif
