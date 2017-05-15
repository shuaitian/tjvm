#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/exception/all.hpp>
#include <string>
#include <vector>
#include "config.h"
#include "ziputil.h"
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
	ZipUtil zip("my.zip");
	//vector<string> fileNames = zip.getFileNames();
	const char* filename = "hello.txt";
	cout << "extract file :" << filename << endl;
	shared_ptr<ByteArray> byteArray = zip.extractFileByName(filename);
	cout << "byteArray size:" << byteArray->getCurrentSize() << endl; 
//	cout << "byteArray content:" << byteArray->getData() << endl;
	for(unsigned long i=0; i<byteArray->getCurrentSize(); i++){
		if((*byteArray)[i] == ' ') continue;
		cout << (*byteArray)[i];
	}

	cout << endl;
}

void printConfig(){
	shared_ptr<Config> config = Config::instance();
	cout << "class path :" << config->get("classpath") << endl;
	cout << "jre home:" << config->get("Xjre") << endl;
	cout << "main class:" << config->get("mainClass") << endl;
}
