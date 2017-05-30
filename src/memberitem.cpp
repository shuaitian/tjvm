#include "memberitem.h"

CodeAttrItemPtr MemberItem::getCodeAttribute(){
	vector<Attribute>::iterator iter;
	for(iter=attributes->begin();iter!=attributes->end();++iter){
		if((*iter).getAttrName() == "Code")
			return static_pointer_cast<CodeAttrItem>((*iter).getAttributeItem());
	}
	return CodeAttrItemPtr();
}
