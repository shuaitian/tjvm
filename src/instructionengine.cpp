#include "instructionengine.h"
#include "object.h"
#include <stdio.h>
#include <boost/bind.hpp>
#include <stdio.h>
#include <math.h>
#include "rtconstantpool.h"
#include "class.h"



void InstructionEngine::regist(u1 code,function<void()> handler){
	codeMap[code] = handler;
}

void InstructionEngine::run(u1 code){
	function<void()> handler = codeMap[code];
	if(handler){
		pc = currentCodeReader->getPC() - 1; //保存当前指令的pc
		handler();
		currentFrame->getThreadPrivate()->setPC(currentCodeReader->getPC()); //设置下一条指令的pc
	}
	else{
		printf("unknow instruction:%x\n",code);
		currentFrame->display();
		exit(-1);
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
	regist(tt::swap_,bind(&InstructionEngine::swapHandler,this));

	//math
	regist(tt::irem,bind(&InstructionEngine::iremHandler,this));
	regist(tt::lrem,bind(&InstructionEngine::lremHandler,this));
	regist(tt::frem,bind(&InstructionEngine::fremHandler,this));
	regist(tt::drem,bind(&InstructionEngine::dremHandler,this));

	regist(tt::iadd,bind(&InstructionEngine::iaddHandler,this));
	regist(tt::ladd,bind(&InstructionEngine::laddHandler,this));
	regist(tt::fadd,bind(&InstructionEngine::faddHandler,this));
	regist(tt::dadd,bind(&InstructionEngine::daddHandler,this));

	regist(tt::isub,bind(&InstructionEngine::isubHandler,this));
	regist(tt::lsub,bind(&InstructionEngine::lsubHandler,this));
	regist(tt::fsub,bind(&InstructionEngine::fsubHandler,this));
	regist(tt::dsub,bind(&InstructionEngine::dsubHandler,this));

	regist(tt::imul,bind(&InstructionEngine::imulHandler,this));
	regist(tt::lmul,bind(&InstructionEngine::lmulHandler,this));
	regist(tt::fmul,bind(&InstructionEngine::fmulHandler,this));
	regist(tt::dmul,bind(&InstructionEngine::dmulHandler,this));

	regist(tt::idiv,bind(&InstructionEngine::idivHandler,this));
	regist(tt::ldiv,bind(&InstructionEngine::ldivHandler,this));
	regist(tt::fdiv,bind(&InstructionEngine::fdivHandler,this));
	regist(tt::ddiv,bind(&InstructionEngine::ddivHandler,this));

	regist(tt::ineg,bind(&InstructionEngine::inegHandler,this));
	regist(tt::lneg,bind(&InstructionEngine::lnegHandler,this));
	regist(tt::fneg,bind(&InstructionEngine::fnegHandler,this));
	regist(tt::dneg,bind(&InstructionEngine::dnegHandler,this));

	regist(tt::ishl,bind(&InstructionEngine::ishlHandler,this));
	regist(tt::lshl,bind(&InstructionEngine::lshlHandler,this));
	regist(tt::ishr,bind(&InstructionEngine::ishrHandler,this));
	regist(tt::lshr,bind(&InstructionEngine::lshrHandler,this));
	regist(tt::iushr,bind(&InstructionEngine::iushrHandler,this));
	regist(tt::lushr,bind(&InstructionEngine::lushrHandler,this));

	regist(tt::iand,bind(&InstructionEngine::iandHandler,this));
	regist(tt::land,bind(&InstructionEngine::landHandler,this));
	regist(tt::ior,bind(&InstructionEngine::iorHandler,this));
	regist(tt::lor,bind(&InstructionEngine::lorHandler,this));
	regist(tt::ixor,bind(&InstructionEngine::ixorHandler,this));
	regist(tt::lxor,bind(&InstructionEngine::lxorHandler,this));
	regist(tt::iinc,bind(&InstructionEngine::iincHandler,this));

	//conversion
	regist(tt::i2l,bind(&InstructionEngine::i2lHandler,this));
	regist(tt::i2f,bind(&InstructionEngine::i2fHandler,this));
	regist(tt::i2d,bind(&InstructionEngine::i2dHandler,this));
	regist(tt::l2i,bind(&InstructionEngine::l2iHandler,this));
	regist(tt::l2f,bind(&InstructionEngine::l2fHandler,this));
	regist(tt::l2d,bind(&InstructionEngine::l2dHandler,this));
	regist(tt::f2i,bind(&InstructionEngine::f2iHandler,this));
	regist(tt::f2l,bind(&InstructionEngine::f2lHandler,this));
	regist(tt::f2d,bind(&InstructionEngine::f2dHandler,this));
	regist(tt::d2i,bind(&InstructionEngine::d2iHandler,this));
	regist(tt::d2l,bind(&InstructionEngine::d2lHandler,this));
	regist(tt::d2f,bind(&InstructionEngine::d2fHandler,this));
	regist(tt::i2b,bind(&InstructionEngine::i2bHandler,this));
	regist(tt::i2c,bind(&InstructionEngine::i2cHandler,this));
	regist(tt::i2s,bind(&InstructionEngine::i2sHandler,this));

	//comparison
	regist(tt::lcmp,bind(&InstructionEngine::lcmpHandler,this));
	regist(tt::fcmpl,bind(&InstructionEngine::fcmplHandler,this));
	regist(tt::fcmpg,bind(&InstructionEngine::fcmpgHandler,this));
	regist(tt::dcmpl,bind(&InstructionEngine::dcmplHandler,this));
	regist(tt::dcmpg,bind(&InstructionEngine::dcmpgHandler,this));
	regist(tt::ifeq,bind(&InstructionEngine::ifeqHandler,this));
	regist(tt::ifne,bind(&InstructionEngine::ifneHandler,this));
	regist(tt::iflt,bind(&InstructionEngine::ifltHandler,this));
	regist(tt::ifge,bind(&InstructionEngine::ifgeHandler,this));
	regist(tt::ifgt,bind(&InstructionEngine::ifgtHandler,this));
	regist(tt::ifle,bind(&InstructionEngine::ifleHandler,this));
	regist(tt::if_icmpeq,bind(&InstructionEngine::ifIcmpeqHandler,this));
	regist(tt::if_icmpne,bind(&InstructionEngine::ifIcmpneHandler,this));
	regist(tt::if_icmplt,bind(&InstructionEngine::ifIcmpltHandler,this));
	regist(tt::if_icmpge,bind(&InstructionEngine::ifIcmpgeHandler,this));
	regist(tt::if_icmpgt,bind(&InstructionEngine::ifIcmpgtHandler,this));
	regist(tt::if_icmple,bind(&InstructionEngine::ifIcmpleHandler,this));
	regist(tt::if_acmpeq,bind(&InstructionEngine::ifAcmpeqHandler,this));
	regist(tt::if_acmpne,bind(&InstructionEngine::ifAcmpneHandler,this));

	//control
	regist(tt::goto_,bind(&InstructionEngine::gotoHandler,this));
	regist(tt::jsr,bind(&InstructionEngine::jsrHandler,this));
	regist(tt::ret,bind(&InstructionEngine::retHandler,this));
	regist(tt::tableswitch,bind(&InstructionEngine::tableswitchHandler,this));
	regist(tt::lookupswitch,bind(&InstructionEngine::lookupswitchHandler,this));
	//regist(tt::ireturn,bind(&InstructionEngine::ireturnHandler,this));
	//regist(tt::lreturn,bind(&InstructionEngine::lreturnHandler,this));
	//regist(tt::freturn,bind(&InstructionEngine::freturnHandler,this));
	//regist(tt::dreturn,bind(&InstructionEngine::dreturnHandler,this));
	//regist(tt::areturn,bind(&InstructionEngine::areturnHandler,this));
	//regist(tt::return_,bind(&InstructionEngine::returnHandler,this));
	
	//references
	regist(tt::new_,bind(&InstructionEngine::newHandler,this));

	//extended
	regist(tt::ifnull,bind(&InstructionEngine::ifnullHandler,this));
	regist(tt::ifnonnull,bind(&InstructionEngine::ifnonnullHandler,this));


}

inline void InstructionEngine::branch(j_int offset){
	j_int res = pc + offset ;
	//printf("after branch[%d%d]:%d\n",pc,offset,res);
	currentCodeReader->setPC(res);
}

inline j_int InstructionEngine::readOffset16(){
	int16_t val = currentCodeReader->readInt16();
	return static_cast<j_int>(val);
}



void InstructionEngine::reset(FramePtr currentFrame,ByteCodeReaderPtr currentCodeReader){
	this->currentFrame = currentFrame;
	this->currentCodeReader = currentCodeReader;
}

inline void InstructionEngine::newHandler(){
	shared_ptr<Class> curClass = currentFrame->getMethod()->getClass();
	shared_ptr<RtConstantPool> cp = curClass->getConstantPool();
	uint16_t index = currentCodeReader->readUint16();
	shared_ptr<ClassRef> classRef = cp->getClassRef(index);
	shared_ptr<Class> targetClass = Resolver::resolveClassRef(classRef,curClass);
	if(targetClass->is(ACC_INTERFACE) || targetClass->is(ACC_ABSTRACT)){
		//TODO throw exception
		printf("error InstantiationError\n");
		exit(0);
	}

	shared_ptr<Object> ref = targetClass->newObject(targetClass);
	currentOperandStack->pushRef(ref);
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

inline void InstructionEngine::iremHandler(){
	j_int v2 = currentOperandStack->popInt();
	j_int v1 = currentOperandStack->popInt();
	if(v2 == 0){
		//TODO throw exception
		printf("irem error,v2 == 0\n");
		exit(-1);
	}
	j_int result = v1 % v2;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::lremHandler(){
	j_long v2 = currentOperandStack->popLong();
	j_long v1 = currentOperandStack->popLong();
	if(v2 == 0){
		//TODO throw exception
		printf("lrem error,v2 == 0\n");
		exit(-1);
	}
	j_long result = v1 % v2;
	currentOperandStack->pushLong(result);
}
inline void InstructionEngine::fremHandler(){
	j_float v2 = currentOperandStack->popFloat();
	j_float v1 = currentOperandStack->popFloat();
	j_float result = fmod(v1,v2);
	currentOperandStack->pushFloat(result);
}
inline void InstructionEngine::dremHandler(){
	j_double v2 = currentOperandStack->popDouble();
	j_double v1 = currentOperandStack->popDouble();
	j_double result = fmod(v1,v2);
	currentOperandStack->pushDouble(result);
}

inline void InstructionEngine::iaddHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	j_int result = v1 + v2;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::laddHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	j_long result = v1 + v2;
	currentOperandStack->pushLong(result);
}
inline void InstructionEngine::faddHandler(){
	j_float v1 = currentOperandStack->popFloat();
	j_float v2 = currentOperandStack->popFloat();
	j_float result = v1 + v2;
	currentOperandStack->pushFloat(result);
}
inline void InstructionEngine::daddHandler(){
	j_double v1 = currentOperandStack->popDouble();
	j_double v2 = currentOperandStack->popDouble();
	j_double result = v1 + v2;
	currentOperandStack->pushDouble(result);
}

inline void InstructionEngine::isubHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	j_int result = v2 - v1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::lsubHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	j_long result = v2 - v1;
	currentOperandStack->pushLong(result);
}
inline void InstructionEngine::fsubHandler(){
	j_float v1 = currentOperandStack->popFloat();
	j_float v2 = currentOperandStack->popFloat();
	j_float result = v2 - v1;
	currentOperandStack->pushFloat(result);
}
inline void InstructionEngine::dsubHandler(){
	j_double v1 = currentOperandStack->popDouble();
	j_double v2 = currentOperandStack->popDouble();
	j_double result = v2 - v1;
	currentOperandStack->pushDouble(result);
}

inline void InstructionEngine::imulHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	j_int result = v2 * v1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::lmulHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	j_long result = v2 * v1;
	currentOperandStack->pushLong(result);
}
inline void InstructionEngine::fmulHandler(){
	j_float v1 = currentOperandStack->popFloat();
	j_float v2 = currentOperandStack->popFloat();
	j_float result = v2 * v1;
	currentOperandStack->pushFloat(result);
}
inline void InstructionEngine::dmulHandler(){
	j_double v1 = currentOperandStack->popDouble();
	j_double v2 = currentOperandStack->popDouble();
	j_double result = v2 * v1;
	currentOperandStack->pushDouble(result);
}

inline void InstructionEngine::idivHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	if(v2 == 0){
		//TODO throw exception
		printf("idiv error ,v2 == 0\n");
		exit(-1);
	}
	j_int result = v2 / v1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::ldivHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	if(v2 == 0){
		//TODO throw exception
		printf("ldiv error ,v2 == 0\n");
		exit(-1);
	}
	j_long result = v2 / v1;
	currentOperandStack->pushLong(result);
}
inline void InstructionEngine::fdivHandler(){
	j_float v1 = currentOperandStack->popFloat();
	j_float v2 = currentOperandStack->popFloat();
	j_float result = v2 / v1;
	currentOperandStack->pushFloat(result);
}
inline void InstructionEngine::ddivHandler(){
	j_double v1 = currentOperandStack->popDouble();
	j_double v2 = currentOperandStack->popDouble();
	j_double result = v2 / v1;
	currentOperandStack->pushDouble(result);
}

inline void InstructionEngine::inegHandler(){
	j_int val = currentOperandStack->popInt();
	currentOperandStack->pushInt(-val);
}
inline void InstructionEngine::lnegHandler(){
	j_long val = currentOperandStack->popLong();
	currentOperandStack->pushLong(-val);
}
inline void InstructionEngine::fnegHandler(){
	j_float val = currentOperandStack->popFloat();
	currentOperandStack->pushFloat(-val);
}
inline void InstructionEngine::dnegHandler(){
	j_double val = currentOperandStack->popDouble();
	currentOperandStack->pushDouble(-val);
}

inline void InstructionEngine::ishlHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	currentOperandStack->pushInt(v2 << v1);
}
inline void InstructionEngine::lshlHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_long v2 = currentOperandStack->popLong();
	currentOperandStack->pushLong(v2 << v1);
}
inline void InstructionEngine::ishrHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	currentOperandStack->pushInt(v2 >> v1);
}
inline void InstructionEngine::lshrHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_long v2 = currentOperandStack->popLong();
	currentOperandStack->pushLong(v2 >> v1);
}
inline void InstructionEngine::iushrHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	j_int result = static_cast<j_int>(static_cast<uint32_t>(v2) >> v1);
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::lushrHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_long v2 = currentOperandStack->popLong();
	j_int result = static_cast<j_int>(static_cast<uint64_t>(v2) >> v1);
	currentOperandStack->pushLong(result);
}

inline void InstructionEngine::iandHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	currentOperandStack->pushInt(v2 & v1);
}
inline void InstructionEngine::landHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	currentOperandStack->pushLong(v2 & v1);
}
inline void InstructionEngine::iorHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	currentOperandStack->pushInt(v2 | v1);
}
inline void InstructionEngine::lorHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	currentOperandStack->pushLong(v2 | v1);
}
inline void InstructionEngine::ixorHandler(){
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	currentOperandStack->pushInt(v2 ^ v1);
}
inline void InstructionEngine::lxorHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	currentOperandStack->pushLong(v2 ^ v1);
}
inline void InstructionEngine::iincHandler(){
	uint8_t index = currentCodeReader->readUint8();
	int32_t constVal = static_cast<int32_t>(currentCodeReader->readInt8());
	j_int val = currentLocalVars->getInt(index);
	val += constVal;
	currentLocalVars->setInt(index,val);
}

inline void InstructionEngine::i2lHandler(){
	j_int val = currentOperandStack->popInt();
	currentOperandStack->pushLong(static_cast<j_long>(val));
}
inline void InstructionEngine::i2fHandler(){
	j_int val = currentOperandStack->popInt();
	currentOperandStack->pushFloat(static_cast<j_float>(val));
}
inline void InstructionEngine::i2dHandler(){
	j_int val = currentOperandStack->popInt();
	currentOperandStack->pushDouble(static_cast<j_double>(val));
}
inline void InstructionEngine::l2iHandler(){
	j_long val = currentOperandStack->popLong();
	currentOperandStack->pushInt(static_cast<j_int>(val));
}
inline void InstructionEngine::l2fHandler(){
	j_long val = currentOperandStack->popLong();
	currentOperandStack->pushFloat(static_cast<j_float>(val));
}
inline void InstructionEngine::l2dHandler(){
	j_long val = currentOperandStack->popLong();
	currentOperandStack->pushDouble(static_cast<j_double>(val));
}
inline void InstructionEngine::f2iHandler(){
	j_float val = currentOperandStack->popFloat();
	currentOperandStack->pushInt(static_cast<j_int>(val));
}
inline void InstructionEngine::f2lHandler(){
	j_float val = currentOperandStack->popFloat();
	currentOperandStack->pushLong(static_cast<j_long>(val));
}
inline void InstructionEngine::f2dHandler(){
	j_float val = currentOperandStack->popFloat();
	currentOperandStack->pushDouble(static_cast<j_double>(val));
}
inline void InstructionEngine::d2iHandler(){
	j_double val = currentOperandStack->popDouble();
	currentOperandStack->pushInt(static_cast<j_int>(val));
}
inline void InstructionEngine::d2lHandler(){
	j_double val = currentOperandStack->popDouble();
	currentOperandStack->pushLong(static_cast<j_long>(val));
}
inline void InstructionEngine::d2fHandler(){
	j_double val = currentOperandStack->popDouble();
	currentOperandStack->pushFloat(static_cast<j_float>(val));
}
inline void InstructionEngine::i2bHandler(){
	j_int val = currentOperandStack->popInt();
	currentOperandStack->pushInt(static_cast<j_int>(static_cast<j_byte>(val)));
}
inline void InstructionEngine::i2cHandler(){
	j_int val = currentOperandStack->popInt();
	currentOperandStack->pushInt(static_cast<j_int>(static_cast<j_char>(val)));
}
inline void InstructionEngine::i2sHandler(){
	j_int val = currentOperandStack->popInt();
	currentOperandStack->pushInt(static_cast<j_int>(static_cast<j_short>(val)));
}

inline void InstructionEngine::lcmpHandler(){
	j_long v1 = currentOperandStack->popLong();
	j_long v2 = currentOperandStack->popLong();
	j_int result = 0;
	if(v2 > v1)
		result = 1;
	else if (v2 == v1)
		result = 0;
	else
		result = -1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::fcmplHandler(){
	j_float v1 = currentOperandStack->popFloat();
	j_float v2 = currentOperandStack->popFloat();
	j_int result = 0;
	if(v2 > v1)
		result = 1;
	else if (v2 == v1)
		result = 0;
	else if (v2 < v1)
		result = -1;
	if(isnan(v1) || isnan(v2))
		result = -1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::fcmpgHandler(){
	j_float v1 = currentOperandStack->popFloat();
	j_float v2 = currentOperandStack->popFloat();
	j_int result = 0;
	if(v2 > v1)
		result = 1;
	else if (v2 == v1)
		result = 0;
	else if (v2 < v1)
		result = -1;
	if(isnan(v1) || isnan(v2))
		result = 1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::dcmplHandler(){
	j_double v1 = currentOperandStack->popDouble();
	j_double v2 = currentOperandStack->popDouble();
	j_int result = 0;
	if(v2 > v1)
		result = 1;
	else if (v2 == v1)
		result = 0;
	else if (v2 < v1)
		result = -1;
	if(isnan(v1) || isnan(v2))
		result = -1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::dcmpgHandler(){
	j_double v1 = currentOperandStack->popDouble();
	j_double v2 = currentOperandStack->popDouble();
	j_int result = 0;
	if(v2 > v1)
		result = 1;
	else if (v2 == v1)
		result = 0;
	else if (v2 < v1)
		result = -1;
	if(isnan(v1) || isnan(v2))
		result = 1;
	currentOperandStack->pushInt(result);
}
inline void InstructionEngine::ifeqHandler(){
	j_int offset = readOffset16();
	j_int val = currentOperandStack->popInt();
	if(val == 0)
		branch(offset);
}
inline void InstructionEngine::ifneHandler(){
	j_int offset = readOffset16();
	j_int val = currentOperandStack->popInt();
	if(val != 0)
		branch(offset);
}
inline void InstructionEngine::ifltHandler(){
	j_int offset = readOffset16();
	j_int val = currentOperandStack->popInt();
	if(val < 0)
		branch(offset);
}
inline void InstructionEngine::ifgeHandler(){
	j_int offset = readOffset16();
	j_int val = currentOperandStack->popInt();
	if(val >= 0)
		branch(offset);
}
inline void InstructionEngine::ifgtHandler(){
	j_int offset = readOffset16();
	j_int val = currentOperandStack->popInt();
	if(val > 0)
		branch(offset);
}
inline void InstructionEngine::ifleHandler(){
	j_int offset = readOffset16();
	j_int val = currentOperandStack->popInt();
	if(val <= 0)
		branch(offset);
}
inline void InstructionEngine::ifIcmpeqHandler(){
	j_int offset = readOffset16();
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	if(v2 == v1)
		branch(offset);
}
inline void InstructionEngine::ifIcmpneHandler(){
	j_int offset = readOffset16();
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	if(v2 != v1)
		branch(offset);
}
inline void InstructionEngine::ifIcmpltHandler(){
	j_int offset = readOffset16();
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	if(v2 < v1)
		branch(offset);
}
inline void InstructionEngine::ifIcmpgeHandler(){
	j_int offset = readOffset16();
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	if(v2 >= v1)
		branch(offset);
}
inline void InstructionEngine::ifIcmpgtHandler(){
	j_int offset = readOffset16();
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	if(v2 > v1)
		branch(offset);
}
inline void InstructionEngine::ifIcmpleHandler(){
	j_int offset = readOffset16();
	j_int v1 = currentOperandStack->popInt();
	j_int v2 = currentOperandStack->popInt();
	if(v2 <= v1)
		branch(offset);
}
inline void InstructionEngine::ifAcmpeqHandler(){
	j_int offset = readOffset16();
	ObjectPtr v1 = currentOperandStack->popRef();
	ObjectPtr v2 = currentOperandStack->popRef();
	if(v1 == v2)
		branch(offset);
}
inline void InstructionEngine::ifAcmpneHandler(){
	j_int offset = readOffset16();
	ObjectPtr v1 = currentOperandStack->popRef();
	ObjectPtr v2 = currentOperandStack->popRef();
	if(v1 != v2)
		branch(offset);
}

inline void InstructionEngine::gotoHandler(){
	j_int offset = readOffset16();
	branch(offset);
}
//TODO
inline void InstructionEngine::jsrHandler(){}
inline void InstructionEngine::retHandler(){}

inline void InstructionEngine::tableswitchHandler(){
	currentCodeReader->skipPadding();
	int32_t defaultOffset = currentCodeReader->readInt32();
	int32_t low = currentCodeReader->readInt32();
	int32_t high = currentCodeReader->readInt32();
	int32_t jumpOffsetsCount = high -low + 1;
	shared_ptr<vector<int32_t> > jumpOffsets = currentCodeReader->readInt32s(jumpOffsetsCount);

	j_int index = currentOperandStack->popInt();
	j_int offset;
	if (index >= low && index <= high)
		offset = static_cast<j_int>((*jumpOffsets)[index - low]);
	else
		offset = static_cast<j_int>(defaultOffset);
	branch(offset);
}
inline void InstructionEngine::lookupswitchHandler(){
	currentCodeReader->skipPadding();
	int32_t defaultOffset = currentCodeReader->readInt32();
	int32_t npairs = currentCodeReader->readInt32();
	shared_ptr<vector<int32_t> > matchOffsets = currentCodeReader->readInt32s(npairs * 2);

	j_int key = currentOperandStack->popInt();
	for(int32_t i=0; i < npairs*2; i+=2){
		if((*matchOffsets)[i] == key){
			j_int offset = (*matchOffsets)[i+1];
			branch(offset);
			return;
		}
	}

	branch(defaultOffset);
}
inline void InstructionEngine::ireturnHandler(){}
inline void InstructionEngine::lreturnHandler(){}
inline void InstructionEngine::freturnHandler(){}
inline void InstructionEngine::dreturnHandler(){}
inline void InstructionEngine::areturnHandler(){}
inline void InstructionEngine::returnHandler(){}

inline void InstructionEngine::ifnullHandler(){
	j_int offset = readOffset16();
	ObjectPtr ref = currentOperandStack->popRef();
	if(!ref){
		branch(offset);
	}
}
inline void InstructionEngine::ifnonnullHandler(){
	j_int offset = readOffset16();
	ObjectPtr ref = currentOperandStack->popRef();
	if(!ref){
		branch(offset);
	}
}



