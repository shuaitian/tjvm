#ifndef _CLASSMEMBER_H_
#define _CLASSMEMBER_H_
#include "def.h"
#include "memberitem.h"
#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
using namespace boost;
using namespace std;
class Class;
class ClassMember
{
protected:
	uint16_t accessFlags;
	string name;
	string descriptor;
	shared_ptr<Class> clazz;
	ClassMember(MemberItemPtr memberItem);
public:
	string_ref getName();
	string_ref getDescriptor();
	shared_ptr<Class> getClass();
	bool is(u2 flag);
};

#endif