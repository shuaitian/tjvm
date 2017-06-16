#include "field.h"

Field::Field(MemberItemPtr memberItem):
	ClassMember(memberItem)
{
	
}

shared_ptr<vector<Field::Pointer> > Field::builds(MemberPtr field){
	shared_ptr<vector<Pointer> > ret = make_shared<vector<Pointer> >();
	MemItemVecPtr vec = field->getMemberItems();
	vector<MemberItemPtr>::iterator iter;
	for(iter=vec->begin();iter!=vec->end();++iter){
		MemberItemPtr item = *iter;
		Field::Pointer p(new Field(item));
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