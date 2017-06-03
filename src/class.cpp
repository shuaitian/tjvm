#include "class.h"

Class::Class(){}

Class::Pointer Class::build(ClassEntityPtr entity){
	Pointer ret(new Class());
	ret->accessFlags = entity->getAccessFlags();
	ret->name = entity->getClassName().data();
	printf("className:%s\n",(ret->name).c_str());
	ret->superClassName = entity->getSuperClassName().data();
	printf("superClassName:%s\n",ret->superClassName.c_str());
	ret->interfaceNames = entity->getInterfaceNames();
	vector<string>::iterator iter;
	for(iter=ret->interfaceNames->begin();iter!=ret->interfaceNames->end();++iter){
		string interfaceName = *iter;
		printf("interfaceName:%s\n",interfaceName.c_str());
	}
	ret->constantPool = RtConstantPool::build(entity->getConstantPool());
	ret->fields = Field::builds(entity->getFieldMember());
	vector<Field::Pointer>::iterator fieldIter;
	for(fieldIter=ret->fields->begin();fieldIter!=ret->fields->end();++fieldIter){
		printf("field name:%s descriptor:%s\n",(*fieldIter)->getName().data(),(*fieldIter)->getDescriptor().data());
	}
	ret->methods = Method::builds(entity->getMethodMember());
	vector<Method::Pointer>::iterator methodIter;
	for(methodIter=ret->methods->begin();methodIter!=ret->methods->end();++methodIter){
		printf("method name:%s descriptor:%s\n",(*methodIter)->getName().data(),(*methodIter)->getDescriptor().data());
	}
	return ret;
}

bool Class::is(u2 flag){
	return 0 != (accessFlags & flag);
}