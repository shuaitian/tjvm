#ifndef _BYTEARRAY_H_
#define _BYTEARRAY_H_
#include <boost/smart_ptr.hpp>
class ByteArray;
typedef boost::shared_ptr<ByteArray> ByteArrayPtr;
class ByteArray{
private:
	unsigned long len;
	unsigned long total;
	unsigned char *data;
	unsigned long initiaSize;
public:
	ByteArray();
	void append(void* buf,int size);
	unsigned char* getData();
	unsigned char getByIndex(unsigned long index);
	unsigned long getCurrentSize(){
		return len;
	}
	unsigned char operator[](unsigned long index);
	void display();
	~ByteArray();

};

#endif
