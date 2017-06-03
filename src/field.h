#ifndef _FIELD_H_
#define _FIELD_H_
#include <boost/smart_ptr.hpp>
#include "member.h"
#include "classmember.h"
using namespace boost;
class Field : public ClassMember
{
public:
	typedef shared_ptr<Field> Pointer;
private:
	Field(MemberItemPtr memberItem);
public:
	static shared_ptr<vector<Pointer> > builds(MemberPtr filed);
};

#endif