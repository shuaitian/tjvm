#ifndef _RTCONSTANTPOOL_H_
#define _RTCONSTANTPOOL_H_
#include <boost/smart_ptr.hpp>
#include "constantpool.h"
using namespace boost;
class RtConstantPool
{
public:
	typedef shared_ptr<RtConstantPool> Pointer;
public:
	static Pointer build(ConstantPoolPtr pool);
};

#endif