#ifndef _CONSTANTPOOL_H_
#define _CONSTANTPOOL_H_
#include <boost/smart_ptr.hpp>
#include <vector>
#include "constantitem.h"
using namespace std;
using namespace boost;

class ConstantPool{
private:
	vector<shared_ptr<ConstantItem> > pool;
public:
	void add(shared_ptr<ConstantItem> item);
	int getSize(){
		return pool.size();
	}
};

#endif
