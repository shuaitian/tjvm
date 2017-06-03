#ifndef _CONSTANTPOOL_H_
#define _CONSTANTPOOL_H_
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include <vector>
#include "constantitem.h"
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
	void display();
};

#endif
