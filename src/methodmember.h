#ifndef _METHODMEMBER_H_
#define _METHODMEMBER_H_
#include <boost/smart_ptr.hpp>
#include "member.h"
#include "memberitem.h"
using namespace boost;
class MethodMember;
typedef shared_ptr<MethodMember> MethodMemberPtr;
class MethodMember : public Member 
{
public:
	MemberItemPtr getMainMethod();
};

#endif