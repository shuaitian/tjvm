#include "memberitemreader.h"
#include <stdio.h>

MemReaderPtr MemberItemReader::self;

MemReaderPtr MemberItemReader::instance(){
	if(!self){
		MemReaderPtr temp(new MemberItemReader());
		self = temp;
	}
	return self;
}

MemberItemPtr MemberItemReader::read(shared_ptr<ClassReader> classReader){
	MemberItemPtr ret = make_shared<MemberItem>();
	ret->setAccessFlags(classReader->readU2());
	ret->setNameIndex(classReader->readU2());
	ret->setDescriptorIndex(classReader->readU2());
//	ret->setAttributesCount(classReader->readU2());
	ret->setAttributes(readAttributes(classReader));
	ret->setAttributesCount(ret->getAttributes()->size());
	return ret;
}

AttrVecPtr MemberItemReader::readAttributes(shared_ptr<ClassReader> classReader){
	AttrVecPtr ret = make_shared<vector<Attribute> >();
	u2 attrbutesCount = classReader->readU2();
	for(u2 i=0;i<attrbutesCount;i++){
		Attribute attr;
		attr.setAttrNameIndex(classReader->readU2());
		attr.setAttrLength(classReader->readU4());
		attr.setInfo(classReader->readBytes(attr.getAttrLength()));
		ret->push_back(attr);		
	}
	return ret;
}
