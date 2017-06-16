#ifndef _CLASSREADER_H_
#define _CLASSREADER_H_
#include "def.h"
#include "bytearray.h"
#include <boost/smart_ptr.hpp>
#include <vector>
using namespace boost;
using namespace std;

class ClassReader{
private:
	shared_ptr<ByteArray> data;
	unsigned long index;
public:
	ClassReader(shared_ptr<ByteArray> data);
	u1 readU1();
	u2 readU2();
	u4 readU4();
	u8 readU8();
	
	vector<u2> readU2Table();
	shared_ptr<ByteArray> readBytes(unsigned long length);
	
};

#endif
