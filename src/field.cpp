#include "field.h"
#include "attributeitem.h"

Field::Field(MemberItemPtr memberItem,shared_ptr<Class> clazz):
	ClassMember(memberItem,clazz)
{
	
}

shared_ptr<vector<Field::Pointer> > Field::builds(MemberPtr field,shared_ptr<Class> clazz){
	shared_ptr<vector<Pointer> > ret = make_shared<vector<Pointer> >();
	MemItemVecPtr vec = field->getMemberItems();
	vector<MemberItemPtr>::iterator iter;
	for(iter=vec->begin();iter!=vec->end();++iter){
		MemberItemPtr item = *iter;
		Field::Pointer p(new Field(item,clazz));
		ret->push_back(p);
	}
	return ret;
}

void Field::setSlotId(uint32_t slotId){
	this->slotId = slotId;
}
uint32_t Field::getSlotId(){
	return this->slotId;
}

bool Field::isDoubleOrLong(){
	return descriptor=="J" || descriptor=="D";	
}

bool Field::hasConstValueIndex(){
	ConstantValueAttrItemPtr attrItem = memberItem->getConstValueAttr();
	if(attrItem)
		return true;
	else 
		return false;
}

uint16_t Field::getConstValueIndex(){
	ConstantValueAttrItemPtr attrItem = memberItem->getConstValueAttr();
	if(!attrItem){
		printf("ConstantValue does not exist in '%s'\n",name.c_str());
		exit(0);
	}
	return attrItem->getConstValueIndex();
}

bool Field::isAccessibleTo(shared_ptr<Class> clazz){
	//TODO 
	return true;
}