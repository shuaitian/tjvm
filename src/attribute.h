#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
#include <boost/smart_ptr.hpp>
#include "def.h"
#include "bytearray.h"
using namespace boost;
class Attribute{
public:
	typedef shared_ptr<Attribute> AttributePtr;
private:
	u2 	attrNameIndex;
	u4 attrLength;
	ByteArrayPtr info;
public:
	void setAttrNameIndex(u2 index){
		this->attrNameIndex = index;
	}	
	u2 getAttrNameIndex(){
		return this->attrNameIndex;
	}

	void setAttrLength(u4 length){
		this->attrLength = length;
	}
	u4 getAttrLength(){
		return attrLength;
	}

	void setInfo(ByteArrayPtr info){
		this->info = info;
	}
	ByteArrayPtr getInfo(){
		return this->info;
	}
};

#endif


