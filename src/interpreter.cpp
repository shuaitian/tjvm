#include "interpreter.h"
#include "attributeitem.h"
#include "threadprivate.h"
#include "bytecodereader.h"
#include "instructionengine.h"
#include <stdio.h>

Interpreter::Interpreter():
	threadPrivate(ThreadPrivate::build())
{

}
void Interpreter::interpret(MemberItemPtr method){
	CodeAttrItemPtr codeItem = method->getCodeAttribute();
	FramePtr frame = Frame::build(codeItem->getMaxLocals(),codeItem->getMaxStack(),threadPrivate);
	ByteCodeReaderPtr codeReader = ByteCodeReader::build(codeItem);

	threadPrivate->pushFrame(frame);
	InstructionEnginePtr engine = InstructionEngine::build(frame,codeReader);
	j_int pc;

	while(true){
		pc = threadPrivate->getPC();
		codeReader->setPC(pc);
		u1 code = codeReader->readUint8();
		//printf("inst %x ...\n",code);
		engine->run(code);
	}

}

InterpreterPtr Interpreter::build(){
	InterpreterPtr ret(new Interpreter());
	return ret;
}