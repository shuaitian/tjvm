#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_
#include <boost/smart_ptr.hpp>
#include "def.h"
#include "bytearray.h"
#include "attributeitem.h"
#include <boost/utility/string_ref.hpp>

using namespace boost;

class AttributeItem;
class Attribute{
public:
	typedef shared_ptr<Attribute> AttributePtr;
private:
	u2 	attrNameIndex;
	string_ref attrName;
	u4 attrLength;
	ByteArrayPtr info;
	shared_ptr<AttributeItem> attrItem;
public:
	void setAttrName(string_ref name){
		this->attrName = name;
	}
	string_ref getAttrName(){
		return this->attrName;
	}

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
	
	void setAttributeItem(shared_ptr<AttributeItem> attrItem){
		this->attrItem = attrItem;
	}

	shared_ptr<AttributeItem> getAttributeItem(){
		return this->attrItem;	
	}
};

#endif


