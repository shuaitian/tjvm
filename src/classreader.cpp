#include "classreader.h"
#include <string.h>

ClassReader::ClassReader(shared_ptr<ByteArray> br):
	data(br),
	index(0)
{
	
}

u1 ClassReader::readU1(){
	return static_cast<u1>((*data)[index++]);
}

u2 ClassReader::readU2(){
	u1 tail = readU1();
	u1 head = readU1();
	u2 ret;
	u1* p = (u1*)&ret;
	memcpy(p,&head,sizeof(head));
	memcpy(p+1,&tail,sizeof(tail));
	return ret;
}

u4 ClassReader::readU4(){
	u2 tail = readU2();
	u2 head = readU2();
	u4 ret;
	u2* p = (u2*)&ret;
	memcpy(p,&head,sizeof(head));
	memcpy(p+1,&tail,sizeof(tail));
	return ret;
}

u8 ClassReader::readU8(){
	u4 tail = readU4();
	u4 head = readU4();
	u8 ret;
	u4* p = (u4*)&ret;
	memcpy(p,&head,sizeof(head));
	memcpy(p+1,&tail,sizeof(tail));
	return ret;
}

vector<u2> ClassReader::readU2Table(){
	vector<u2> ret;
	u2 length = readU2();
	for(u2 i=0;i<length;i++){
		ret.push_back(readU2());
	}
	return ret;
}

shared_ptr<ByteArray> ClassReader::readBytes(unsigned long length){
	shared_ptr<ByteArray> ret;
	if(length > 0){
		ret = make_shared<ByteArray>();
		for(unsigned long i=0; i<length;i++){
			unsigned char byte = (*data)[index++];
			ret->append(&byte,sizeof(unsigned char));
		}
	}
	return ret;
}


