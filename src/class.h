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
#include "slot.h"
#include "classentity.h"
using namespace boost;
using namespace std;
class Object;

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
	ClassLoader::Pointer classLoader;
	Pointer superClass;
	shared_ptr<vector<Pointer> > interfaces;
	uint32_t instanceSlotCount;
	uint32_t staticSlotCount;
	shared_ptr<vector<Slot> > staticFields;
	Class();
public:
	static Pointer build(ClassEntityPtr entity);
	bool is(u2 flag);
public:
	void setClassLoader(ClassLoader::Pointer loader);
	ClassLoader::Pointer getClassLoader();
	string_ref getName();
	string_ref getSuperClassName();
	void setSuperClass(Pointer super);
	Pointer getSuperClass();
	shared_ptr<vector<string> > getInterfaceNames();
	void setInterfaces(shared_ptr<vector<Pointer> > interfaces);
	shared_ptr<vector<Pointer> > getInterfaces();
	uint32_t getInstanceSlotCount();
	uint32_t getStaticSlotCount();
	void setInstanceSlotCount(uint32_t count);
	void setStaticSlotCount(uint32_t count);
	shared_ptr<vector<Field::Pointer> > getFields();
	shared_ptr<vector<Method::Pointer> > getMethods();
	void setStaticFields(shared_ptr<vector<Slot> > staticFields);
	shared_ptr<vector<Slot> > getStaticFields();
	RtConstantPool::Pointer getConstantPool();
	bool isAccessibleTo(shared_ptr<Class> clazz);
	shared_ptr<Field> lookupField(string_ref name,string_ref descriptor);
	shared_ptr<Object> newObject(shared_ptr<Class> self);
	shared_ptr<Method> getMainMethod();
};

#endif