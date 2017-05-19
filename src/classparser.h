#ifndef _CLASSPARSER_H_
#define _CLASSPARSER_H_
#include <boost/smart_ptr.hpp>
#include "classentity.h"
#include "bytearray.h"
#include "classreader.h"

using namespace boost;

class ClassParser{
private:
	static shared_ptr<ClassParser> self;
	ClassParser();
	shared_ptr<ConstantPool> readConstantPool(shared_ptr<ClassReader> classReader);
public:
	static shared_ptr<ClassParser> instance();
	shared_ptr<ClassEntity> parser(shared_ptr<ByteArray> byteArray);
};

#endif
