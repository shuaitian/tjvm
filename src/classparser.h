#ifndef _CLASSPARSER_H_
#define _CLASSPARSER_H_
#include <boost/smart_ptr.hpp>
#include "classentity.h"
#include "bytearray.h"
#include "classreader.h"
#include "def.h"
#include "member.h"
#include "methodmember.h"
#include <vector>

using namespace std;
using namespace boost;

class ClassParser{
private:
	static shared_ptr<ClassParser> self;
	ClassParser();
	shared_ptr<ConstantPool> readConstantPool(shared_ptr<ClassReader> classReader);
	shared_ptr<vector<u2> > readInterfaces(shared_ptr<ClassReader> classReader);
	MemberPtr readFieldMember(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	MethodMemberPtr readMethodMember(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrVecPtr readAttributes(shared_ptr<ClassReader> classReader);
public:
	static shared_ptr<ClassParser> instance();
	shared_ptr<ClassEntity> parser(shared_ptr<ByteArray> byteArray);
};

#endif
