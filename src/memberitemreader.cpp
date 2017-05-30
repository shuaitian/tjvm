#include "memberitemreader.h"
#include <vector>
#include <stdio.h>
using namespace std;

MemReaderPtr MemberItemReader::self;

MemReaderPtr MemberItemReader::instance(){
	if(!self){
		MemReaderPtr temp(new MemberItemReader());
		self = temp;
	}
	return self;
}

MemberItemPtr MemberItemReader::read(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
	MemberItemPtr ret = make_shared<MemberItem>();
	ret->setAccessFlags(classReader->readU2());
	ret->setNameIndex(classReader->readU2());
	ret->setName(constPoolPtr->readUTF8ByIndex(ret->getNameIndex()));
	ret->setDescriptorIndex(classReader->readU2());
	ret->setDescriptor(constPoolPtr->readUTF8ByIndex(ret->getDescriptorIndex()));
//	ret->setAttributesCount(classReader->readU2());
	ret->setAttributes(readAttributes(classReader,constPoolPtr));
	ret->setAttributesCount(ret->getAttributes()->size());
	return ret;
}

AttrVecPtr MemberItemReader::readAttributes(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
	AttrVecPtr ret = make_shared<vector<Attribute> >();
	u2 attrbutesCount = classReader->readU2();
	for(u2 i=0;i<attrbutesCount;i++){
		Attribute attr;
		attr.setAttrNameIndex(classReader->readU2());
		parseAttribute(classReader,constPoolPtr,attr);
	//	attr.setAttrLength(classReader->readU4());
	//	attr.setInfo(classReader->readBytes(attr.getAttrLength()));
	//	attr.setAttributeItem((AttributeParser::instance())->parse(constPoolPtr->readUTF8ByIndex(attr.getAttrNameIndex()),attr.getInfo()));
		ret->push_back(attr);		
	}
	return ret;
}

AttrItemPtr MemberItemReader::readDeprecated(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){ 
	u4 len = classReader->readU4();
	if(len != 0){
		printf("error readDeprecated 'len!=0'\n");
		exit(-1);
		//TODO throw exception
	}
	return static_pointer_cast<AttributeItem>(make_shared<DeprecatedAttrItem>());
}

AttrItemPtr MemberItemReader::readSynthetic(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
    u4 len = classReader->readU4();
   if(len != 0){
		printf("error readSynthetic 'len!=0'\n");
		exit(-1);
		//TODO throw exception
	}
	return static_pointer_cast<AttributeItem>(make_shared<SyntheticAttrItem>());
}

AttrItemPtr MemberItemReader::readSourceFile(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
    u4 len = classReader->readU4();
    if(len != 2){
		printf("error readSourceFile 'len!=2'\n");
		exit(-1);
		//TODO throw exception
	}
	shared_ptr<SourceFileAttrItem> ret = make_shared<SourceFileAttrItem>();
	u2 sourceFileIndex = classReader->readU2();
	ret->setSourceFileIndex(sourceFileIndex);
	ret->setSourceFile(constPoolPtr->readUTF8ByIndex(sourceFileIndex));
	//printf("SourceFile:%s\n",(ret->getSourceFile()).data());
    return static_pointer_cast<AttributeItem>(ret);
}

AttrItemPtr MemberItemReader::readConstantValue(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
    u4 len = classReader->readU4();
     if(len != 2){
		printf("error readConstantValue 'len!=2'\n");
		exit(-1);
		//TODO throw exception
	}
	shared_ptr<ConstantValueAttrItem> ret = make_shared<ConstantValueAttrItem>();
	u2 constValueIndex = classReader->readU2();
	ret->setConstValueIndex(constValueIndex);
	printf("const value index:%u\n",constValueIndex);
    return static_pointer_cast<AttributeItem>(ret);
}

AttrItemPtr MemberItemReader::readCode(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
    u4 len __attribute__((unused));
	len = classReader->readU4();
    //classReader->readBytes(len);
	shared_ptr<CodeAttrItem> ret = make_shared<CodeAttrItem>();
	u2 max_stack = classReader->readU2();
	u2 max_locals = classReader->readU2();
	u4 code_length = classReader->readU4();
	ret->setMaxStack(max_stack);
	ret->setMaxLocals(max_locals);
	ret->setCodeLength(code_length);
	shared_ptr<vector<u1> > code = make_shared<vector<u1> >();
	for(u4 i=0; i<code_length;i++){
		code->push_back(classReader->readU1());
	}
	ret->setCode(code);

	u2 exceptionTableLength = classReader->readU2();
	ret->setExceptionTableLength(exceptionTableLength);
	shared_ptr<vector<ExceptionTableEntry> > exceptionTable = make_shared<vector<ExceptionTableEntry> >();
	for(u2 i=0; i<exceptionTableLength;i++){
		ExceptionTableEntry entry;
		entry.startPC = classReader->readU2();
		entry.endPC = classReader->readU2();
		entry.handlerPC = classReader->readU2();
		entry.catchType = classReader->readU2();
		exceptionTable->push_back(entry);
	}
	ret->setExceptionTable(exceptionTable);

	//u2 attributes_count = classReader->readU2();
	AttrVecPtr attributes = readAttributes(classReader,constPoolPtr);
	ret->setAttributes(attributes);
    return static_pointer_cast<AttributeItem>(ret);
}

AttrItemPtr MemberItemReader::readExceptions(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
	u4 len __attribute__((unused));
	len = classReader->readU4();
	shared_ptr<ExceptionsAttrItem> ret = make_shared<ExceptionsAttrItem>();
	u2 numberOfExceptions = classReader->readU2();
	ret->setNumberOfExceptions(numberOfExceptions);
	shared_ptr<vector<u2> > exceptionIndexTable = make_shared<vector<u2> >();
	for(u2 i=0; i<numberOfExceptions;i++){
		u2 exceptionIndex = classReader->readU2();
		exceptionIndexTable->push_back(exceptionIndex);
	}
	ret->setExceptionIndexTable(exceptionIndexTable);
    return static_pointer_cast<AttributeItem>(ret);
}

AttrItemPtr MemberItemReader::readLineNumberTable(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
    u4 len __attribute__((unused));
	len = classReader->readU4();
    //classReader->readBytes(len);
	shared_ptr<LineNumberTableAttrItem> ret = make_shared<LineNumberTableAttrItem>();
	u2 lineNumberTableLength = classReader->readU2();
	ret->setLineNumberTableLength(lineNumberTableLength);
	shared_ptr<vector<LineNumberTableEntry> > lineNumberTable = make_shared<vector<LineNumberTableEntry> >();
	for(u2 i=0; i<lineNumberTableLength;i++){
		LineNumberTableEntry entry;
		entry.startPC = classReader->readU2();
		entry.lineNumber = classReader->readU2();
		lineNumberTable->push_back(entry);
	}
	ret->setLineNumberTable(lineNumberTable);
    return static_pointer_cast<AttributeItem>(ret);
}

AttrItemPtr MemberItemReader::readLocalVariableTable(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr){
    u4 len = classReader->readU4();
    classReader->readBytes(len);
    return make_shared<AttributeItem>();
} 

void MemberItemReader::parseAttribute(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr,Attribute& attr){
	string_ref name = constPoolPtr->readUTF8ByIndex(attr.getAttrNameIndex());
	attr.setAttrName(name);
	if("Deprecated" == name){
		attr.setAttributeItem(readDeprecated(classReader,constPoolPtr));
	}
	else if("Synthetic" == name){
		attr.setAttributeItem(readSynthetic(classReader,constPoolPtr));
	}
	else if("SourceFile" == name){
        attr.setAttributeItem(readSourceFile(classReader,constPoolPtr));
    }
	else if("ConstantValue" == name){
		attr.setAttributeItem(readConstantValue(classReader,constPoolPtr));
	}
	else if("Code" == name){
		attr.setAttributeItem(readCode(classReader,constPoolPtr));
	}
	else if("Exceptions" == name){
		attr.setAttributeItem(readExceptions(classReader,constPoolPtr));
	}
	else if("LineNumberTable" == name){
		attr.setAttributeItem(readLineNumberTable(classReader,constPoolPtr));
	}
	else if("LocalVariableTable" == name){
		attr.setAttributeItem(readLocalVariableTable(classReader,constPoolPtr));
	}
	else{
		u4 len = classReader->readU4();
		classReader->readBytes(len);
		printf("unknow attr name:%s\n",name.data());
	}
}
