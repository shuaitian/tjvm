#ifndef _CLASSENTITY_H_
#define _CLASSENTITY_H_
#include "def.h"
#include "constantpool.h"
#include "member.h"
#include <vector>
#include <boost/smart_ptr.hpp>
using namespace std;
class ClassEntity{
private:
	u4 magic;
	u2 minorVersion;
	u2 majorVersion;
	shared_ptr<ConstantPool> constantPool;
	u2 accessFlags;
	u2 thisClass;
	u2 superClass;
	shared_ptr<vector<u2> > interfaces;
	MemberPtr fieldMember;
	MemberPtr methodMember;
public:
	u4 getMagic(){
		return magic;
	}
	u2 getMinorVersion(){
		return minorVersion;
	}
	u2 getMajorVersion(){
		return majorVersion;
	}
	shared_ptr<ConstantPool> getConstantPool(){
		return constantPool;
	}
	u2 getAccessFlags(){
		return accessFlags;
	}
	u2 getThisClass(){
		return thisClass;
	}
	u2 getSuperClass(){
		return superClass;
	}
	shared_ptr<vector<u2> > getInterfaces(){
		return interfaces;
	}
	MemberPtr getFieldMember(){
		return fieldMember;
	}
	MemberPtr getMethodMember(){
		return methodMember;
	}
	void setMagic(u4 magic){
		this->magic = magic;
	}
	void setMinorVersion(u2 minorVersion){
		this->minorVersion = minorVersion;
	}
	void setMajorVersion(u2 majorVersion){
		this->majorVersion = majorVersion;
	}
	void setConstantPool(shared_ptr<ConstantPool> constantPool){
		this->constantPool = constantPool;
	}
	void setAccessFlags(u2 accessFlags){
		this->accessFlags = accessFlags;
	}
	void setThisClass(u2 thisClass){
		this->thisClass = thisClass;
	}
	void setSuperClass(u2 superClass){
		this->superClass = superClass;
	}
	void setInterfaces(shared_ptr<vector<u2> > interfaces){
		this->interfaces = interfaces;
	}
	void setFieldMember(MemberPtr fieldMember){
		this->fieldMember = fieldMember;
	}
	void setMethodMember(MemberPtr methodMember){
		this->methodMember = methodMember;
	}
};

#endif
