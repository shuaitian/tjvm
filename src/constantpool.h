#ifndef _CONSTANTPOOL_H_
#define _CONSTANTPOOL_H_
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include <vector>
#include "constantitem.h"
#include "cpdef.h"
using namespace std;
using namespace boost;
class ConstantPool;
typedef shared_ptr<ConstantPool> ConstantPoolPtr;



class ConstantPool{
private:
	vector<shared_ptr<ConstantItem> > pool;
	shared_ptr<ConstantItem> readConstItemByOwnIndex(u2 index);
public:
	void add(shared_ptr<ConstantItem> item);
	int getSize(){
		return pool.size();
	}
	string_ref readUTF8ByIndex(u2 index);
	string_ref readClassByIndex(u2 index);
	int32_t readIntegerByIndex(u2 index);
	int64_t readLongByIndex(u2 index);
	float readFloatByIndex(u2 index);
	double readDoubleByIndex(u2 index);
	shared_ptr<ClassRef> readClassRefByIndex(u2 index);
	shared_ptr<FieldRef> readFieldRefByIndex(u2 index);
	shared_ptr<MethodRef> readMethodRefByIndex(u2 index);
	shared_ptr<InterfaceMethodRef> readInterfaceMethodRefByIndex(u2 index);
	shared_ptr<NameAndType> readNameAndTypeByIndex(u2 index);
	void display();
};

#endif
