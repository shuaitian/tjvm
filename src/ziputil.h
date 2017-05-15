#ifndef _ZIPUTIL_H_
#define _ZIPUTIL_H_
#include <boost/utility/string_ref.hpp>
#include <boost/smart_ptr.hpp>
#include <string>
#include <vector>

#include <unzip.h>

#include "bytearray.h"
using namespace boost;
using namespace std;

class ZipUtil{
private:
	string zipFilename;
	vector<string> fileList;
	unzFile uf;
	int extractCurrentFile();
public:
	ZipUtil(string_ref filename);
	vector<string>& getFileNames();
	shared_ptr<ByteArray> extractFileByName(string_ref filename);
};

#endif
