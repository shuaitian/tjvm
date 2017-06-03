#include "method.h"

Method::Method(MemberItemPtr memberItem):
	ClassMember(memberItem)
{
	CodeAttrItemPtr codeAttr = memberItem->getCodeAttribute();
	if(codeAttr){
		maxStack = codeAttr->getMaxStack();
		maxLocals = codeAttr->getMaxLocals();
		code = codeAttr->getCode();
	}
}

shared_ptr<vector<Method::Pointer> > Method::builds(MethodMemberPtr method){
	shared_ptr<vector<Pointer> > ret = make_shared<vector<Pointer> >();
	MemItemVecPtr vec = method->getMemberItems();
	vector<MemberItemPtr>::iterator iter;
	for(iter=vec->begin();iter!=vec->end();++iter){
		MemberItemPtr item = *iter;
		Method::Pointer p(new Method(item));
		ret->push_back(p);
	}
	return ret;
}