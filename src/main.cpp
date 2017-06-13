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
#include "bytecodereader.h"
#include "instructionengine.h"
#include "interpreter.h"
#include "class.h"

using namespace std; 
using namespace boost;

const char* VERSION = "1.0.0";

void printConfig();
void start();
void testEngine();

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
	//testFrame();
	testEngine();
}

void testEngine(){
	shared_ptr<Config> config = Config::instance();
	shared_ptr<ClassFileReader> classFileReader = ClassFileReader::instance();
	shared_ptr<ByteArray> classFile = classFileReader->readClassFile(config->get("mainClass"));
	if(classFile){
		ClassEntityPtr classEntity = ClassParser::instance()->parser(classFile);
		Class::Pointer clazz = Class::build(classEntity);
		classEntity->getConstantPool()->display();
		MemberItemPtr mainItem = classEntity->getMethodMember()->getMainMethod();
		//classEntity->getConstantPool()->display();
		if(mainItem){
			InterpreterPtr interpreter = Interpreter::build();
			interpreter->interpret(mainItem);
		}
	}
}


void start(){
}

void printConfig(){
	shared_ptr<Config> config = Config::instance();
	cout << "class path :" << config->get("classpath") << endl;
	cout << "jre home:" << config->get("Xjre") << endl;
	cout << "main class:" << config->get("mainClass") << endl;
}
