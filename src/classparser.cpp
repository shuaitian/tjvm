#include "classparser.h"
#include "classreader.h"
#include <stdio.h>
#include "constantitem.h"
#include "constantitemreader.h"

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
	return classEntity;
}

shared_ptr<ConstantPool> ClassParser::readConstantPool(shared_ptr<ClassReader> classReader){
	shared_ptr<ConstantPool> pool = make_shared<ConstantPool>();
	u2 poolSize = classReader->readU2();
	for(u2 i = 1; i < poolSize; i++){
		shared_ptr<ConstantItem> constantItem = ConstantItemReader::instance()->read(classReader);
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
