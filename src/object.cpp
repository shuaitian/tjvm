#include "object.h"
#include "class.h"

ObjectPtr Object::nullPtr(){
	return ObjectPtr();
}

Object::Object(shared_ptr<Class> clazz){
	fields = make_shared<vector<Slot> >();
	int count = clazz->getInstanceSlotCount();
	for(int i=0; i<count ;i++){
		Slot slot;
		slot.num = 0;
		slot.ref = nullPtr();
		fields->push_back(slot);
	}
}

shared_ptr<Object> Object::newObject(shared_ptr<Class> clazz){
	shared_ptr<Object> ret(new Object(clazz));
	return ret;
}

shared_ptr<vector<Slot> > Object::getFields(){
	return this->fields;
}
