
#include "../common/common.h"

typedef struct AST_Node                 AST_Node;
typedef struct AST_Node_Exp             AST_Node_Exp;
typedef struct AST_Node_Block           AST_Node_Block;
typedef struct AST_Node_If              AST_Node_If;
typedef struct AST_Node_While           AST_Node_While;
typedef struct AST_Node_ExpList         AST_Node_ExpList;
typedef struct AST_Node_Print           AST_Node_Print;
typedef struct AST_Node_Assign          AST_Node_Assign;
typedef struct AST_Node_DictEntry       AST_Node_DictEntry;
typedef struct AST_Node_Dict            AST_Node_Dict;
typedef struct AST_Node_LabelList       AST_Node_LabelList;
typedef struct AST_Node_ObjectFunction  AST_Node_ObjectFunction;
typedef struct AST_Node_Identifier      AST_Node_Identifier;
typedef struct AST_Node_Return          AST_Node_Return;
typedef struct AST_Node_Import          AST_Node_Import;
typedef struct AST_Node_Class           AST_Node_Class;


enum {

    /* Node types */

    NODE_EXP,
    NODE_BLOCK,
    NODE_IF,
    NODE_WHILE,
    NODE_EXPLIST,
    NODE_BREAK,
    NODE_CONTINUE,
    NODE_PRINT,
    NODE_DICT,
    NODE_DICTENTRY,
    NODE_LABELLIST,
    NODE_FUNCTION,
    NODE_IDENTIFIER,
    NODE_BREAKPOINT,
    NODE_RETURN,

    NODE_IMPORT,
    NODE_CLASS,

};

enum {

    /* Expression node types */

    EXP_I64,
    EXP_F64,
    EXP_STRING,
    EXP_ARRAY,
    EXP_DICT,
    EXP_LABEL,
    EXP_CALL,
    EXP_ADD,
    EXP_SUB,
    EXP_MUL,
    EXP_DIV,
    EXP_LSS,
    EXP_GRT,
    EXP_LEQ,
    EXP_GEQ,
    EXP_EQL,
    EXP_NQL,
    EXP_AND,
    EXP_OR,
    EXP_XOR,
    EXP_SELECT,
    EXP_SELECT_ATTR,
    EXP_ASSIGN,
    EXP_TRUE,
    EXP_FALSE,
    EXP_LAMBDA,

};

enum {
  EXP_CONSTANT    = 1,
  EXP_ASSIGNABLE  = 2,
};

#define AST_NODE_HEAD               \
    u8                  n_type;     \
    AST_Node*           n_next;     \
    u32                 lineno;   \
    u32                 flags

struct AST_Node {
    AST_NODE_HEAD;

};

struct AST_Node_Import {
  AST_NODE_HEAD;
  char *name, *as;
};

struct AST_Node_Return {
  AST_NODE_HEAD;
  AST_Node *value;
};

struct AST_Node_ObjectFunction {

    AST_NODE_HEAD;

    char     *name;
    AST_Node *args;
    AST_Node *block;
};

struct AST_Node_DictEntry {

    AST_NODE_HEAD;

    char *label;
    AST_Node *value;

};

struct AST_Node_Dict {

    AST_NODE_HEAD;

    AST_Node *head,
             *tail;
    u32       count;

};

struct AST_Node_Print {

    AST_NODE_HEAD;

    AST_Node *args;
    u32 arg_count;
};


struct AST_Node_Assign {

    AST_NODE_HEAD;

    AST_Node *identifier;
    AST_Node *value;
};


struct AST_Node_Identifier {

    AST_NODE_HEAD;

    char *base_label;

    struct {
        AST_Node *index;
        char     *attr_name;
        char      is_index;
    } elements[16];
    u32 elem_count;

};

struct AST_Node_Block {

    AST_NODE_HEAD;

    AST_Node *head, *tail;
    u32 count;
};

struct AST_Node_LabelList {

    AST_NODE_HEAD;

    char *labels[16];
    u32 count;
};

struct AST_Node_If {

    AST_NODE_HEAD;

    AST_Node *condition, *if_block, *else_block;
};

struct AST_Node_While {

    AST_NODE_HEAD;

    AST_Node *condition, *do_block;
};

struct AST_Node_Exp {

    AST_NODE_HEAD;

    u8 type;

    union {
        i64 value_i64;
        f64 value_f64;
        char *value_string;
        char *label;
        AST_Node_ExpList *value_array;
        AST_Node_Dict    *value_dict;
        AST_Node_ObjectFunction *value_lambda;
    };

    union {
        struct {
            AST_Node *l_exp, *r_exp;
        };

        struct {
            AST_Node *arg_exps;
            u32       arg_count;
        };
    };
};

struct AST_Node_ExpList {
    AST_NODE_HEAD;
    AST_Node *head, *tail;
    u32 count;
};

struct AST_Node_Class {
  AST_NODE_HEAD;
  char *name;
  AST_Node *members;
};

//void 		AST_Node_Exp_print(AST_Node *node, u32 depth);

AST_Node 	*AST_Node_create(u8 type);
AST_Node 	*AST_Node_ExpList_create();
void 		AST_Node_ExpList_append(AST_Node *node, AST_Node *e);
AST_Node 	*AST_Node_ObjectFunction_create(char *name, AST_Node *args, AST_Node *block);
AST_Node 	*AST_Node_LabelList_create();
void 		AST_Node_LabelList_append(AST_Node *_list, char *label);
AST_Node 	*AST_Node_Identifier_create(char *base_label);
void 		AST_Node_Identifier_append(AST_Node *_id, AST_Node *index, char *attr_name);
AST_Node 	*AST_Node_Print_create(AST_Node *node);
AST_Node 	*AST_Node_If_create(AST_Node *condition, AST_Node *if_block, AST_Node *else_block);
void 		AST_Node_If_append_else(AST_Node *node, AST_Node *else_block);
AST_Node 	*AST_Node_While_create(AST_Node *condition, AST_Node *do_block);
AST_Node 	*AST_Node_Return_create(AST_Node *value);
AST_Node 	*AST_Node_Block_create(AST_Node *child);
void 		AST_Node_append(AST_Node *node, AST_Node *node2);
AST_Node 	*AST_Node_Dict_create();
void 		AST_Node_Dict_append(AST_Node *_dict, char *label, AST_Node *value);
AST_Node 	*AST_Node_operator(u8 type, AST_Node *l_exp, AST_Node *r_exp);
AST_Node    *AST_Node_dict(AST_Node *_node);
AST_Node    *AST_Node_lambda(AST_Node *node);
AST_Node 	*AST_Node_true();
AST_Node 	*AST_Node_false();
AST_Node 	*AST_Node_string(char *string);
AST_Node 	*AST_Node_array(AST_Node *l);
AST_Node 	*AST_Node_i64(i64 value);
AST_Node 	*AST_Node_f64(f64 value);
AST_Node 	*AST_Node_label(char *label);
AST_Node 	*AST_Node_import_create(char *name, char *as);
AST_Node 	*AST_Node_Class_create(char *name, AST_Node *members);
AST_Node    *AST_Node_Return_create(AST_Node *value);
AST_Node    *AST_Node_import_create(char *name, char *as);

AST_Node *AST_Build(char *path);

/* === Builder === */

typedef struct Builder Builder;
typedef struct Segment Segment;

enum {
  BLOCK_CANT_RETURN = 1,
  BLOCK_IS_ROOT = 2
};

struct Segment {
    char *content;
    u32 size, used;
};

struct Builder {
    Segment data;
    Segment code;
    Segment code_start;
    Segment function_space;
    u32 lineno;
};

void Segment_free(Segment *seg);
char Segment_merge(Segment *a, Segment *b);
char Segment_resize(Segment *seg);
u32  Segment_insert_at(Segment *seg, u32 addr, void *s, u32 length);
u32 Segment_insert(Segment *seg, void *s, u32 length);
u32 Segment_insert_opcode(Segment *seg, char opcode);
u32 Segment_insert_padding(Segment *seg, u32 size);
u32 Segment_addr(Segment *seg);
void emit_lineno_of(Segment *seg, void *addr);

void Build_Exp_call(Segment *seg, AST_Node_Exp *exp);
void Build_ObjectArray(Segment *seg, AST_Node_Exp *exp);
void Build_DictEntry(Segment *seg, AST_Node *node);
void Build_Dict(Segment *seg, AST_Node_Exp *exp);
void Build_Method(Segment *seg, AST_Node *node);
void Build_ObjectFunction(Segment *seg, AST_Node *node);
void Build_Exp(Segment *seg, AST_Node *node);
void Build_Print(Segment *seg, AST_Node *node);
void Build_assign(Segment *seg, AST_Node *node);
void Build_Import(Segment *seg, AST_Node *node);
void Build_Class(Segment *seg, AST_Node *node);
void Build_Block(Segment *seg, AST_Node *node, int flags);
void Build_While(Segment *seg, AST_Node *node, int flags);
void Build_If(Segment *seg, AST_Node *node, int flags);
void Build_Lambda(Segment *seg, AST_Node *node); // TODO


char *Build(AST_Node *root, u32 *e_size);
void Compile(char *path, AST_Node *root);

extern int yylineno;
extern Builder builder;

char* duplicate_segment(const char *token, int size);