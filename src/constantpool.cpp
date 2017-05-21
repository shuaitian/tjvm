#include "constantpool.h"
#include "def.h"
#include <stdio.h>

void ConstantPool::add(shared_ptr<ConstantItem> item){
//	printf("add constant item %d\n",item->getTag());
	pool.push_back(item);
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
