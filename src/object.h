#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <boost/smart_ptr.hpp>
#include <vector>
#include "slot.h"
using namespace boost;
using namespace std;

class Object;
typedef shared_ptr<Object> ObjectPtr;
class Class;
class Object
{
private:
	shared_ptr<Class> clazz;
	shared_ptr<vector<Slot> > fields;
	Object(shared_ptr<Class> clazz);
public:
	static ObjectPtr nullPtr();
	static shared_ptr<Object> newObject(shared_ptr<Class> clazz);

	shared_ptr<vector<Slot> > getFields();
};

#endif