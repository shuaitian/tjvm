#include "constantitemreader.h"
#include <stdio.h>
#include <string>
using namespace std;

shared_ptr<ConstantItemReader> ConstantItemReader::self;

ConstantItemReader::ConstantItemReader(){

}

shared_ptr<ConstantItemReader> ConstantItemReader::instance(){
	if(!self){
		shared_ptr<ConstantItemReader> temp(new ConstantItemReader());
		self = temp;
	}
	return self;
}

shared_ptr<ConstantItem> ConstantItemReader::read(shared_ptr<ClassReader> classReader){	
	shared_ptr<ConstantItem> ret;
	u1 tag = classReader->readU1();
	switch(tag){
	case CONSTANT_Integer:
		ret = readIntegerItem(classReader);
		break;
	case CONSTANT_Float:
		ret = readFloatItem(classReader);
		break;
	case CONSTANT_Long:
		ret = readLongItem(classReader);
		break;
	case CONSTANT_Double:
		ret = readDoubleItem(classReader);
		break;
	case CONSTANT_Utf8:
		ret = readUTF8Item(classReader);
		break;
	case CONSTANT_String:
		ret = readStringItem(classReader);
		break;
	case CONSTANT_Class:
		ret = readClassItem(classReader);
		break;
	case CONSTANT_NameAndType:
		ret = readNameAndTypeItem(classReader);
		break;
	case CONSTANT_Fieldref:
		ret = readFieldRefItem(classReader);
		break;
	case CONSTANT_Methodref:
		ret = readMethodRefItem(classReader);
		break;
	case CONSTANT_InterfaceMethodref:
		ret = readInterfaceMethodRefItem(classReader);
		break;
	default:
		printf("unknow tag:%d\n",tag);
		break;
	}
	ret->setTag(tag);
	return ret;	
}

shared_ptr<ConstantInterfaceMethodRefItem> ConstantItemReader::readInterfaceMethodRefItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantInterfaceMethodRefItem> ret = make_shared<ConstantInterfaceMethodRefItem>();
	u2 classIndex = classReader->readU2();
	u2 nameAndTypeIndex = classReader->readU2();
	ret->setClassIndex(classIndex);
	ret->setNameAndTypeIndex(nameAndTypeIndex);
	return ret;
}

shared_ptr<ConstantMethodRefItem> ConstantItemReader::readMethodRefItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantMethodRefItem> ret = make_shared<ConstantMethodRefItem>();
	u2 classIndex = classReader->readU2();
	u2 nameAndTypeIndex = classReader->readU2();
	ret->setClassIndex(classIndex);
	ret->setNameAndTypeIndex(nameAndTypeIndex);
	return ret;
}

shared_ptr<ConstantFieldRefItem> ConstantItemReader::readFieldRefItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantFieldRefItem> ret = make_shared<ConstantFieldRefItem>();
	u2 classIndex = classReader->readU2();
	u2 nameAndTypeIndex = classReader->readU2();
	ret->setClassIndex(classIndex);
	ret->setNameAndTypeIndex(nameAndTypeIndex);
	return ret;
}

shared_ptr<ConstantNameAndTypeItem> ConstantItemReader::readNameAndTypeItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantNameAndTypeItem> ret = make_shared<ConstantNameAndTypeItem>();
	u2 nameIndex = classReader->readU2();
	u2 descriptorIndex = classReader->readU2();
	ret->setNameIndex(nameIndex);	
	ret->setDescriptorIndex(descriptorIndex);
	return ret;
}

shared_ptr<ConstantClassItem> ConstantItemReader::readClassItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantClassItem> ret = make_shared<ConstantClassItem>();
	u2 index = classReader->readU2();
	ret->setNameIndex(index);
	return ret;
}

shared_ptr<ConstantStringItem> ConstantItemReader::readStringItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantStringItem> ret = make_shared<ConstantStringItem>();
	u2 index = classReader->readU2();
	ret->setStringIndex(index);
	return ret;
}

shared_ptr<ConstantUTF8Item> ConstantItemReader::readUTF8Item(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantUTF8Item> ret = make_shared<ConstantUTF8Item>();
	u2 length = classReader->readU2();
	shared_ptr<ByteArray> bytes = classReader->readBytes(length);
	ret->setLength(length);
	ret->setBytes(bytes);
	if(bytes){
		unsigned char* p = bytes->getData();
		unsigned long pSize = bytes->getCurrentSize();
		string str(p,p+pSize);
		ret->setStr(str);
	}
	return ret;
}

shared_ptr<ConstantDoubleItem> ConstantItemReader::readDoubleItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantDoubleItem> ret =make_shared<ConstantDoubleItem>();
	u8 val = classReader->readU8();
	ret->setBytes(val);
	return ret;
}

shared_ptr<ConstantLongItem> ConstantItemReader::readLongItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantLongItem> ret = make_shared<ConstantLongItem>();
	u8 val = classReader->readU8();
	ret->setBytes(val);
	return ret;
}

shared_ptr<ConstantIntegerItem> ConstantItemReader::readIntegerItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantIntegerItem> ret = make_shared<ConstantIntegerItem>();
	u4 val = classReader->readU4();
	ret->setBytes(val);
	return ret;
}

shared_ptr<ConstantFloatItem> ConstantItemReader::readFloatItem(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantFloatItem> ret = make_shared<ConstantFloatItem>();
	u4 val = classReader->readU4();
	ret->setBytes(val);	
	return ret;
}
