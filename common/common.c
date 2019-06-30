
#include "common.h"

InstrInfo instr_infos[] = {

    {OPCODE_NOPE,               "NOPE",             0, 0}, // ok
    {OPCODE_END,                "END",              0, 0}, // OK
    {OPCODE_PUSH_I64,           "PUSH_I64",         (int[]) {OPT_I64}, 1}, // OK
    {OPCODE_PUSH_F64,           "PUSH_F64",         (int[]) {OPT_F64}, 1}, // OK
    {OPCODE_PUSH_STRING,        "PUSH_STRING",      (int[]) {OPT_STRING}, 1}, // OK
    {OPCODE_PUSH_NAMED,         "PUSH_NAMED",       (int[]) {OPT_STRING}, 1}, // OK
    {OPCODE_PUSH_TRUE,          "PUSH_TRUE",        (int[]) {}, 0}, // OK
    {OPCODE_PUSH_FALSE,         "PUSH_FALSE",       (int[]) {}, 0}, // OK
    {OPCODE_PUSH_SELF,          "PUSH_SELF",        (int[]) {}, 0}, // OK
    {OPCODE_PUSH_FUNC,          "PUSH_FUNC",        (int[]) {OPT_STRING, OPT_U32}, 2}, // OK
    {OPCODE_PUSH_ATTR,          "PUSH_ATTR",        (int[]) {OPT_STRING}, 1}, // OK
    {OPCODE_PUSH_METHOD,        "PUSH_METHOD",      (int[]) {OPT_STRING, OPT_U32}, 2}, // ok
    {OPCODE_PUSH_ARG,           "PUSH_ARG",         (int[]) {}, 0}, // OK
    {OPCODE_JUMP,               "JUMP",             (int[]) {OPT_U32}, 1}, // OK
    {OPCODE_JUMPR,              "JUMPR",            (int[]) {OPT_U32}, 1}, // OK
    {OPCODE_JIFTP,              "JIFTP",            (int[]) {OPT_I32}, 1}, // OK
    {OPCODE_JIFFP,              "JIFFP",            (int[]) {OPT_I32}, 1}, // OK
    {OPCODE_BIFFP,              "BIFFP",            (int[]) {}, 0}, // OK
    {OPCODE_BREAK,              "BREAK",            (int[]) {}, 0}, // OK
    {OPCODE_CONTINUE,           "CONTINUE",         (int[]) {}, 0}, // OK
    {OPCODE_CALL,               "CALL",             (int[]) {}, 0}, // OK
    {OPCODE_POP,                "POP",              (int[]) {}, 0}, // OK
    {OPCODE_ADD,                "ADD",              (int[]) {}, 0}, // OK
    {OPCODE_SUB,                "SUB",              (int[]) {}, 0}, // OK
    {OPCODE_MUL,                "MUL",              (int[]) {}, 0}, // OK
    {OPCODE_DIV,                "DIV",              (int[]) {}, 0}, // OK
    {OPCODE_LSS,                "LSS",              (int[]) {}, 0}, // OK
    {OPCODE_GRT,                "GRT",              (int[]) {}, 0}, // OK
    {OPCODE_LEQ,                "LEQ",              (int[]) {}, 0}, // OK
    {OPCODE_GEQ,                "GEQ",              (int[]) {}, 0}, // OK
    {OPCODE_EQL,                "EQL",              (int[]) {}, 0}, // OK
    {OPCODE_NQL,                "NQL",              (int[]) {}, 0}, // OK
    {OPCODE_AND,                "AND",              (int[]) {}, 0}, // OK
    {OPCODE_OR,                 "OR",               (int[]) {}, 0},   // OK
    {OPCODE_XOR,                "XOR",              (int[]) {}, 0}, // OK
    {OPCODE_ASSIGN,             "ASSIGN",           (int[]) {OPT_STRING}, 1}, // OK
    {OPCODE_PRINT,              "PRINT",            (int[]) {}, 0}, // OK
    {OPCODE_PRINTLN,            "PRINTLN",          (int[]) {}, 0}, // OK
    {OPCODE_TYPE_NAME,          "TYPE_NAME",        (int[]) {}, 0}, // OK
    {OPCODE_TYPE,               "TYPE",             (int[]) {}, 0}, // OK
    {OPCODE_WHILE_BEG,          "WHILE_BEG",        (int[]) {OPT_U32}, 1}, // OK
    {OPCODE_WHILE_END,          "WHILE_END",        (int[]) {}, 0}, // OK
    {OPCODE_FUNC_BEG,           "FUNC_BEG",         (int[]) {}, 0}, // OK
    {OPCODE_FUNC_END,           "FUNC_END",         (int[]) {}, 0}, // OK
    {OPCODE_BUILD_CLASS,        "BUILD_CLASS",      (int[]) {}, 0}, // ok
    {OPCODE_BUILD_ARRAY,        "BUILD_ARRAY",      (int[]) {}, 0}, // OK
    {OPCODE_DICT_CREATE,        "DICT_CREATE",      (int[]) {}, 0}, // OK
    {OPCODE_INSERT,             "INSERT",           (int[]) {}, 0}, // OK
    {OPCODE_SELECT,             "SELECT",           (int[]) {}, 0}, // OK
    {OPCODE_SET_ATTR,           "SET_ATTR",         (int[]) {OPT_STRING}, 1}, // OK
    {OPCODE_TRY_ASSIGN_ARG,     "TRY_ASSIGN_ARG",   (int[]) {OPT_STRING}, 1}, // OK
    {OPCODE_TRY_ASSIGN_SELF,    "TRY_ASSIGN_SELF",  (int[]) {}, 0}, // OK
    {OPCODE_AREC_CREATE,        "AREC_CREATE",      (int[]) {}, 0}, // OK
    {OPCODE_BREAKPOINT,         "BREAKPOINT",       (int[]) {}, 0}, // OK
    {OPCODE_IMPORT,             "IMPORT",           (int[]) {OPT_STRING}, 1}, // ok
    {OPCODE_IMPORT_AND_NAME,    "IMPORT_AND_NAME",  (int[]) {OPT_STRING, OPT_STRING}, 2}, // ok
    {OPCODE_CIMPORT,            "CIMPORT",          (int[]) {OPT_STRING}, 1}, // OK
    {OPCODE_CIMPORT_AND_NAME,   "CIMPORT_AND_NAME", (int[]) {OPT_STRING, OPT_STRING}, 2}, // OK
    {OPCODE_LINENO,             "LINENO",           (int[]){OPT_U32}, 1} // ok
};

int instr_count = sizeof(instr_infos) / sizeof(InstrInfo);

InstrInfo *get_instrinfo_by_repr(char repr) {
    for(int i = 0; i < instr_count; i++)
        if(instr_infos[i].repr == repr)
            return instr_infos + i;
    return 0;
}

InstrInfo *get_instrinfo_by_name(char *name) {
    for(int i = 0; i < instr_count; i++)
        if(strcmp(instr_infos[i].name, name) == 0)
            return instr_infos + i;
    return 0;
}

char get_instr_allignment(InstrInfo *instr) {
  return 1;
}

char *opcode_name(u8 opcode) {
    switch(opcode) {
        case OPCODE_NOPE:           return "NOPE";
        case OPCODE_END:            return "END";
        case OPCODE_PUSH_I64:       return "PUSH_I64";
        case OPCODE_PUSH_F64:       return "PUSH_F64";
        case OPCODE_PUSH_STRING:    return "PUSH_STRING";
        case OPCODE_PUSH_NAMED:     return "PUSH_NAMED";
        case OPCODE_JUMP:           return "JUMP";
        case OPCODE_JUMPR:          return "JUMPR";
        case OPCODE_JIFTP:          return "JIFTP";
        case OPCODE_JIFFP:          return "JIFFP";
        case OPCODE_POP:            return "POP";
        case OPCODE_ADD:            return "ADD";
        case OPCODE_SUB:            return "SUB";
        case OPCODE_MUL:            return "MUL";
        case OPCODE_DIV:            return "DIV";
        case OPCODE_ASSIGN:         return "ASSIGN";
        case OPCODE_PRINT:          return "PRINT";
        case OPCODE_PRINTLN:        return "PRINTLN";
        case OPCODE_TYPE_NAME:      return "TYPENAME";
        case OPCODE_TYPE:           return "TYPE";
        case OPCODE_WHILE_BEG:      return "WHILE_BEG";
        case OPCODE_WHILE_END:      return "WHILE_END";
        case OPCODE_BIFFP:          return "BIFFP";
        case OPCODE_BREAK:          return "BREAK";
        case OPCODE_CONTINUE:       return "CONTINUE";
        case OPCODE_BUILD_ARRAY:    return "BUILD_ARRAY";
        case OPCODE_DICT_CREATE:    return "DICT_CREATE";
        case OPCODE_INSERT:         return "INSERT";
        case OPCODE_CALL:           return "CALL";
        case OPCODE_PUSH_ARG:       return "PUSH_ARG";
        case OPCODE_TRY_ASSIGN_ARG: return "TRY_ASSIGN_ARG";
        case OPCODE_FUNC_BEG:       return "FUNC_BEG";
        case OPCODE_FUNC_END:       return "FUNC_END";
        case OPCODE_PUSH_FUNC:      return "PUSH_FUNC";
        case OPCODE_PUSH_ATTR :     return "PUSH_ATTR";
        case OPCODE_SELECT    :     return "SELECT";
        case OPCODE_SET_ATTR  :     return "SET_ATTR";
        case OPCODE_LSS:            return "LSS";
        case OPCODE_LEQ:            return "LEQ";
        case OPCODE_GRT:            return "GRT";
        case OPCODE_GEQ:            return "GEQ";
        case OPCODE_EQL:            return "EQL";
        case OPCODE_NQL:            return "NQL";
        case OPCODE_AND:            return "AND";
        case OPCODE_OR :            return "OR";
        case OPCODE_XOR:            return "XOR";
        case OPCODE_AREC_CREATE:    return "AREC_CREATE";
        case OPCODE_PUSH_TRUE:      return "PUSH_TRUE";
        case OPCODE_PUSH_FALSE:     return "PUSH_FALSE";
        case OPCODE_BREAKPOINT:             return "BREAKPOINT";
        case OPCODE_PUSH_SELF:              return "OPCODE_PUSH_SELF";
        case OPCODE_TRY_ASSIGN_SELF:        return "OPCODE_TRY_ASSIGN_SELF";
        case OPCODE_IMPORT:                return "IMPORT";
        case OPCODE_IMPORT_AND_NAME:       return "IMPORT_AND_NAME";
        case OPCODE_CIMPORT:               return "CIMPORT";
        case OPCODE_CIMPORT_AND_NAME:      return "CIMPORT_AND_NAME";

    }
    return "???";
}
