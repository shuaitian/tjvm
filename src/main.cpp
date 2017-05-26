#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/exception/all.hpp>
#include <string>
#include <vector>
#include <stdio.h>
#include "config.h"
#include "ziputil.h"
#include "classfilereader.h"
#include "classreader.h"
#include "classentity.h"
#include "classparser.h"
#include "frame.h"
#include "operandstack.h"

using namespace std; 
using namespace boost;

const char* VERSION = "1.0.0";

void printConfig();
void start();
void testFrame();

int main(int argc,char* argv[]){
	//parse config from command line
   	Config::build(argv,argc);
	shared_ptr<Config> config = Config::instance();
	
	//print help info
	if(config->contains("help")){
		cout << Config::instance()->getOpts();
		exit(0);
	}

	//print version info
	if(config->contains("version")){
		cout << VERSION << endl;
		exit(0);
	}

	if(!config->check()){
		cout << "[--help] for help" << endl;
		exit(0);
	}

	//start();
	testFrame();
}

void testFrame(){
	FramePtr frame = Frame::build(200,200);
	OperandStackPtr operandStack = frame->getOperandStack();
	operandStack->pushInt(100);
	operandStack->pushFloat(21.23);
	operandStack->pushLong(3232323);
	double d = 10.4;
	operandStack->pushDouble(d);
	
	cout << "double:" << operandStack->popDouble() << endl;
	cout << "long:" << operandStack->popLong() << endl;
	cout << "float:" << operandStack->popFloat() << endl;
	cout << "int:" << operandStack->popInt() << endl;
	
	cout << "----------------------------------" << endl;
	LocalVarsPtr localVars = frame->getLocalVars();
	localVars->setInt(0,12);
	localVars->setFloat(1,12.043434);
	localVars->setLong(2,4443424234);
	localVars->setDouble(4,55.66778);

	cout << "double:" << localVars->getDouble(4) << endl;
	cout << "long:" << localVars->getLong(2) << endl;
	cout << "float:" << localVars->getFloat(1) << endl;
	cout << "int:" << localVars->getInt(0) << endl;

}

void start(){
//	ZipUtil zip("my.zip");
//	//vector<string> fileNames = zip.getFileNames();
//	const char* filename = "hello.txt";
//	cout << "extract file :" << filename << endl;
//	shared_ptr<ByteArray> byteArray = zip.extractFileByName(filename);
//	cout << "byteArray size:" << byteArray->getCurrentSize() << endl; 
//	cout << "byteArray content:" << byteArray->getData() << endl;
//	for(unsigned long i=0; i<byteArray->getCurrentSize(); i++){
//		if((*byteArray)[i] == ' ') continue;
//		cout << (*byteArray)[i];
//	}
	shared_ptr<Config> config = Config::instance();
	shared_ptr<ClassFileReader> classFileReader = ClassFileReader::instance();
	shared_ptr<ByteArray> classFile = classFileReader->readClassFile(config->get("mainClass"));
	//cout << endl;
	if(classFile){
		cout << "Class File Size:" << classFile->getCurrentSize() << endl;
//		classFile->display();
//		ClassReader classReader(classFile);		
//		printf("%x",classReader.readU1());
//		printf(" %x\n",classReader.readU1());
		shared_ptr<ClassEntity> classEntity = ClassParser::instance()->parser(classFile);
		printf("magic:%x\n",classEntity->getMagic());
		printf("minor version:%d,major version:%d\n",classEntity->getMinorVersion(),classEntity->getMajorVersion());
		printf("constant pool size:%d\n",(classEntity->getConstantPool())->getSize());
		(classEntity->getConstantPool())->display();
		printf("this class:#%u\n",classEntity->getThisClass());
		printf("super class:#%u\n",classEntity->getSuperClass());
		//(classEntity->getFieldMember())->display("field");
		//(classEntity->getMethodMember())->display("method");
		printf("class attribute count:%u\n",(unsigned int)classEntity->getAttributes()->size());
		MemberPtr methodMember = classEntity->getMethodMember();
		MemItemVecPtr memberItems = methodMember->getMemberItems();
		printf("method member count:%u\n",(unsigned int)memberItems->size());
		vector<shared_ptr<MemberItem> >::iterator iter;
		for(iter=memberItems->begin();iter!=memberItems->end();++iter){
			MemberItemPtr memItemPtr = *iter;
			printf("method name:%s\n",(memItemPtr->getName()).data());
			AttrVecPtr attrs = memItemPtr->getAttributes();
			vector<Attribute>::iterator iter1;
			for(iter1=attrs->begin();iter1!=attrs->end();++iter1){
				Attribute attr = *iter1;
				shared_ptr<AttributeItem> attrItem= attr.getAttributeItem();
				if(attr.getAttrName() == "Code"){
					shared_ptr<CodeAttrItem> codeAttrItem = static_pointer_cast<CodeAttrItem>(attrItem);
					//printf("code length:%u\n",codeAttrItem->getCodeLength());
					//printf("exception table length:%u\n",codeAttrItem->getExceptionTableLength());
					AttrVecPtr codeAttr = codeAttrItem->getAttributes();
					vector<Attribute>::iterator codeAttrIter;
					for(codeAttrIter=codeAttr->begin();codeAttrIter!=codeAttr->end();++codeAttrIter){
						Attribute codeAttr = *codeAttrIter;
						shared_ptr<AttributeItem> codeAttrItem= codeAttr.getAttributeItem();
						if(codeAttr.getAttrName() == "LineNumberTable"){
							//printf("line number table \n");
						}
					}
				}
				if(attr.getAttrName() == "Exceptions"){
					shared_ptr<ExceptionsAttrItem> excepAttrItem = static_pointer_cast<ExceptionsAttrItem>(attrItem);
					printf("\texception count:%u\n",excepAttrItem->getNumberOfExceptions());
				}

				if(attr.getAttrName() == "LineNumberTable"){
					printf("line number table\n");
				}
				
			}
		}
	}
	else{
		cout << "not found" << endl;
	}
}

void printConfig(){
	shared_ptr<Config> config = Config::instance();
	cout << "class path :" << config->get("classpath") << endl;
	cout << "jre home:" << config->get("Xjre") << endl;
	cout << "main class:" << config->get("mainClass") << endl;
}
