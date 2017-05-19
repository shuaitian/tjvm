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
using namespace std;
using namespace boost;

const char* VERSION = "1.0.0";

void printConfig();
void start();

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

	start();
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
