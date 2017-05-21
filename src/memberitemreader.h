#ifndef _MEMBERITEMREADER_H_
#define _MEMBERITEMREADER_H_
#include <boost/smart_ptr.hpp>
#include "classreader.h"
#include "memberitem.h"
#include "attribute.h"

using namespace boost;
class MemberItemReader;

typedef shared_ptr<MemberItemReader> MemReaderPtr;

class MemberItemReader{
private:
	static MemReaderPtr self;
	MemberItemReader(){}
	AttrVecPtr readAttributes(shared_ptr<ClassReader> classReader);
public:
	static MemReaderPtr instance();
	MemberItemPtr read(shared_ptr<ClassReader> classReader);
};

#endif
