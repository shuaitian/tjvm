#include "instructionengine.h"
#include "object.h"
#include <stdio.h>
#include <boost/bind.hpp>
#include <stdio.h>



void InstructionEngine::regist(u1 code,function<void()> handler){
	codeMap[code] = handler;
}

void InstructionEngine::run(u1 code){
	function<void()> handler = codeMap[code];
	if(handler){
		handler();
	}
	else{
		printf("unknow instruction:%x\n",code);
	}
}	

InstructionEnginePtr InstructionEngine::build(FramePtr curFrame,ByteCodeReaderPtr curCodeReader){
	InstructionEnginePtr ret(new InstructionEngine(curFrame,curCodeReader));
	return ret;
}

InstructionEngine::InstructionEngine(FramePtr curFrame,ByteCodeReaderPtr curCodeReader):
	currentFrame(curFrame),
	currentCodeReader(curCodeReader),
	currentLocalVars(currentFrame->getLocalVars()),
	currentOperandStack(currentFrame->getOperandStack())
{
	//const
	regist(nop,bind(&InstructionEngine::nopHandler,this));
	regist(aconst_null,bind(&InstructionEngine::aconstNullHandler,this));
	regist(dconst_0,bind(&InstructionEngine::dconst0Handler,this));
	regist(dconst_1,bind(&InstructionEngine::dconst1Handler,this));
	regist(fconst_0,bind(&InstructionEngine::fconst0Handler,this));
	regist(fconst_1,bind(&InstructionEngine::fconst1Handler,this));
	regist(fconst_2,bind(&InstructionEngine::fconst2Handler,this));
	regist(iconst_m1,bind(&InstructionEngine::iconstM1Handler,this));
	regist(iconst_0,bind(&InstructionEngine::iconst0Handler,this));
	regist(iconst_1,bind(&InstructionEngine::iconst1Handler,this));
	regist(iconst_2,bind(&InstructionEngine::iconst2Handler,this));
	regist(iconst_3,bind(&InstructionEngine::iconst3Handler,this));
	regist(iconst_4,bind(&InstructionEngine::iconst4Handler,this));
	regist(iconst_5,bind(&InstructionEngine::iconst5Handler,this));
	regist(lconst_0,bind(&InstructionEngine::lconst0Handler,this));
	regist(lconst_1,bind(&InstructionEngine::lconst1Handler,this));
	regist(bipush,bind(&InstructionEngine::bipushHandler,this));
	regist(sipush,bind(&InstructionEngine::sipushHandler,this));
	
	//load
	regist(iload,bind(&InstructionEngine::iloadHandler,this));
	regist(iload_0,bind(&InstructionEngine::iload0Handler,this));
	regist(iload_1,bind(&InstructionEngine::iload1Handler,this));
	regist(iload_2,bind(&InstructionEngine::iload2Handler,this));
	regist(iload_3,bind(&InstructionEngine::iload3Handler,this));

	regist(lload,bind(&InstructionEngine::lloadHandler,this));
	regist(lload_0,bind(&InstructionEngine::lload0Handler,this));
	regist(lload_1,bind(&InstructionEngine::lload1Handler,this));
	regist(lload_2,bind(&InstructionEngine::lload2Handler,this));
	regist(lload_3,bind(&InstructionEngine::lload3Handler,this));

	regist(fload,bind(&InstructionEngine::floadHandler,this));
	regist(fload_0,bind(&InstructionEngine::fload0Handler,this));
	regist(fload_1,bind(&InstructionEngine::fload1Handler,this));
	regist(fload_2,bind(&InstructionEngine::fload2Handler,this));
	regist(fload_3,bind(&InstructionEngine::fload3Handler,this));

	regist(dload,bind(&InstructionEngine::dloadHandler,this));
	regist(dload_0,bind(&InstructionEngine::dload0Handler,this));
	regist(dload_1,bind(&InstructionEngine::dload1Handler,this));
	regist(dload_2,bind(&InstructionEngine::dload2Handler,this));
	regist(dload_3,bind(&InstructionEngine::dload3Handler,this));

	regist(aload,bind(&InstructionEngine::aloadHandler,this));
	regist(aload_0,bind(&InstructionEngine::aload0Handler,this));
	regist(aload_1,bind(&InstructionEngine::aload1Handler,this));
	regist(aload_2,bind(&InstructionEngine::aload2Handler,this));
	regist(aload_3,bind(&InstructionEngine::aload3Handler,this));
	
	//store
	regist(istore,bind(&InstructionEngine::istoreHandler,this));
	regist(istore_0,bind(&InstructionEngine::istore0Handler,this));
	regist(istore_1,bind(&InstructionEngine::istore1Handler,this));
	regist(istore_2,bind(&InstructionEngine::istore2Handler,this));
	regist(istore_3,bind(&InstructionEngine::istore3Handler,this));
	
	regist(lstore,bind(&InstructionEngine::lstoreHandler,this));
	regist(lstore_0,bind(&InstructionEngine::lstore0Handler,this));
	regist(lstore_1,bind(&InstructionEngine::lstore1Handler,this));
	regist(lstore_2,bind(&InstructionEngine::lstore2Handler,this));
	regist(lstore_3,bind(&InstructionEngine::lstore3Handler,this));

	regist(fstore,bind(&InstructionEngine::fstoreHandler,this));
	regist(fstore_0,bind(&InstructionEngine::fstore0Handler,this));
	regist(fstore_1,bind(&InstructionEngine::fstore1Handler,this));
	regist(fstore_2,bind(&InstructionEngine::fstore2Handler,this));
	regist(fstore_3,bind(&InstructionEngine::fstore3Handler,this));

	regist(dstore,bind(&InstructionEngine::dstoreHandler,this));
	regist(dstore_0,bind(&InstructionEngine::dstore0Handler,this));
	regist(dstore_1,bind(&InstructionEngine::dstore1Handler,this));
	regist(dstore_2,bind(&InstructionEngine::dstore2Handler,this));
	regist(dstore_3,bind(&InstructionEngine::dstore3Handler,this));

	regist(astore,bind(&InstructionEngine::astoreHandler,this));
	regist(astore_0,bind(&InstructionEngine::astore0Handler,this));
	regist(astore_1,bind(&InstructionEngine::astore1Handler,this));
	regist(astore_2,bind(&InstructionEngine::astore2Handler,this));
	regist(astore_3,bind(&InstructionEngine::astore3Handler,this));
	
	//stack
	regist(pop,bind(&InstructionEngine::popHandler,this));
	regist(pop2,bind(&InstructionEngine::pop2Handler,this));
	regist(tt::dup,bind(&InstructionEngine::dupHandler,this));
	regist(dup_x1,bind(&InstructionEngine::dupX1Handler,this));
	regist(dup_x2,bind(&InstructionEngine::dupX2Handler,this));
	regist(tt::dup2,bind(&InstructionEngine::dup2Handler,this));
	regist(dup2_x1,bind(&InstructionEngine::dup2X1Handler,this));
	regist(dup2_x2,bind(&InstructionEngine::dup2X2Handler,this));
	regist(tt::swap,bind(&InstructionEngine::swapHandler,this));

}



void InstructionEngine::reset(FramePtr currentFrame,ByteCodeReaderPtr currentCodeReader){
	this->currentFrame = currentFrame;
	this->currentCodeReader = currentCodeReader;
}

inline void InstructionEngine::nopHandler(){
	//printf("brance instruciton\n");
}
 
inline void InstructionEngine::aconstNullHandler(){
	currentOperandStack->pushRef(Object::nullPtr());
}
inline void InstructionEngine::dconst0Handler(){
	currentOperandStack->pushDouble(0.0);
}
inline void InstructionEngine::dconst1Handler(){
	currentOperandStack->pushDouble(1.0);
}
inline void InstructionEngine::fconst0Handler(){
	currentOperandStack->pushFloat(0.0f);
}
inline void InstructionEngine::fconst1Handler(){
	currentOperandStack->pushFloat(1.0f);
}
inline void InstructionEngine::fconst2Handler(){
	currentOperandStack->pushFloat(2.0f);
}
inline void InstructionEngine::iconstM1Handler(){
	currentOperandStack->pushInt(-1);
}
inline void InstructionEngine::iconst0Handler(){
	currentOperandStack->pushInt(0);
}
inline void InstructionEngine::iconst1Handler(){
	currentOperandStack->pushInt(1);
}
inline void InstructionEngine::iconst2Handler(){
	currentOperandStack->pushInt(2);
}
inline void InstructionEngine::iconst3Handler(){
	currentOperandStack->pushInt(3);
}
inline void InstructionEngine::iconst4Handler(){
	currentOperandStack->pushInt(4);
}
inline void InstructionEngine::iconst5Handler(){
	currentOperandStack->pushInt(5);
}
inline void InstructionEngine::lconst0Handler(){
	currentOperandStack->pushLong(0);
}
inline void InstructionEngine::lconst1Handler(){
	currentOperandStack->pushLong(1);
}

inline void InstructionEngine::bipushHandler(){
	int8_t val = currentCodeReader->readInt8();
	currentFrame->getOperandStack()->pushInt(static_cast<j_int>(val));
}
inline void InstructionEngine::sipushHandler(){
	int16_t val = currentCodeReader->readInt16();
	currentOperandStack->pushInt(static_cast<j_short>(val));
}
inline void InstructionEngine::iloadHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_int val = currentLocalVars->getInt(index);
	currentOperandStack->pushInt(val);
}
inline void InstructionEngine::iload0Handler(){
	j_int val = currentLocalVars->getInt(0);
	currentOperandStack->pushInt(val);
}
inline void InstructionEngine::iload1Handler(){
	j_int val = currentLocalVars->getInt(1);
	currentOperandStack->pushInt(val);
}
inline void InstructionEngine::iload2Handler(){
	j_int val = currentLocalVars->getInt(2);
	currentOperandStack->pushInt(val);
}
inline void InstructionEngine::iload3Handler(){
	j_int val = currentLocalVars->getInt(3);
	currentOperandStack->pushInt(val);
}

inline void InstructionEngine::lloadHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_long val = currentLocalVars->getLong(index);
	currentOperandStack->pushLong(val);
}
inline void InstructionEngine::lload0Handler(){
	j_long val = currentLocalVars->getLong(0);
	currentOperandStack->pushLong(val);
}
inline void InstructionEngine::lload1Handler(){
	j_long val = currentLocalVars->getLong(1);
	currentOperandStack->pushLong(val);
}
inline void InstructionEngine::lload2Handler(){
	j_long val = currentLocalVars->getLong(2);
	currentOperandStack->pushLong(val);
}
inline void InstructionEngine::lload3Handler(){
	j_long val = currentLocalVars->getLong(3);
	currentOperandStack->pushLong(val);
}

inline void InstructionEngine::floadHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_float val = currentLocalVars->getFloat(index);
	currentOperandStack->pushFloat(val);
}
inline void InstructionEngine::fload0Handler(){
	j_float val = currentLocalVars->getFloat(0);
	currentOperandStack->pushFloat(val);
}
inline void InstructionEngine::fload1Handler(){
	j_float val = currentLocalVars->getFloat(1);
	currentOperandStack->pushFloat(val);
}
inline void InstructionEngine::fload2Handler(){
	j_float val = currentLocalVars->getFloat(2);
	currentOperandStack->pushFloat(val);
}
inline void InstructionEngine::fload3Handler(){
	j_float val = currentLocalVars->getFloat(3);
	currentOperandStack->pushFloat(val);
}

inline void InstructionEngine::dloadHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_double val = currentLocalVars->getDouble(index);
	currentOperandStack->pushDouble(val);
}
inline void InstructionEngine::dload0Handler(){
	j_double val = currentLocalVars->getDouble(0);
	currentOperandStack->pushDouble(val);
}
inline void InstructionEngine::dload1Handler(){
	j_double val = currentLocalVars->getDouble(1);
	currentOperandStack->pushDouble(val);
}
inline void InstructionEngine::dload2Handler(){
	j_double val = currentLocalVars->getDouble(2);
	currentOperandStack->pushDouble(val);
}
inline void InstructionEngine::dload3Handler(){
	j_double val = currentLocalVars->getDouble(3);
	currentOperandStack->pushDouble(val);
}

inline void InstructionEngine::aloadHandler(){
	uint8_t index = currentCodeReader->readUint8();
	ObjectPtr val = currentLocalVars->getRef(index);
	currentOperandStack->pushRef(val);
}
inline void InstructionEngine::aload0Handler(){
	ObjectPtr val = currentLocalVars->getRef(0);
	currentOperandStack->pushRef(val);
}
inline void InstructionEngine::aload1Handler(){
	ObjectPtr val = currentLocalVars->getRef(1);
	currentOperandStack->pushRef(val);
}

inline void InstructionEngine::aload2Handler(){
	ObjectPtr val = currentLocalVars->getRef(2);
	currentOperandStack->pushRef(val);
}
inline void InstructionEngine::aload3Handler(){
	ObjectPtr val = currentLocalVars->getRef(3);
	currentOperandStack->pushRef(val);
}

inline void InstructionEngine::istoreHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_int val = currentOperandStack->popInt();
	currentLocalVars->setInt(index,val);
}
inline void InstructionEngine::istore0Handler(){
	j_int val = currentOperandStack->popInt();
	currentLocalVars->setInt(0,val);
}
inline void InstructionEngine::istore1Handler(){
	j_int val = currentOperandStack->popInt();
	currentLocalVars->setInt(1,val);
}
inline void InstructionEngine::istore2Handler(){
	j_int val = currentOperandStack->popInt();
	currentLocalVars->setInt(2,val);
}
inline void InstructionEngine::istore3Handler(){
	j_int val = currentOperandStack->popInt();
	currentLocalVars->setInt(3,val);
}

inline void InstructionEngine::lstoreHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_long val = currentOperandStack->popLong();
	currentLocalVars->setLong(index,val);
}
inline void InstructionEngine::lstore0Handler(){
	j_long val = currentOperandStack->popLong();
	currentLocalVars->setLong(0,val);
}
inline void InstructionEngine::lstore1Handler(){
	j_long val = currentOperandStack->popLong();
	currentLocalVars->setLong(1,val);
}
inline void InstructionEngine::lstore2Handler(){
	j_long val = currentOperandStack->popLong();
	currentLocalVars->setLong(2,val);
}
inline void InstructionEngine::lstore3Handler(){
	j_long val = currentOperandStack->popLong();
	currentLocalVars->setLong(3,val);
}

inline void InstructionEngine::fstoreHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_float val = currentOperandStack->popFloat();
	currentLocalVars->setFloat(index,val);
}
inline void InstructionEngine::fstore0Handler(){
	j_float val = currentOperandStack->popFloat();
	currentLocalVars->setFloat(0,val);
}
inline void InstructionEngine::fstore1Handler(){
	j_float val = currentOperandStack->popFloat();
	currentLocalVars->setFloat(1,val);
}
inline void InstructionEngine::fstore2Handler(){
	j_float val = currentOperandStack->popFloat();
	currentLocalVars->setFloat(2,val);
}
inline void InstructionEngine::fstore3Handler(){
	j_float val = currentOperandStack->popFloat();
	currentLocalVars->setFloat(3,val);
}

inline void InstructionEngine::dstoreHandler(){
	uint8_t index = currentCodeReader->readUint8();
	j_double val = currentOperandStack->popDouble();
	currentLocalVars->setDouble(index,val);
}
inline void InstructionEngine::dstore0Handler(){
	j_double val = currentOperandStack->popDouble();
	currentLocalVars->setDouble(0,val);
}
inline void InstructionEngine::dstore1Handler(){
	j_double val = currentOperandStack->popDouble();
	currentLocalVars->setDouble(1,val);
}
inline void InstructionEngine::dstore2Handler(){
	j_double val = currentOperandStack->popDouble();
	currentLocalVars->setDouble(2,val);
}
inline void InstructionEngine::dstore3Handler(){
	j_double val = currentOperandStack->popDouble();
	currentLocalVars->setDouble(3,val);
}
	
inline void InstructionEngine::astoreHandler(){
	uint8_t index = currentCodeReader->readUint8();
	ObjectPtr val = currentOperandStack->popRef();
	currentLocalVars->setRef(index,val);
}
inline void InstructionEngine::astore0Handler(){
	ObjectPtr val = currentOperandStack->popRef();
	currentLocalVars->setRef(0,val);
}	

inline void InstructionEngine::astore1Handler(){
	ObjectPtr val = currentOperandStack->popRef();
	currentLocalVars->setRef(1,val);
}

inline void InstructionEngine::astore2Handler(){
	ObjectPtr val = currentOperandStack->popRef();
	currentLocalVars->setRef(2,val);
}

inline void InstructionEngine::astore3Handler(){
	ObjectPtr val = currentOperandStack->popRef();
	currentLocalVars->setRef(3,val);
}

inline void InstructionEngine::popHandler(){
	currentOperandStack->popSlot();
}
inline void InstructionEngine::pop2Handler(){
	currentOperandStack->popSlot();
	currentOperandStack->popSlot();
}

inline void InstructionEngine::dupHandler(){
	Slot slot = currentOperandStack->popSlot();
	currentOperandStack->pushSlot(slot);
	currentOperandStack->pushSlot(slot);
}
inline void InstructionEngine::dupX1Handler(){
	Slot slot1 = currentOperandStack->popSlot();
	Slot slot2 = currentOperandStack->popSlot();
	currentOperandStack->pushSlot(slot1);
	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
}
inline void InstructionEngine::dupX2Handler(){
	Slot slot1 = currentOperandStack->popSlot();
	Slot slot2 = currentOperandStack->popSlot();
	Slot slot3 = currentOperandStack->popSlot();
	currentOperandStack->pushSlot(slot1);
	currentOperandStack->pushSlot(slot3);
	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
}
inline void InstructionEngine::dup2Handler(){
	Slot slot1 = currentOperandStack->popSlot();
	Slot slot2 = currentOperandStack->popSlot();
	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
}
inline void InstructionEngine::dup2X1Handler(){
	Slot slot1 = currentOperandStack->popSlot();
	Slot slot2 = currentOperandStack->popSlot();
	Slot slot3 = currentOperandStack->popSlot();

	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
	currentOperandStack->pushSlot(slot3);
	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
}
inline void InstructionEngine::dup2X2Handler(){
	Slot slot1 = currentOperandStack->popSlot();
	Slot slot2 = currentOperandStack->popSlot();
	Slot slot3 = currentOperandStack->popSlot();
	Slot slot4 = currentOperandStack->popSlot();

	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
	currentOperandStack->pushSlot(slot4);
	currentOperandStack->pushSlot(slot3);
	currentOperandStack->pushSlot(slot2);
	currentOperandStack->pushSlot(slot1);
}

inline void InstructionEngine::swapHandler(){
	Slot slot1 = currentOperandStack->popSlot();
	Slot slot2 = currentOperandStack->popSlot();
	currentOperandStack->pushSlot(slot1);
	currentOperandStack->pushSlot(slot2);
}		

