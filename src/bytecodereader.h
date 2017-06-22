#ifndef _BYTECODEREADER_H_
#define _BYTECODEREADER_H_
#include <boost/smart_ptr.hpp>
#include <vector>
#include "attributeitem.h"
#include "def.h"
using namespace std;
using namespace boost;
class ByteCodeReader;
typedef shared_ptr<ByteCodeReader> ByteCodeReaderPtr;

class ByteCodeReader
{
private:
	j_int pc;
	ByteCodeReader(shared_ptr<vector<u1> > code);
	shared_ptr<vector<u1> > code;
public:
	static ByteCodeReaderPtr build(shared_ptr<vector<u1> > code);
	uint8_t readUint8();
	int8_t readInt8();
	uint16_t readUint16();
	int16_t readInt16();
	int32_t readInt32();
	shared_ptr<vector<int32_t> > readInt32s(int32_t size);
	j_int getPC();
	void setPC(j_int pc);
	void skipPadding();
	bool hasMore();
};

#endif