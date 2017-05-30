#include "member.h"
#include <stdio.h>
void Member::display(const char* memberType){
	vector<shared_ptr<MemberItem> >::iterator iter;
	printf("%s count:%u\n",memberType,(unsigned int)member_items->size());
	for(iter = member_items->begin();iter!=member_items->end();++iter){
		MemberItemPtr memItem = *iter;
		printf("\tname index:%u\n",memItem->getNameIndex());
		printf("\tdescriptor index:%u\n",memItem->getDescriptorIndex());
		printf("\tattribute count:%u\n",memItem->getAttributesCount());
		printf("\t-----------------\n");
	}
}

MemberItemPtr Member::getMemberItemByNameAndDesc(string_ref name,string_ref desc){
	vector<MemberItemPtr>::iterator iter;
	for(iter=member_items->begin();iter!=member_items->end();++iter){
		if(((*iter)->getName() == name) && ((*iter)->getDescriptor() == desc)){
			return (*iter);
		}
	}
	return MemberItemPtr();
}
