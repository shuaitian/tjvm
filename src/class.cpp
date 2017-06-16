#include "class.h"

Class::Class(){}

Class::Pointer Class::build(ClassEntityPtr entity){
	Pointer ret(new Class());
	ret->accessFlags = entity->getAccessFlags();
	ret->name = entity->getClassName().data();
	//printf("className:%s\n",(ret->name).c_str());
	ret->superClassName = entity->getSuperClassName().data();
	//printf("superClassName:%s\n",ret->superClassName.c_str());
	ret->interfaceNames = entity->getInterfaceNames();
	//vector<string>::iterator iter;
	//for(iter=ret->interfaceNames->begin();iter!=ret->interfaceNames->end();++iter){
	//	string interfaceName = *iter;
	//	printf("interfaceName:%s\n",interfaceName.c_str());
	//}
	ret->constantPool = RtConstantPool::build(entity->getConstantPool());
	//printf("#6 class: name:%s\n",ret->constantPool->getClassRef(6)->name.c_str());
	//shared_ptr<FieldRef> fieldRef = ret->constantPool->getFieldRef(4);
	//printf("#4 FieldRef: className:%s name:%s descriptor:%s\n",fieldRef->className.c_str(),fieldRef->name.c_str(),fieldRef->descriptor.c_str());
	//shared_ptr<MethodRef> methodRef = ret->constantPool->getMethodRef(5);
	//printf("#5 MethodRef: className:%s name:%s descriptor:%s\n",methodRef->className.c_str(),methodRef->name.c_str(),methodRef->descriptor.c_str());
	ret->fields = Field::builds(entity->getFieldMember());
	//vector<Field::Pointer>::iterator fieldIter;
	//for(fieldIter=ret->fields->begin();fieldIter!=ret->fields->end();++fieldIter){
	//	printf("field name:%s descriptor:%s\n",(*fieldIter)->getName().data(),(*fieldIter)->getDescriptor().data());
	//}
	ret->methods = Method::builds(entity->getMethodMember());
	//vector<Method::Pointer>::iterator methodIter;
	//for(methodIter=ret->methods->begin();methodIter!=ret->methods->end();++methodIter){
	//	printf("method name:%s descriptor:%s\n",(*methodIter)->getName().data(),(*methodIter)->getDescriptor().data());
	//}
	return ret;
}

bool Class::is(u2 flag){
	return 0 != (accessFlags & flag);
}

void Class::setClassLoader(ClassLoader::Pointer loader){
	this->classLoader = loader;
}
ClassLoader::Pointer Class::getClassLoader(){
	return this->classLoader;
} 

string_ref Class::getName(){
	return this->name;
}

string_ref Class::getSuperClassName(){
	return this->superClassName;
}
void Class::setSuperClass(Class::Pointer super){
	this->superClass = super;
}
Class::Pointer Class::getSuperClass(){
	return this->superClass;
}

shared_ptr<vector<string> > Class::getInterfaceNames(){
	return this->interfaceNames;
}
void Class::setInterfaces(shared_ptr<vector<Class::Pointer> > interfaces){
	this->interfaces = interfaces;
}
shared_ptr<vector<Class::Pointer> > Class::getInterfaces(){
	return this->interfaces;
}

uint32_t Class::getInstanceSlotCount(){
	return this->instanceSlotCount;
}

uint32_t Class::getStaticSlotCount(){
	return this->staticSlotCount;
}

void Class::setInstanceSlotCount(uint32_t count){
	this->instanceSlotCount = count;
}
void Class::setStaticSlotCount(uint32_t count){
	this->staticSlotCount = count;
}

shared_ptr<vector<Field::Pointer> > Class::getFields(){
	return this->fields;
}

shared_ptr<vector<Method::Pointer> > Class::getMethods(){
	return this->methods;
}

void Class::setStaticFields(shared_ptr<vector<Slot> > staticFields){
	this->staticFields = staticFields;
}
shared_ptr<vector<Slot> > Class::getStaticFields(){
	return this->staticFields;
}