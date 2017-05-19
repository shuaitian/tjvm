#include "constantpool.h"
#include <stdio.h>

void ConstantPool::add(shared_ptr<ConstantItem> item){
//	printf("add constant item %d\n",item->getTag());
	pool.push_back(item);
}
