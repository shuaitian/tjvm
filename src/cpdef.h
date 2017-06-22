#ifndef _CPDEF_H_
#define _CPDEF_H_
#include <string>
#include <boost/smart_ptr.hpp>
using namespace boost;
using namespace std;

class Class;
class Field;
class ClassLoader;

class ClassRef
{
public:
	string name;
};

class FieldRef
{
public:
	string className;
	string name;
	string descriptor;
};

class MethodRef
{
public:
	string className;
	string name;
	string descriptor;
};

class InterfaceMethodRef
{
public:
	string className;
	string name;
	string descriptor;
};

class NameAndType 
{
public:
	string name;
	string descriptor;
};

class Resolver{
public:
	static shared_ptr<Class> resolveClassRef(shared_ptr<ClassRef> classRef,shared_ptr<Class> sourceClass);
	static shared_ptr<Field> resolveFieldRef(shared_ptr<FieldRef> fieldRef,shared_ptr<Class> sourceClass);
};

#endif	