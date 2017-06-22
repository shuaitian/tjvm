#include "method.h"

Method::Method(MemberItemPtr memberItem,shared_ptr<Class> clazz):
	ClassMember(memberItem,clazz)
{
	CodeAttrItemPtr codeAttr = memberItem->getCodeAttribute();
	this->codeItem = codeAttr;
	if(codeAttr){
		maxStack = codeAttr->getMaxStack();
		maxLocals = codeAttr->getMaxLocals();
		code = codeAttr->getCode();
	}
}

uint16_t Method::getMaxStack(){
	return this->maxStack;
}
uint16_t Method::getMaxLocals(){
	return this->maxLocals;
}

shared_ptr<vector<Method::Pointer> > Method::builds(MethodMemberPtr method,shared_ptr<Class> clazz){
	shared_ptr<vector<Pointer> > ret = make_shared<vector<Pointer> >();
	MemItemVecPtr vec = method->getMemberItems();
	vector<MemberItemPtr>::iterator iter;
	for(iter=vec->begin();iter!=vec->end();++iter){
		MemberItemPtr item = *iter;
		Method::Pointer p(new Method(item,clazz));
		ret->push_back(p);
	}
	return ret;
}

shared_ptr<vector<u1> > Method::getCode(){
	return this->code;
}

shared_ptr<CodeAttrItem> Method::getCodeItem(){
	return this->codeItem;
}