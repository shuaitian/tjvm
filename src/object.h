#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <boost/smart_ptr.hpp>
using namespace boost;

class Object;
typedef shared_ptr<Object> ObjectPtr;
class Object
{
};

#endif