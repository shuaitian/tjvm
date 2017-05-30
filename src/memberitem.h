#ifndef _MEMBERITEM_H_
#define _MEMBERITEM_H_
#include "def.h"
#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include "attribute.h"
#include <stdio.h>
using namespace std;
using namespace boost;
class MemberItem;

typedef shared_ptr<MemberItem> MemberItemPtr;
typedef shared_ptr<vector<Attribute> > AttrVecPtr;

class MemberItem{
private:
	u2 access_flags;
	u2 name_index;
	string_ref name;
	u2 descriptor_index;
	u2 attributes_count;
	string_ref descriptor;
	AttrVecPtr attributes;
public:
	CodeAttrItemPtr getCodeAttribute();

	void setDescriptor(string_ref descriptor){
		this->descriptor = descriptor;
	}

	string_ref getDescriptor(){
		return this->descriptor;
	}

	void setName(string_ref name){
		this->name = name;
	}
	string_ref getName(){
		return this->name;
	}

	void setAccessFlags(u2 access_flags){
		this->access_flags = access_flags;
	}
	u2 getAccessFlags(){
		return access_flags;
	}

	void setNameIndex(u2 name_index){
		this->name_index = name_index;
	}

	u2 getNameIndex(){
		return name_index;
	}

	void setDescriptorIndex(u2 descriptor_index){
		this->descriptor_index = descriptor_index;
	}
	
	u2 getDescriptorIndex(){
		return this->descriptor_index;
	}

	void setAttributesCount(u2 attributes_count){
		this->attributes_count = attributes_count;
	}

	u2 getAttributesCount(){
		return this->attributes_count;
	}

	void setAttributes(AttrVecPtr attributes){
		this->attributes = attributes;
	}

	AttrVecPtr getAttributes(){
		return this->attributes;
	}
};

#endif
