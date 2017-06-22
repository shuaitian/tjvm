#include "interpreter.h"
#include "attributeitem.h"
#include "threadprivate.h"
#include "bytecodereader.h"
#include "instructionengine.h"
#include "method.h"
#include <stdio.h>
#include <vector>

Interpreter::Interpreter():
	threadPrivate(ThreadPrivate::build())
{

}
void Interpreter::interpret(shared_ptr<Method> method){
	shared_ptr<vector<u1> > code = method->getCode();	
	FramePtr frame = Frame::build(method->getMaxLocals(),method->getMaxStack(),threadPrivate);
	frame->setMethod(method);
	ByteCodeReaderPtr codeReader = ByteCodeReader::build(code);

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