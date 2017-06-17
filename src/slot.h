#ifndef _SLOT_H_
#define _SLOT_H_
#include <boost/smart_ptr.hpp>
#include <vector>
#include "def.h"
using namespace boost;
using namespace std;
class Object;
struct Slot
{
	j_int num;
	shared_ptr<Object> ref;
};

class SlotUtil
{
private:
	static void printErrorExit(const char* str);
public:
	static void setInt(shared_ptr<vector<Slot> > slots,uint32_t index,j_int val);
	static j_int getInt(shared_ptr<vector<Slot> > slots,uint32_t index);
	static void setFloat(shared_ptr<vector<Slot> > slots,uint32_t index,j_float val);
	static j_float getFloat(shared_ptr<vector<Slot> > slots,uint32_t index);
	static void setLong(shared_ptr<vector<Slot> > slots,uint32_t index,j_long val);
	static j_long getLong(shared_ptr<vector<Slot> > slots,uint32_t index);

	static void setDouble(shared_ptr<vector<Slot> > slots,uint32_t index,j_double val);
	static j_double getDouble(shared_ptr<vector<Slot> > slots,uint32_t index);

	static void setRef(shared_ptr<vector<Slot> > slots,uint32_t index,shared_ptr<Object> ref);
	static shared_ptr<Object> getRef(shared_ptr<vector<Slot> > slots,uint32_t index);
};

#endif