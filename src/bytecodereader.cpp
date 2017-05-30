#include "bytecodereader.h"
#include <string.h>

ByteCodeReader::ByteCodeReader(shared_ptr<CodeAttrItem> cai):
	codeAttrItem(cai),
	pc(0)
{
	this->code = cai->getCode();	
}
ByteCodeReaderPtr ByteCodeReader::build(shared_ptr<CodeAttrItem> cai)
{
	ByteCodeReaderPtr ret(new ByteCodeReader(cai));
	return ret;
}
uint8_t ByteCodeReader::readUint8(){
	u1 ret = (*code)[pc++];
	return static_cast<uint8_t>(ret);
}
int8_t ByteCodeReader::readInt8(){
	uint8_t ret = readUint8();
	return static_cast<int8_t>(ret);
}
uint16_t ByteCodeReader::readUint16(){
	uint8_t high = readUint8();
	uint8_t low = readUint8();
	return (high << 8) | low;
}
int16_t ByteCodeReader::readInt16(){
	uint16_t ret = readUint16();
	return static_cast<int16_t>(ret);
}
int32_t ByteCodeReader::readInt32(){
	int16_t high = readInt16();
	int16_t low = readInt16();
	return (high << 16) | low;
}	

bool ByteCodeReader::hasMore(){
	return ((uint32_t)pc) < (code->size());
}
