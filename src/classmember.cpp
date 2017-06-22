#include "classmember.h"

ClassMember::ClassMember(MemberItemPtr memberItem,shared_ptr<Class> clazz):
	accessFlags(memberItem->getAccessFlags()),
	name(memberItem->getName().data()),
	descriptor(memberItem->getDescriptor().data())
{
	this->memberItem = memberItem;
	this->clazz = clazz;
}

string_ref ClassMember::getName(){
	return this->name;
}
string_ref ClassMember::getDescriptor(){
	return this->descriptor;
}
shared_ptr<Class> ClassMember::getClass(){
	return this->clazz;
}
bool ClassMember::is(u2 flag){
	return 0 != (accessFlags & flag);
}