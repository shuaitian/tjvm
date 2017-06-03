#ifndef _METHOD_H_
#define _METHOD_H_
#include <boost/smart_ptr.hpp>
#include "methodmember.h"
#include "classmember.h"
using namespace boost;
class Method : public ClassMember
{
private:
	Method(MemberItemPtr memberItem);
	uint16_t maxStack;
	uint16_t maxLocals;
	shared_ptr<vector<u1> > code;	
public:
	typedef shared_ptr<Method> Pointer;
public:
	static shared_ptr<vector<Pointer> > builds(MethodMemberPtr method);
};

#endif