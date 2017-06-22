#ifndef _FIELD_H_
#define _FIELD_H_
#include <boost/smart_ptr.hpp>
#include "member.h"
#include "classmember.h"
class Class;
using namespace boost;
class Field : public ClassMember
{
public:
	typedef shared_ptr<Field> Pointer;
private:
	Field(MemberItemPtr memberItem,shared_ptr<Class> clazz);
	uint32_t slotId;
public:
	static shared_ptr<vector<Pointer> > builds(MemberPtr filed,shared_ptr<Class> clazz);
	void setSlotId(uint32_t slotId);
	uint32_t getSlotId();
	bool isDoubleOrLong();
	bool hasConstValueIndex();
	uint16_t getConstValueIndex();
	bool isAccessibleTo(shared_ptr<Class> clazz);
};

#endif