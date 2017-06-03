#ifndef _CLASS_H_
#define _CLASS_H_
#include <boost/smart_ptr.hpp>
#include <string>
#include <vector>
#include <boost/utility/string_ref.hpp>
#include "def.h"
#include "rtconstantpool.h"
#include "field.h"
#include "method.h"
#include "classloader.h"
#include "localvars.h"
#include "classentity.h"
using namespace boost;
using namespace std;
class Class
{
public:
	typedef shared_ptr<Class> Pointer;
private:
	uint16_t accessFlags;
	string name;
	string superClassName;
	shared_ptr<vector<string> > interfaceNames;
	RtConstantPool::Pointer constantPool;
	shared_ptr<vector<Field::Pointer> > fields;
	shared_ptr<vector<Method::Pointer> > methods;
	Pointer superClass;
	shared_ptr<vector<Pointer> > interfaces;
	uint32_t instanceSlotCount;
	uint32_t staticSlotCount;
	shared_ptr<Slot> slots;
	Class();
public:
	static Pointer build(ClassEntityPtr entity);
	bool is(u2 flag);
};

#endif