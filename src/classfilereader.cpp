#include "classfilereader.h"
#include "config.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "ziputil.h"
using namespace boost::filesystem;
using namespace std;

shared_ptr<ClassFileReader> ClassFileReader::self;

ClassFileReader::ClassFileReader():
	jre(),
	classpath()
{
	shared_ptr<Config> config = Config::instance();
	jre = config->get("jre");
	classpath = config->get("classpath");

	cout << "jre:" << jre << endl;
	cout << "classpath:" << classpath << endl;
}

shared_ptr<ClassFileReader> ClassFileReader::instance(){
	if(!self){
		shared_ptr<ClassFileReader> t(new ClassFileReader);
		self = t;
	}

	return self;
}

shared_ptr<ByteArray> ClassFileReader::readClassFile(string_ref classFileName){
	string cfnString = classFileName.to_string();
	replace_all(cfnString,".","/");
	cfnString += ".class";
	string_ref ucfn(cfnString);
	shared_ptr<ByteArray> ret;
	bool found = false;
	path jrePath(jre);
	if(!found){
		//find in bootstrap class path
		jrePath /= "lib";
		if(exists(jrePath)){
			ret = travelDirectory(ucfn,jrePath);
			if(ret)
				found = true;
		}
	}

	if(!found){
		//find in extension classpath
		jrePath /= "ext";
		if(exists(jrePath)){
			ret = travelDirectory(ucfn,jrePath);
			if(ret)
				found = true;
		}
	}

	if(!found){
		// find in user class path
		string filePath = classpath + "/" + cfnString;
	    ret = readFileFromExsitPath(filePath);
		if(!ret){
			if(exists(classpath))
				ret = travelDirectory(ucfn,classpath);
		}
		if(ret)
			found = true;
	}
	return ret;
}

shared_ptr<ByteArray> ClassFileReader::readFileFromExsitPath(string_ref path){
	shared_ptr<ByteArray> ret;
	if(exists(path.data())){
		ByteArray *ba = new ByteArray;
		ifstream in(path.data(),ios::in|ios::binary);
		char buffer[8192];
		int len = 0;
		while(!in.eof()){
			in.read(buffer,8192);
			len = in.gcount();
			ba->append(buffer,len);
		}
		ret = shared_ptr<ByteArray>(ba);
	}

	return ret;
}

shared_ptr<ByteArray> ClassFileReader::travelDirectory(string_ref classFileName,const path &p){
	shared_ptr<ByteArray> ret;
	directory_iterator end;
	for(directory_iterator pos(p);pos!=end;++pos){
		if(is_directory(*pos)){
			travelDirectory(classFileName,(*pos).path());
		}
		else{
			//handle
			const path &curFile = pos->path();
			if(curFile.extension().string() == ".jar"){
				ret = findFileInJar(classFileName,curFile);
				if(ret){
					break;
				}
			}
		}
	}
	return ret;
}

shared_ptr<ByteArray> ClassFileReader::findFileInJar(string_ref classFileName,const path& curFile){
	shared_ptr<ByteArray> ret;
	ZipUtil jarFile(curFile.string());
	vector<string> fileNames = jarFile.getFileNames();
	vector<string>::iterator iter = fileNames.begin();
	for(;iter!=fileNames.end();++iter){
		if(classFileName == (*iter)){
			ret = jarFile.extractFileByName(classFileName);
			break;
		}
	}
	return ret;
}
