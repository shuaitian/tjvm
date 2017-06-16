#ifndef _DEF_H_
#define _DEF_H_
#include <inttypes.h>
namespace tt{

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef int8_t j_byte;
typedef int16_t j_short;
typedef int32_t j_int;
typedef int64_t j_long;
typedef uint16_t j_char;
typedef float j_float;
typedef double j_double;
typedef bool j_boolean;

const u1 nop = 0x00;
const u1 aconst_null = 0x01;
const u1 iconst_m1 = 0x02;
const u1 iconst_0 = 0x03;
const u1 iconst_1 = 0x04;
const u1 iconst_2 = 0x05;
const u1 iconst_3 = 0x06;
const u1 iconst_4 = 0x07;
const u1 iconst_5 = 0x08;
const u1 lconst_0 = 0x09;
const u1 lconst_1 = 0x0a;
const u1 fconst_0 = 0x0b;
const u1 fconst_1 = 0x0c;
const u1 fconst_2 = 0x0d;
const u1 dconst_0 = 0x0e;
const u1 dconst_1 = 0x0f;
const u1 bipush = 0x10;
const u1 sipush = 0x11;
const u1 ldc = 0x12;
const u1 ldc_w = 0x13;
const u1 ldc2_w = 0x14;

const u1 iload = 0x15;
const u1 lload = 0x16;
const u1 fload = 0x17;
const u1 dload = 0x18;
const u1 aload = 0x19;
const u1 iload_0 = 0x1a;
const u1 iload_1 = 0x1b;
const u1 iload_2 = 0x1c;
const u1 iload_3 = 0x1d;
const u1 lload_0 = 0x1e;
const u1 lload_1 = 0x1f;
const u1 lload_2 = 0x20;
const u1 lload_3 = 0x21;
const u1 fload_0 = 0x22;
const u1 fload_1 = 0x23;
const u1 fload_2 = 0x24;
const u1 fload_3 = 0x25;
const u1 dload_0 = 0x26;
const u1 dload_1 = 0x27;
const u1 dload_2 = 0x28;
const u1 dload_3 = 0x29;
const u1 aload_0 = 0x2a;
const u1 aload_1 = 0x2b;
const u1 aload_2 = 0x2c;
const u1 aload_3 = 0x2d;
const u1 iaload = 0x2e;
const u1 laload = 0x2f;
const u1 faload = 0x30;
const u1 daload = 0x31;
const u1 aaload = 0x32;
const u1 baload = 0x33;
const u1 caload = 0x34;
const u1 saload = 0x35;

const u1 istore = 0x36;
const u1 lstore = 0x37;
const u1 fstore = 0x38;
const u1 dstore = 0x39;
const u1 astore = 0x3a;
const u1 istore_0 = 0x3b;
const u1 istore_1 = 0x3c;
const u1 istore_2 = 0x3d;
const u1 istore_3 = 0x3e;
const u1 lstore_0 = 0x3f;
const u1 lstore_1 = 0x40;
const u1 lstore_2 = 0x41;
const u1 lstore_3 = 0x42;
const u1 fstore_0 = 0x43;
const u1 fstore_1 = 0x44;
const u1 fstore_2 = 0x45;
const u1 fstore_3 = 0x46;
const u1 dstore_0 = 0x47;
const u1 dstore_1 = 0x48;
const u1 dstore_2 = 0x49;
const u1 dstore_3 = 0x4a;
const u1 astore_0 = 0x4b;
const u1 astore_1 = 0x4c;
const u1 astore_2 = 0x4d;
const u1 astore_3 = 0x4e;
const u1 iastore = 0x4f;
const u1 lastore = 0x50;
const u1 fastore = 0x51;
const u1 dastore = 0x52;
const u1 aastore = 0x53;
const u1 bastore = 0x54;
const u1 castore = 0x55;
const u1 sastore = 0x56;

//stack
const u1 pop = 0x57;
const u1 pop2 = 0x58;
const u1 dup = 0x59; 
const u1 dup_x1 = 0x5a;
const u1 dup_x2 = 0x5b;
const u1 dup2 = 0x5c;
const u1 dup2_x1 = 0x5d;
const u1 dup2_x2 = 0x5e;
const u1 swap_ = 0x5f; //for ambigious

//math
const u1 iadd = 0x60;
const u1 ladd = 0x61;
const u1 fadd = 0x62;
const u1 dadd = 0x63;
const u1 isub = 0x64;
const u1 lsub = 0x65;
const u1 fsub = 0x66;
const u1 dsub = 0x67;
const u1 imul = 0x68;
const u1 lmul = 0x69;
const u1 fmul = 0x6a;
const u1 dmul = 0x6b;
const u1 idiv = 0x6c;
const u1 ldiv = 0x6d;
const u1 fdiv = 0x6e;
const u1 ddiv = 0x6f;
const u1 irem = 0x70;
const u1 lrem = 0x71;
const u1 frem = 0x72;
const u1 drem = 0x73;
const u1 ineg = 0x74;
const u1 lneg = 0x75;
const u1 fneg = 0x76;
const u1 dneg = 0x77;
const u1 ishl = 0x78;
const u1 lshl = 0x79;
const u1 ishr = 0x7a;
const u1 lshr = 0x7b;
const u1 iushr = 0x7c;
const u1 lushr = 0x7d;
const u1 iand = 0x7e;
const u1 land = 0x7f;
const u1 ior = 0x80;
const u1 lor = 0x81;
const u1 ixor = 0x82;
const u1 lxor = 0x83;
const u1 iinc = 0x84;

//conversion
const u1 i2l = 0x85;
const u1 i2f = 0x86;
const u1 i2d = 0x87;
const u1 l2i = 0x88;
const u1 l2f = 0x89;
const u1 l2d = 0x8a;
const u1 f2i = 0x8b;
const u1 f2l = 0x8c;
const u1 f2d = 0x8d;
const u1 d2i = 0x8e;
const u1 d2l = 0x8f;
const u1 d2f = 0x90;
const u1 i2b = 0x91;
const u1 i2c = 0x92;
const u1 i2s = 0x93;

//comparison
const u1 lcmp = 0x94;
const u1 fcmpl = 0x95;
const u1 fcmpg = 0x96;
const u1 dcmpl = 0x97;
const u1 dcmpg = 0x98;
const u1 ifeq = 0x99;
const u1 ifne = 0x9a;
const u1 iflt = 0x9b;
const u1 ifge = 0x9c;
const u1 ifgt = 0x9d;
const u1 ifle = 0x9e;
const u1 if_icmpeq = 0x9f;
const u1 if_icmpne = 0xa0;
const u1 if_icmplt = 0xa1;
const u1 if_icmpge = 0xa2;
const u1 if_icmpgt = 0xa3;
const u1 if_icmple = 0xa4;
const u1 if_acmpeq = 0xa5;
const u1 if_acmpne = 0xa6;

const u1 goto_ = 0xa7;
const u1 jsr = 0xa8;
const u1 ret = 0xa9;
const u1 tableswitch = 0xaa;
const u1 lookupswitch = 0xab;
const u1 ireturn = 0xac;
const u1 lreturn = 0xad;
const u1 freturn = 0xae;
const u1 dreturn = 0xaf;
const u1 areturn = 0xb0;
const u1 return_ = 0xb1;

//extended
const u1 wide = 0xc4;
const u1 multianewarray = 0xc5;
const u1 ifnull = 0xc6;
const u1 ifnonnull = 0xc7;
const u1 goto_w = 0xc8;
const u1 jsr_w = 0xc9;


//access flags
const u2 ACC_PUBLIC = 0x0001;
const u2 ACC_PRIVATE = 0x0002;
const u2 ACC_PROTECTED = 0x0004;
const u2 ACC_STATIC = 0x0008;
const u2 ACC_FINAL = 0x0010;
const u2 ACC_SUPER = 0x0020;
const u2 ACC_SYNCHRONIZED = 0x0020;
const u2 ACC_VOLATILE = 0x0040;
const u2 ACC_BRIDGE = 0x0040;
const u2 ACC_TRANSIENT = 0x0080;
const u2 ACC_VARARGS = 0x0080;
const u2 ACC_NATIVE = 0x0100;
const u2 ACC_INTERFACE = 0x0200;
const u2 ACC_ABSTRACT = 0x0400;
const u2 ACC_STRICT = 0x0800;
const u2 ACC_SYNTHETIC = 0x1000;
const u2 ACC_ANNOTATION = 0x2000;
const u2 ACC_ENUM = 0x4000;


}// namespace tt

using namespace tt;
#endif
