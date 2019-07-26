
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

enum {
    /* Bytecode instructions */
    OPCODE_NOPE,
    OPCODE_END,
    OPCODE_PUSH_I64,
    OPCODE_PUSH_F64,
    OPCODE_PUSH_STRING,
    OPCODE_PUSH_NAMED,
    OPCODE_JUMP,
    OPCODE_JUMPR,
    OPCODE_JIFTP,
    OPCODE_JIFFP,
    OPCODE_POP,
    OPCODE_ADD,
    OPCODE_SUB,
    OPCODE_MUL,
    OPCODE_DIV,
    OPCODE_LSS,
    OPCODE_GRT,
    OPCODE_LEQ,
    OPCODE_GEQ,
    OPCODE_EQL,
    OPCODE_NQL,
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_XOR,
    OPCODE_ASSIGN,
    OPCODE_PRINT,
    OPCODE_PRINTLN,
    OPCODE_TYPE_NAME,
    OPCODE_TYPE,
    OPCODE_WHILE_BEG,
    OPCODE_WHILE_END,
    OPCODE_BIFFP,
    OPCODE_BREAK,
    OPCODE_CONTINUE,
    OPCODE_BUILD_ARRAY,
    OPCODE_DICT_CREATE,
    OPCODE_INSERT,
    OPCODE_CALL,
    OPCODE_PUSH_ARG,
    OPCODE_TRY_ASSIGN_ARG,
    OPCODE_FUNC_BEG,
    OPCODE_FUNC_END,
    OPCODE_PUSH_FUNC,
    OPCODE_PUSH_ATTR,
    OPCODE_SELECT,
    OPCODE_SET_ATTR,
    OPCODE_AREC_CREATE,
    OPCODE_PUSH_TRUE,
    OPCODE_PUSH_FALSE,
    OPCODE_BREAKPOINT,
    OPCODE_PUSH_SELF,
    OPCODE_TRY_ASSIGN_SELF,
    OPCODE_IMPORT,
    OPCODE_IMPORT_AND_NAME,
    OPCODE_CIMPORT,
    OPCODE_CIMPORT_AND_NAME,
    OPCODE_BUILD_CLASS, // create a class object and pushed it onto the stack
    OPCODE_PUSH_METHOD, // inserts a method into the class object onto the stack
    OPCODE_LINENO,
    OPCODE_PUSH_LAMBDA,
  };

enum {
    OPT_U8, OPT_U16, OPT_U32, OPT_U64,
    OPT_I8, OPT_I16, OPT_I32, OPT_I64,
                     OPT_F32, OPT_F64,
    OPT_STRING,
};

typedef struct InstrInfo {
    char  repr;
    char *name;
    int  *arg_types;
    int   arg_count;
} InstrInfo;

extern InstrInfo instr_infos[];
extern int instr_count;

char *opcode_name(u8 opcode);
void printb(char b);
InstrInfo *get_instrinfo_by_name(char *name);
InstrInfo *get_instrinfo_by_repr(char repr);
char get_instr_allignment(InstrInfo *instr);

#endif
