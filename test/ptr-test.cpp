#include <stdio.h>
#include <boost/smart_ptr.hpp>

using namespace boost;

class Object{};

int main(){
	shared_ptr<Object> ptr;
	if(ptr){
		printf("not null\n");
	}
	else
	{
		printf("is null\n");
	}
}
