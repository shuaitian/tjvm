#include "cpdef.h"
#include "class.h"
#include "field.h"
#include "classloader.h"

shared_ptr<Class> Resolver::resolveClassRef(shared_ptr<ClassRef> classRef,shared_ptr<Class> sourceClass){
	shared_ptr<ClassLoader> loader = sourceClass->getClassLoader();
	shared_ptr<Class> ret = loader->loadClass(classRef->name);
	if(!ret->isAccessibleTo(sourceClass)){
		//TODO throw exception
		printf("error IllegalAccessError\n");
	}
	return ret;
}
shared_ptr<Field> Resolver::resolveFieldRef(shared_ptr<FieldRef> fieldRef,shared_ptr<Class> sourceClass){
	shared_ptr<ClassLoader> loader = sourceClass->getClassLoader();
	shared_ptr<Class> c = loader->loadClass(fieldRef->className);
	shared_ptr<Field> field = c->lookupField(fieldRef->descriptor);
	if(!field){
		//TODO throw exception
		printf("error NoSuchFieldError[%s,%s]\n",fieldRef->className.c_str(),fieldRef->name.c_str());
		exit(0);
	}

	if(!field->isAccessibleTo(sourceClass)){
		//TODO throw exception
		printf("error IllegalAccessError\n");
		exit(0);
	}
	return field;
}