#ifndef _CONSTANTITEM_H_
#define _CONSTANTITEM_H_
#include "def.h"
#include "bytearray.h"
#include <boost/smart_ptr.hpp>
#include <string.h>
#include <string>
using namespace std;
using namespace boost;

const u1 CONSTANT_Class 				= 7;
const u1 CONSTANT_Fieldref 				= 9;
const u1 CONSTANT_Methodref				= 10;
const u1 CONSTANT_InterfaceMethodref	= 11;
const u1 CONSTANT_String				= 8;
const u1 CONSTANT_Integer				= 3;
const u1 CONSTANT_Float					= 4;
const u1 CONSTANT_Long					= 5;
const u1 CONSTANT_Double				= 6;
const u1 CONSTANT_NameAndType			= 12;
const u1 CONSTANT_Utf8					= 1;
const u1 CONSTANT_MethodHandle			= 15;
const u1 CONSTANT_MethodType			= 16;
const u1 CONSTANT_InvokeDynamic			= 18;


class ConstantItem{
private:
	u1 tag;
	u2 ownIndex;	
public:
	void setTag(u1 tag){
		this->tag = tag;
	}
	u1 getTag(){
		return this->tag;
	}
	void setOwnIndex(u2 index){
		this->ownIndex = index;
	}
	u2 getOwnIndex(){
		return this->ownIndex;
	}
};

class ConstantU4Item : public ConstantItem{
protected:
	u4 bytes;
public:
	void setBytes(u4 bytes){
		this->bytes = bytes;
	}
	u4 getBytes(){
		return this->bytes;
	}
};

class ConstantIntegerItem : public ConstantU4Item{
public:
	int32_t getInt32Local(){
		return static_cast<int32_t>(bytes);
	}
};

class ConstantFloatItem : public ConstantU4Item{
public:
	float getFloatLocal(){
		float ret;
		memcpy(&ret,&bytes,sizeof(bytes));
		return ret;
	}
};

class ConstantU8Item : public ConstantItem{
protected:
	u8 bytes;
public:
	void setBytes(u8 bytes){
		this->bytes = bytes;
	}
	u8 getBytes(){
		return this->bytes;
	}
};

class ConstantLongItem : public ConstantU8Item{
public:
	int64_t getLong64Local(){
		return static_cast<int64_t>(bytes);
	}
};

class ConstantDoubleItem : public ConstantU8Item{
public:
	double getDoubleLocal(){
		double ret;
		memcpy(&ret,&bytes,sizeof(bytes));
		return ret;
	}
};


class ConstantUTF8Item : public ConstantItem{
private:
	u2 length;
	shared_ptr<ByteArray> bytes;
	string str;
public:
	void setLength(u2 length){
		this->length = length;
	}
	u2 getLength(){
		return this->length;
	}

	void setBytes(shared_ptr<ByteArray> bytes){
		this->bytes = bytes;
	}

	shared_ptr<ByteArray> getBytes(){
		return this->bytes;
	}
	void setStr(const string& str){
		this->str = str;
	}

	string& getStr(){
		return this->str;
	}
};


class ConstantStringItem : public ConstantItem{
private:
	u2 stringIndex;
public:
	void setStringIndex(u2 index){
		this->stringIndex = index;
	}
	u2 getStringIndex(){
		return this->stringIndex;
	}

	uint32_t getStringIndexLocal(){
		return this->stringIndex;
	}

};

class ConstantClassItem : public ConstantItem{
private:	
	u2 nameIndex;
public:
	void setNameIndex(u2 index){
		this->nameIndex = index;
	}

	u2 getNameIndex(){
		return this->nameIndex;
	}

	uint16_t getNameIndexLocal(){
		return this->nameIndex;
	}
	
};

class ConstantNameAndTypeItem : public ConstantItem{
private:
	u2 nameIndex;
	u2 descriptorIndex;
public:
	void setNameIndex(u2 nameIndex){
		this->nameIndex = nameIndex;
	}
	u2 getNameIndex(){
		return this->nameIndex;
	}

	void setDescriptorIndex(u2 index){
		this->descriptorIndex = index;
	}
	u2 getDescriptorIndex(){
		return this->descriptorIndex;
	}

	uint32_t getNameIndexLocal(){
		return this->nameIndex;
	}

	uint32_t getDescriptorIndexLocal(){
		return this->descriptorIndex;
	}
};

class ConstantMemberItem : public ConstantItem{
private:
	u2 classIndex;
	u2 nameAndTypeIndex;
public:
	void setClassIndex(u2 classIndex){
		this->classIndex = classIndex;
	}
	u2 getClassIndex(){
		return this->classIndex;
	}
	void setNameAndTypeIndex(u2 index){
		this->nameAndTypeIndex = index;
	}
	u2 getNameAndTypeIndex(){
		return this->nameAndTypeIndex;
	}

	uint32_t getClassIndexLocal(){
		return classIndex;
	}

	uint32_t getNameAndTypeIndexLocal(){
		return nameAndTypeIndex;
	}
};

class ConstantFieldRefItem : public ConstantMemberItem{};
class ConstantMethodRefItem : public ConstantMemberItem{};
class ConstantInterfaceMethodRefItem : public ConstantMemberItem{};

#endif
