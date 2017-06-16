#ifndef _LOCALVARS_H_
#define _LOCALVARS_H_
#include <boost/smart_ptr.hpp>
#include "def.h"
#include "object.h"
#include "slot.h"	
using namespace boost;

class LocalVars;
typedef shared_ptr<LocalVars> LocalVarsPtr;

//struct Slot
//{
//	j_int num;
//	ObjectPtr ref;
//};

class LocalVars
{
private:
	LocalVars(uint32_t maxLocals);
	Slot *slots;
	uint32_t size;
	void printErrorExit(const char* str);
public:
	~LocalVars();
	Slot& operator[](uint32_t index);
	static LocalVarsPtr build(uint32_t maxLocals);

	void setInt(uint32_t index,j_int val);
	j_int getInt(uint32_t index);
	void setFloat(uint32_t index,j_float val);
	j_float getFloat(uint32_t index);
	void setLong(uint32_t index,j_long val);
	j_long getLong(uint32_t index);

	void setDouble(uint32_t index,j_double val);
	j_double getDouble(uint32_t index);

	void setRef(uint32_t index,ObjectPtr ref);
	ObjectPtr getRef(uint32_t index);

	void display();
};

#endif