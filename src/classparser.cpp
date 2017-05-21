#include "classparser.h"
#include "classreader.h"
#include <stdio.h>
#include "constantitem.h"
#include "constantitemreader.h"
#include "memberitemreader.h"

shared_ptr<ClassParser> ClassParser::self;


ClassParser::ClassParser(){

}

shared_ptr<ClassEntity> ClassParser::parser(shared_ptr<ByteArray> byteArray){
	shared_ptr<ClassReader> classReader = make_shared<ClassReader>(byteArray);
	shared_ptr<ClassEntity> classEntity = make_shared<ClassEntity>();
	classEntity->setMagic(classReader->readU4());		
	classEntity->setMinorVersion(classReader->readU2());
	classEntity->setMajorVersion(classReader->readU2());
	classEntity->setConstantPool(readConstantPool(classReader));
	classEntity->setAccessFlags(classReader->readU2());
	classEntity->setThisClass(classReader->readU2());
	classEntity->setSuperClass(classReader->readU2());
	classEntity->setInterfaces(readInterfaces(classReader));
	classEntity->setFieldMember(readFieldMember(classReader));
	classEntity->setMethodMember(readMethodMember(classReader));
	return classEntity;
}

MemberPtr ClassParser::readFieldMember(shared_ptr<ClassReader> classReader){
	MemberPtr ret = make_shared<Member>();
	u2 fieldMemberCount = classReader->readU2();
	MemReaderPtr memReader = MemberItemReader::instance();
//	printf("field count:%u\n",fieldMemberCount);
	MemItemVecPtr vec = make_shared<vector<shared_ptr<MemberItem> > >();
	for(u2 i = 0; i<fieldMemberCount;i++){
		MemberItemPtr memberItem = memReader->read(classReader);
		vec->push_back(memberItem); 
	}
	ret->setMemberItems(vec);
	return ret;
}

MemberPtr ClassParser::readMethodMember(shared_ptr<ClassReader> classReader){
	return readFieldMember(classReader);
}

shared_ptr<vector<u2> > ClassParser::readInterfaces(shared_ptr<ClassReader> classReader){
	u2 interfacesCount = classReader->readU2();
	shared_ptr<vector<u2> > ret = make_shared<vector<u2> >();
	for(u2 i=0; i<interfacesCount;i++){
		u2 index = classReader->readU2();
		printf("#%u",index);
		ret->push_back(index);
	}
	printf("\n");
	return  ret;
}

shared_ptr<ConstantPool> ClassParser::readConstantPool(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantPool> pool = make_shared<ConstantPool>();
	u2 poolSize = classReader->readU2();
	for(u2 i = 1; i < poolSize; i++){
		shared_ptr<ConstantItem> constantItem = ConstantItemReader::instance()->read(classReader);
		constantItem->setOwnIndex(i);
		if(constantItem->getTag() == CONSTANT_Long || constantItem->getTag() == CONSTANT_Double){
			i++;
		}
		pool->add(constantItem);		
	}
	return pool;
}


shared_ptr<ClassParser> ClassParser::instance(){
	if(!self){
		shared_ptr<ClassParser> temp(new ClassParser);
		self = temp;
	}
	return self;
}
