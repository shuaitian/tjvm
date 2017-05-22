#ifndef _MEMBERITEMREADER_H_
#define _MEMBERITEMREADER_H_
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include "constantpool.h"
#include "classreader.h"
#include "memberitem.h"
#include "attribute.h"
#include "def.h"

using namespace boost;
class MemberItemReader;

typedef shared_ptr<MemberItemReader> MemReaderPtr;

class MemberItemReader{
private:
	static MemReaderPtr self;
	MemberItemReader(){}
	void parseAttribute(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr,Attribute& attr);
	AttrItemPtr readDeprecated(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrItemPtr readSynthetic(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrItemPtr readSourceFile(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrItemPtr readConstantValue(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrItemPtr readCode(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrItemPtr readExceptions(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrItemPtr readLineNumberTable(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	AttrItemPtr readLocalVariableTable(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
public:
	AttrVecPtr readAttributes(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
	static MemReaderPtr instance();
	MemberItemPtr read(shared_ptr<ClassReader> classReader,ConstantPoolPtr constPoolPtr);
};

#endif
