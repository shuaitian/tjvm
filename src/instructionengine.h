#ifndef _INSTRUCTIONENGINE_H_
#define _INSTRUCTIONENGINE_H_
#include <map>
#include <boost/smart_ptr.hpp>
#include <boost/function.hpp>
#include "def.h"
#include "frame.h"
#include "bytecodereader.h"
#include "operandstack.h"
#include "localvars.h"
using namespace boost;
using namespace std;
class InstructionEngine;
typedef shared_ptr<InstructionEngine> InstructionEnginePtr;

class InstructionEngine
{
private:
	map<u1,function<void()> > codeMap;
	InstructionEngine(FramePtr currentFrame,ByteCodeReaderPtr currentCodeReader);
	FramePtr currentFrame;
	ByteCodeReaderPtr currentCodeReader;
	LocalVarsPtr currentLocalVars;
	OperandStackPtr currentOperandStack;
	j_int pc;
public:
	void regist(u1 code,function<void()> handler);
	void run(u1 code);
	static InstructionEnginePtr build(FramePtr currentFrame,ByteCodeReaderPtr currentCodeReader);
	void reset(FramePtr currentFrame,ByteCodeReaderPtr currentCodeReader);
private:
	void branch(j_int offset);
	j_int readOffset16();

	void nopHandler();
	void aconstNullHandler();
	void dconst0Handler();
	void dconst1Handler();
	void fconst0Handler();
	void fconst1Handler();
	void fconst2Handler();
	void iconstM1Handler();
	void iconst0Handler();
	void iconst1Handler();
	void iconst2Handler();
	void iconst3Handler();
	void iconst4Handler();
	void iconst5Handler();
	void lconst0Handler();
	void lconst1Handler();
	void bipushHandler();
	void sipushHandler();

	void iloadHandler();
	void iload0Handler();
	void iload1Handler();
	void iload2Handler();
	void iload3Handler();

	void lloadHandler();
	void lload0Handler();
	void lload1Handler();
	void lload2Handler();
	void lload3Handler();

	void floadHandler();
	void fload0Handler();
	void fload1Handler();
	void fload2Handler();
	void fload3Handler();

	void dloadHandler();
	void dload0Handler();
	void dload1Handler();
	void dload2Handler();
	void dload3Handler();

	void aloadHandler();
	void aload0Handler();
	void aload1Handler();
	void aload2Handler();
	void aload3Handler();
	
	//store
	void istoreHandler();
	void istore0Handler();
	void istore1Handler();
	void istore2Handler();
	void istore3Handler();

	void lstoreHandler();
	void lstore0Handler();
	void lstore1Handler();
	void lstore2Handler();
	void lstore3Handler();

	void fstoreHandler();
	void fstore0Handler();
	void fstore1Handler();
	void fstore2Handler();
	void fstore3Handler();

	void dstoreHandler();
	void dstore0Handler();
	void dstore1Handler();
	void dstore2Handler();
	void dstore3Handler();
	
	void astoreHandler();
	void astore0Handler();
	void astore1Handler();
	void astore2Handler();
	void astore3Handler();

	//stack
	void popHandler();
	void pop2Handler();
	void dupHandler();
	void dupX1Handler();
	void dupX2Handler();
	void dup2Handler();
	void dup2X1Handler();
	void dup2X2Handler();
	void swapHandler();

	//math
	
	void iremHandler();
	void lremHandler();
	void fremHandler();
	void dremHandler();

	void iaddHandler();
	void laddHandler();
	void faddHandler();
	void daddHandler();

	void isubHandler();
	void lsubHandler();
	void fsubHandler();
	void dsubHandler();

	void imulHandler();
	void lmulHandler();
	void fmulHandler();
	void dmulHandler();

	void idivHandler();
	void ldivHandler();
	void fdivHandler();
	void ddivHandler();

	void inegHandler();
	void lnegHandler();
	void fnegHandler();
	void dnegHandler();

	void ishlHandler();
	void lshlHandler();
	void ishrHandler();
	void lshrHandler();
	void iushrHandler();
	void lushrHandler();

	void iandHandler();
	void landHandler();
	void iorHandler();
	void lorHandler();
	void ixorHandler();
	void lxorHandler();
	void iincHandler();

	void i2lHandler();
	void i2fHandler();
	void i2dHandler();
	void l2iHandler();
	void l2fHandler();
	void l2dHandler();
	void f2iHandler();
	void f2lHandler();
	void f2dHandler();
	void d2iHandler();
	void d2lHandler();
	void d2fHandler();
	void i2bHandler();
	void i2cHandler();
	void i2sHandler();

	//comparison
	void lcmpHandler();
	void fcmplHandler();
	void fcmpgHandler();
	void dcmplHandler();
	void dcmpgHandler();
	void ifeqHandler();
	void ifneHandler();
	void ifltHandler();
	void ifgeHandler();
	void ifgtHandler();
	void ifleHandler();
	void ifIcmpeqHandler();
	void ifIcmpneHandler();
	void ifIcmpltHandler();
	void ifIcmpgeHandler();
	void ifIcmpgtHandler();
	void ifIcmpleHandler();
	void ifAcmpeqHandler();
	void ifAcmpneHandler();

	//Control
	void gotoHandler();
	void jsrHandler();
	void retHandler();
	void tableswitchHandler();
	void lookupswitchHandler();
	void ireturnHandler();
	void lreturnHandler();
	void freturnHandler();
	void dreturnHandler();
	void areturnHandler();
	void returnHandler();

	//references
	void newHandler();

	//extended
	void ifnullHandler();
	void ifnonnullHandler();
};

#endif