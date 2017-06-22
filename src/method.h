#ifndef _METHOD_H_
#define _METHOD_H_
#include <boost/smart_ptr.hpp>
#include "methodmember.h"
#include "classmember.h"
class Class;
using namespace boost;
class Method : public ClassMember
{
private:
	Method(MemberItemPtr memberItem,shared_ptr<Class> clazz);
	uint16_t maxStack;
	uint16_t maxLocals;
	shared_ptr<vector<u1> > code;	
	shared_ptr<CodeAttrItem> codeItem;
public:
	typedef shared_ptr<Method> Pointer;
public:
	static shared_ptr<vector<Pointer> > builds(MethodMemberPtr method,shared_ptr<Class> clazz);
	shared_ptr<vector<u1> > getCode();
	shared_ptr<CodeAttrItem> getCodeItem();
	uint16_t getMaxStack();
	uint16_t getMaxLocals();
};

#endif