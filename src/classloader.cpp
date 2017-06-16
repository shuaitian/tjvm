#include "classloader.h"
#include "class.h"
#include "config.h"
#include "classfilereader.h"
#include "classparser.h"
#include "field.h"
#include "object.h"
#include <stdio.h>

ClassLoader::Pointer ClassLoader::build(){
	Pointer ret(new ClassLoader());
	return ret;
}
shared_ptr<Class> ClassLoader::loadClass(string_ref name){
	map<string,shared_ptr<Class> >::iterator iter = classMap->find(name.data());
	if(iter != classMap->end())
		return iter->second;
	return loadNonArrayClass(name);
}

ClassLoader::ClassLoader()	
{
	classMap = make_shared<map<string,Class::Pointer> >();
}

shared_ptr<Class> ClassLoader::loadNonArrayClass(string_ref name){
	Class::Pointer ret;
	shared_ptr<Config> config = Config::instance();
	shared_ptr<ClassFileReader> classFileReader = ClassFileReader::instance();
	shared_ptr<ByteArray> classFile = classFileReader->readClassFile(name);
	if(!classFile)
	{
		printf("error class '%s' not found\n",name.data());
		exit(0);
	};

	ClassEntityPtr classEntity = ClassParser::instance()->parser(classFile);
	ret = Class::build(classEntity);
	ret->setClassLoader(ClassLoader::Pointer(this));
	resolveSuperClass(ret);
	resolveInterfaces(ret);
	(*classMap)[string(name.data())] = ret;
	//以上对应于虚拟机规范中类加载过程的第一阶段 加载阶段，将class字节流解析成虚拟机可以识别的class结构体
	
	link(ret); //类加载过程的第二阶段 链接；
	return ret;
}

void ClassLoader::resolveSuperClass(shared_ptr<Class> clazz){
	if(clazz->getName() != "java/lang/Object"){
		string_ref superClassName = clazz->getSuperClassName();
		clazz->setSuperClass(clazz->getClassLoader()->loadClass(superClassName));
	}
}
void ClassLoader:: resolveInterfaces(shared_ptr<Class> clazz){
	shared_ptr<vector<string> >  interfaceNames = clazz->getInterfaceNames();
	shared_ptr<vector<shared_ptr<Class> > > interfaces = make_shared<vector<shared_ptr<Class> > >();
	vector<string>::iterator iter;
	for(iter = interfaceNames->begin();iter != interfaceNames->end(); ++iter){
		interfaces->push_back(clazz->getClassLoader()->loadClass((*iter)));
	}
	clazz->setInterfaces(interfaces);
}

void ClassLoader::link(shared_ptr<Class> clazz){
	verify(clazz);
	prepare(clazz);
}

void ClassLoader::verify(shared_ptr<Class> clazz){
	//TODO 验证class文件 参考The Java Virtual Machine Specification Java SE 8 Edition chapter 4.10
}

void ClassLoader::prepare(shared_ptr<Class> clazz){
	//Preparation involves creating the static fields for a class or interface and initializing such fields to their default values.
	calcInstanceFieldSlotIds(clazz);
	calcStaticFieldSlotIds(clazz);
	allocAndInitStaticVars(clazz);
}


shared_ptr<vector<string> > ClassLoader::mapedNames(){
	shared_ptr<vector<string> > ret = make_shared<vector<string> >();
	map<string,shared_ptr<Class> >::iterator iter;
	for(iter = classMap->begin(); iter != classMap->end(); ++iter){
		ret->push_back(iter->second->getName().data());
		//printf("class name:%s\n",iter->second->getName().data());
		//shared_ptr<vector<Method::Pointer> > methods = iter->second->getMethods();
		//vector<Method::Pointer>::iterator iter2;
		//for(iter2 = methods->begin();iter2!=methods->end();++iter2){
		//	printf("\tmethod:%s\n",(*iter2)->getName().data());
		//}
	}
	return ret;
}

void ClassLoader::calcInstanceFieldSlotIds(shared_ptr<Class> clazz){
	uint32_t slotId = 0;
	if(clazz->getSuperClass()){
		slotId = clazz->getSuperClass()->getInstanceSlotCount();
	}
	shared_ptr<vector<Field::Pointer> > fields = clazz->getFields();
	vector<Field::Pointer>::iterator iter;
	for(iter=fields->begin();iter!=fields->end();++iter){
		if(!((*iter)->is(ACC_STATIC))){
			(*iter)->setSlotId(slotId++);
			//slotId++;
			if((*iter)->isDoubleOrLong()){
				slotId++;
			}
		}
	}
	clazz->setInstanceSlotCount(slotId);
}
void ClassLoader::calcStaticFieldSlotIds(shared_ptr<Class> clazz){
	uint32_t slotId = 0;
	if(clazz->getSuperClass()){
		slotId = clazz->getSuperClass()->getStaticSlotCount();
	}
	shared_ptr<vector<Field::Pointer> > fields = clazz->getFields();
	vector<Field::Pointer>::iterator iter;
	for(iter=fields->begin();iter!=fields->end();++iter){
		if((*iter)->is(ACC_STATIC)){
			(*iter)->setSlotId(slotId++);
			if((*iter)->isDoubleOrLong()){
				slotId++;
			}
		}
	}
	clazz->setStaticSlotCount(slotId);
}
void ClassLoader::allocAndInitStaticVars(shared_ptr<Class> clazz){
	shared_ptr<vector<Slot> > staticFields = make_shared<vector<Slot> >();
	for(uint32_t i=0; i<clazz->getStaticSlotCount();i++){
		Slot slot;
		slot.num = 0;
		slot.ref = Object::nullPtr();
		staticFields->push_back(slot);
	}

}