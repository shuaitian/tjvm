#ifndef _CPDEF_H_
#define _CPDEF_H_
#include <string>

struct ClassRef
{
	string name;
};

struct FieldRef
{
	string className;
	string name;
	string descriptor;
};

struct MethodRef
{
	string className;
	string name;
	string descriptor;
};

struct InterfaceMethodRef
{
	string className;
	string name;
	string descriptor;
};

struct NameAndType
{
	string name;
	string descriptor;
};

#endif