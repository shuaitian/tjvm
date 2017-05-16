#ifndef _CLASSFILEREADER_H_
#define _CLASSFILEREADER_H_
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include "bytearray.h"
using namespace std;
using namespace boost;
using namespace boost::filesystem;

class ClassFileReader{
private:
	static shared_ptr<ClassFileReader> self;
	ClassFileReader();
	string jre;
	string classpath;
	shared_ptr<ByteArray> travelDirectory(string_ref classFileName,const path &p);
	shared_ptr<ByteArray> findFileInJar(string_ref classFileName,const path &p);
	shared_ptr<ByteArray> readFileFromExsitPath(string_ref path);
public:
	static shared_ptr<ClassFileReader> instance();
	shared_ptr<ByteArray> readClassFile(string_ref classFileName);
};

#endif
