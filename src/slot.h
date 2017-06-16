#ifndef _SLOT_H_
#define _SLOT_H_
#include <boost/smart_ptr.hpp>
#include "def.h"
using namespace boost;
class Object;
struct Slot
{
	j_int num;
	shared_ptr<Object> ref;
};

#endif