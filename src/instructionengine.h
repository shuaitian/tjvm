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
public:
	void regist(u1 code,function<void()> handler);
	void run(u1 code);
	static InstructionEnginePtr build(FramePtr currentFrame,ByteCodeReaderPtr currentCodeReader);
	void reset(FramePtr currentFrame,ByteCodeReaderPtr currentCodeReader);
private:
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
	


};

#endif