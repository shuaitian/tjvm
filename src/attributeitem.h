#ifndef _ATTRIBUTEITEM_H_
#define _ATTRIBUTEITEM_H_
#include <boost/smart_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include <vector>
#include "attribute.h"

using namespace std;
using namespace boost;

class Attribute;
class AttributeItem{
private:
	u4 length;
public:
	void setLength(u4 length){
		this->length = length;
	}
	
	u4 getLength(){
		return this->length;
	}
};

class DeprecatedAttrItem : public AttributeItem{};
class SyntheticAttrItem : public AttributeItem{};

class SourceFileAttrItem : public AttributeItem{
private:
	u2 sourceFileIndex;
	string_ref sourceFile;
public:
	void setSourceFileIndex(u2 sourceFileIndex){
		this->sourceFileIndex = sourceFileIndex;
	}
	u2 getSourceFileIndex(){
		return this->sourceFileIndex;
	}

	void setSourceFile(string_ref sourceFile){
		this->sourceFile = sourceFile;
	}
	string_ref getSourceFile(){
		return this->sourceFile;
	}
};

class ConstantValueAttrItem : public AttributeItem{
private:
	u2 constValueIndex;
public:
	void setConstValueIndex(u2 constValueIndex){
		this->constValueIndex = constValueIndex;
	}
	u2 getConstValueIndex(){
		return this->constValueIndex;
	}
};

struct ExceptionTableEntry{
	u2 startPC;
	u2 endPC;
	u2 handlerPC;
	u2 catchType;
};

class CodeAttrItem : public AttributeItem{
private:
	u2 maxStack;
	u2 maxLocals;
	u4 codeLength;
	shared_ptr<vector<u1> > code;
	u2 exceptionTableLength;
	shared_ptr<vector<ExceptionTableEntry> > exceptionTable;
	u2 attributesCount;
	shared_ptr<vector<Attribute> > attributes;
public:
	void setMaxStack(u2 maxStack){
		this->maxStack = maxStack;
	}
	void setMaxLocals(u2 maxLocals){
		this->maxLocals = maxLocals;
	}
	void setCodeLength(u4 codeLength){
		this->codeLength = codeLength;
	}
	void setCode(shared_ptr<vector<u1> > code){
		this->code = code;
	}
	void setExceptionTableLength(u2 length){
		this->exceptionTableLength = length;
	}
	void setExceptionTable(shared_ptr<vector<ExceptionTableEntry> > table){
		this->exceptionTable = table;
	}
	void setAttributesCount(u2 count){
		this->attributesCount = count;
	}
	void setAttributes(shared_ptr<vector<Attribute> > attr){
		this->attributes = attr;
	}
	
	u2 getMaxStack(){
		return this->maxStack;
	}
	u2 getMaxLocals(){
		return this->maxLocals;
	}
	u4 getCodeLength(){
		return this->codeLength;
	}
	shared_ptr<vector<u1> > getCode(){
		return this->code;
	}
	u2 getExceptionTableLength(){
		return this->exceptionTableLength;
	}
	shared_ptr<vector<ExceptionTableEntry> > getExceptionTable(){
		return this->exceptionTable;
	}
	u2 getAttributesCount(){
		return this->attributesCount;
	}
	shared_ptr<vector<Attribute> > getAttributes(){
		return this->attributes;
	}

};

class ExceptionsAttrItem : public AttributeItem{
private:
	u2 numberOfExceptions;
	shared_ptr<vector<u2> > exceptionIndexTable;
public:
	void setNumberOfExceptions(u2 numberOfExceptions){
		this->numberOfExceptions = numberOfExceptions;
	}
	void setExceptionIndexTable(shared_ptr<vector<u2> > exceptionIndexTable){
		this->exceptionIndexTable = exceptionIndexTable;
	}

	u2 getNumberOfExceptions(){
		return numberOfExceptions;
	}
	shared_ptr<vector<u2> > getExceptionIndexTable(){
		return exceptionIndexTable;
	}
};

struct LineNumberTableEntry
{
	u2 startPC;
	u2 lineNumber;
};

class LineNumberTableAttrItem : public AttributeItem {
private:
	u2 lineNumberTableLength;
	shared_ptr<vector<LineNumberTableEntry> >lineNumberTable;
public:
	void setLineNumberTableLength(u2 lineNumberTableLength){
		this->lineNumberTableLength = lineNumberTableLength;
	}
	void setLineNumberTable(shared_ptr<vector<LineNumberTableEntry> >lineNumberTable){
		this->lineNumberTable = lineNumberTable;
	}

	u2 getLineNumberTableLength(){
		return this->lineNumberTableLength;
	}
	shared_ptr<vector<LineNumberTableEntry> > getLineNumberTable(){
		return this->lineNumberTable;
	}
};

typedef shared_ptr<AttributeItem> AttrItemPtr;

#endif
