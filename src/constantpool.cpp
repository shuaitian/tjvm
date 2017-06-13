#include "constantpool.h"
#include <string>
#include "def.h"
#include <assert.h>
#include <stdio.h>

void ConstantPool::add(shared_ptr<ConstantItem> item){
//	printf("add constant item %d\n",item->getTag());
	pool.push_back(item);
}

int32_t ConstantPool::readIntegerByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<ConstantItem> item = readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_Integer);
	shared_ptr<ConstantIntegerItem> intItem = static_pointer_cast<ConstantIntegerItem>(item);
	return intItem->getInt32Local();
}
int64_t ConstantPool::readLongByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<ConstantItem> item = readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_Long);
	shared_ptr<ConstantLongItem> longItem = static_pointer_cast<ConstantLongItem>(item);
	return longItem->getLong64Local();
}
float ConstantPool::readFloatByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<ConstantItem> item = readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_Float);
	shared_ptr<ConstantFloatItem> floatItem = static_pointer_cast<ConstantFloatItem>(item);
	return floatItem->getFloatLocal();
}
double ConstantPool::readDoubleByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<ConstantItem> item = readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_Double);
	shared_ptr<ConstantDoubleItem> doubleItem = static_pointer_cast<ConstantDoubleItem>(item);
	return doubleItem->getDoubleLocal();
}

shared_ptr<ClassRef> ConstantPool::readClassRefByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<ClassRef> ret = make_shared<ClassRef>();
	ret->name = readClassByIndex(index).data();
	return ret;
}

shared_ptr<FieldRef> ConstantPool::readFieldRefByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<FieldRef> ret = make_shared<FieldRef>();
	shared_ptr<ConstantItem> item =  readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_Fieldref);
	shared_ptr<ConstantFieldRefItem> fieldItem = static_pointer_cast<ConstantFieldRefItem>(item);
	u2 classIndex = fieldItem->getClassIndex();
	string_ref className = readClassByIndex(classIndex);
	ret->className = className.data();
	u2 nameAndTypeIndex = fieldItem->getNameAndTypeIndex();
	shared_ptr<NameAndType> nat = readNameAndTypeByIndex(nameAndTypeIndex);
	ret->name = nat->name;
	ret->descriptor = nat->descriptor;
	return ret;
	
}
shared_ptr<MethodRef> ConstantPool::readMethodRefByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<MethodRef> ret = make_shared<MethodRef>();
	shared_ptr<ConstantItem> item =  readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_Methodref);
	shared_ptr<ConstantMethodRefItem> methodItem = static_pointer_cast<ConstantMethodRefItem>(item);
	u2 classIndex = methodItem->getClassIndex();
	string_ref className = readClassByIndex(classIndex);
	ret->className = className.data();
	u2 nameAndTypeIndex = methodItem->getNameAndTypeIndex();
	shared_ptr<NameAndType> nat = readNameAndTypeByIndex(nameAndTypeIndex);
	ret->name = nat->name;
	ret->descriptor = nat->descriptor;
	return ret;
}
shared_ptr<InterfaceMethodRef> ConstantPool::readInterfaceMethodRefByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<InterfaceMethodRef> ret = make_shared<InterfaceMethodRef>();
	shared_ptr<ConstantItem> item =  readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_InterfaceMethodref);
	shared_ptr<ConstantInterfaceMethodRefItem> imItem = static_pointer_cast<ConstantInterfaceMethodRefItem>(item);
	u2 classIndex = imItem->getClassIndex();
	string_ref className = readClassByIndex(classIndex);
	ret->className = className.data();
	u2 nameAndTypeIndex = imItem->getNameAndTypeIndex();
	shared_ptr<NameAndType> nat = readNameAndTypeByIndex(nameAndTypeIndex);
	ret->name = nat->name;
	ret->descriptor = nat->descriptor;
	return ret;
}

shared_ptr<NameAndType> ConstantPool::readNameAndTypeByIndex(u2 index){
	assert(index >= 0);
	shared_ptr<NameAndType> ret = make_shared<NameAndType>();
	shared_ptr<ConstantItem> item =  readConstItemByOwnIndex(index);
	assert(item);
	assert(item->getTag() == CONSTANT_NameAndType);
	shared_ptr<ConstantNameAndTypeItem> natItem = static_pointer_cast<ConstantNameAndTypeItem>(item);
	ret->name = readUTF8ByIndex(natItem->getNameIndex()).data();
	ret->descriptor = readUTF8ByIndex(natItem->getDescriptorIndex()).data();
	return ret;
}
string_ref ConstantPool::readClassByIndex(u2 index){
	if(index == 0){
		//object没有父类，superClassindex为0
		std::string *nullStr = new string("");
		return string_ref(*nullStr);
	}
	shared_ptr<ConstantItem> item = readConstItemByOwnIndex(index);
	if(!item){
		printf("error ConstantPool::readClassByIndex(u2 index) illegal paramenter 'index'");
		exit(0);
	}
	if(item->getTag() != CONSTANT_Class){
		printf("error ConstantPool::readClassByIndex(u2 index) item->getTag()!=CONSTANT_Class\n");
		exit(0);
	}
	shared_ptr<ConstantClassItem> classItem = static_pointer_cast<ConstantClassItem>(item);
	u2 nameIndex = classItem->getNameIndex();	
	return readUTF8ByIndex(nameIndex);
}

string_ref ConstantPool::readUTF8ByIndex(u2 index){
	shared_ptr<ConstantItem> item = readConstItemByOwnIndex(index);
	if(!item){
		printf("error ConstantPool::readUTF8ByIndex(u2 index) illegal paramenter 'index'");
		exit(0);
		//TODO throw exception
	}
	if(item->getTag() != CONSTANT_Utf8){
		printf("tag:%u\n",item->getTag());
		printf("error ConstantPool::readUTF8ByIndex(u2 index) item->getTag()!=CONSTANT_Utf8\n");
		exit(0);
		//TODO throw exception
	}
	shared_ptr<ConstantUTF8Item> utf8Item = static_pointer_cast<ConstantUTF8Item>(item);
	return utf8Item->getStr();
}

shared_ptr<ConstantItem> ConstantPool::readConstItemByOwnIndex(u2 index){
	vector<shared_ptr<ConstantItem> >::iterator iter;
	for(iter=pool.begin();iter!=pool.end();++iter){
		shared_ptr<ConstantItem> item = *iter;
		if(item->getOwnIndex() == index){
			return item;
		}
	}
	return make_shared<ConstantItem>();
}
void ConstantPool::display(){
	vector<shared_ptr<ConstantItem> >::iterator iter;
	printf("=====================Constant Pool=================================\n");
	for(iter=pool.begin();iter!=pool.end();++iter){
		shared_ptr<ConstantItem> item = *iter;
		u1 tag = item->getTag();
		switch(tag){
		case CONSTANT_Utf8:{
			shared_ptr<ConstantUTF8Item> utf8Item = static_pointer_cast<ConstantUTF8Item>(item);
			printf("%d\tUTF8\t\t%s\n",utf8Item->getOwnIndex(),(utf8Item->getStr()).c_str());
			break; 
		}
		case CONSTANT_Integer:{
			shared_ptr<ConstantIntegerItem> intItem = static_pointer_cast<ConstantIntegerItem>(item);
			printf("%d\tInteger\t\t%d\n",intItem->getOwnIndex(),intItem->getInt32Local());
			break;
		}
		case CONSTANT_Float:{
			shared_ptr<ConstantFloatItem> floatItem = static_pointer_cast<ConstantFloatItem>(item);
			printf("%d\tFloat\t\t%f\n",floatItem->getOwnIndex(),floatItem->getFloatLocal());
			break;
		}
		case CONSTANT_Long:{
			shared_ptr<ConstantLongItem> longItem = static_pointer_cast<ConstantLongItem>(item);
			printf("%d\tLong\t\t%ld\n",longItem->getOwnIndex(),longItem->getLong64Local());
			break;
		}
		case CONSTANT_Double:{
			shared_ptr<ConstantDoubleItem> doubleItem = static_pointer_cast<ConstantDoubleItem>(item);
			printf("%d\tDouble\t\t%f\n",doubleItem->getOwnIndex(),doubleItem->getDoubleLocal());
			break;
		}
		case CONSTANT_Class:{
			shared_ptr<ConstantClassItem> classItem = static_pointer_cast<ConstantClassItem>(item);
			printf("%d\tClass\t\t#%u\n",classItem->getOwnIndex(),classItem->getNameIndexLocal());
			break;
		}
		case CONSTANT_String:{
			shared_ptr<ConstantStringItem> stringItem = static_pointer_cast<ConstantStringItem>(item);
			printf("%d\tString\t\t#%u\n",stringItem->getOwnIndex(),stringItem->getStringIndexLocal());
			break;
		}
		case CONSTANT_Fieldref:{
			shared_ptr<ConstantFieldRefItem> fieldRefItem = static_pointer_cast<ConstantFieldRefItem>(item);
			printf("%d\tFieldref\t#%u#%u\n",fieldRefItem->getOwnIndex(),fieldRefItem->getClassIndexLocal(),fieldRefItem->getNameAndTypeIndexLocal());
			break;
		}
		case CONSTANT_Methodref:{
			shared_ptr<ConstantMethodRefItem> methodRefItem = static_pointer_cast<ConstantMethodRefItem>(item);
			printf("%d\tMethodref\t#%u#%u\n",methodRefItem->getOwnIndex(),methodRefItem->getClassIndexLocal(),methodRefItem->getNameAndTypeIndexLocal());
			break;
		}
		case CONSTANT_InterfaceMethodref:{
			shared_ptr<ConstantInterfaceMethodRefItem> infcRef8Item = static_pointer_cast<ConstantInterfaceMethodRefItem>(item);
			printf("%d\tInterfMeref\t#%u#%u\n",infcRef8Item->getOwnIndex(),infcRef8Item->getClassIndexLocal(),infcRef8Item->getNameAndTypeIndexLocal());
			break;
		}
		case CONSTANT_NameAndType:{
			shared_ptr<ConstantNameAndTypeItem> nameAndTypeItem = static_pointer_cast<ConstantNameAndTypeItem>(item);
			printf("%d\tNameAndType\t#%u#%u\n",nameAndTypeItem->getOwnIndex(),nameAndTypeItem->getNameIndexLocal(),nameAndTypeItem->getDescriptorIndexLocal());
			break;
		}
		case CONSTANT_MethodHandle:{
			break;
		}
		case CONSTANT_MethodType:{
			break;
		}
		case CONSTANT_InvokeDynamic:{
			break;
		}
		default:
			break;
		}
	}
	printf("===================================================================\n");

}
