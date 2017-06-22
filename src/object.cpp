#include "object.h"

ObjectPtr Object::nullPtr(){
	return ObjectPtr();
}

Object::Object(shared_ptr<Class> clazz){
	
}

shared_ptr<Object> Object::newObject(shared_ptr<Class> clazz){
	shared_ptr<Object> ret(new Object(clazz));
	return ret;
}
