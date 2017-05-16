#include "bytearray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ByteArray::ByteArray():
	len(0),
	initiaSize(16)
{
	data = new unsigned char[initiaSize];
	if(data == NULL){
		printf("alloc %ld bytes failed in ByteArray::ByteArray()\n",initiaSize);
		exit(-1);
		//TODO throw exception
	}

	total = initiaSize;
}

void ByteArray::append(void* buf,int size){
	int have = total - len;
	if(have < size){
		unsigned long requiredSize = (unsigned long)((len + size)*1.5);
		unsigned char* p = new unsigned char[requiredSize];
		if(p == NULL){
			printf("alloc %ld bytes failed in ByteArray::append(void*,int)\n",requiredSize);
			exit(-1);
			//TODO throw exception
		}
		total *= 2;
		memcpy(p,data,len);
		delete[] data;
		data = p;
	}
	memcpy(data+len,buf,size);
	len += size;
}

unsigned char ByteArray::getByIndex(unsigned long index){
	if(index < 0 || index >= len){
		//throw exception
	}
	return data[index];
}

unsigned char* ByteArray::getData(){
	return data;
}

unsigned char ByteArray::operator[](unsigned long index){
	return getByIndex(index);
}

ByteArray::~ByteArray(){
	delete[] data;
}

void ByteArray::display(){
	printf("byte data:");
	for(unsigned long i=0; i<len; i++){
		if((i % 8) == 0)
			printf("\n");
		printf("%x\t",data[i]);
	}
	printf("\n");
}
