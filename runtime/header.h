
#include "../common/common.h"


#define __ObjectType__          &TypeTable_ObjectType
#define __ObjectInt__           &TypeTable_ObjectInt
#define __ObjectFloat__         &TypeTable_ObjectFloat
#define __ObjectString__        &TypeTable_ObjectString
#define __ObjectDict__          &TypeTable_Dict
#define __ObjectBuckets__       &TypeTable_Buckets
#define __ObjectArray__         &TypeTable_ObjectArray
#define __ObjectFunction__      &TypeTable_ObjectFunction
#define __ObjectCFunction__     &TypeTable_ObjectCFunction
#define __ObjectBool___         &TypeTable_ObjectBool


typedef struct Source Source;

struct Source {
    u32 file_size;
    u32 data_size;
    u32 code_size;
    u32 function_space_size;
    u32 function_space_addr;
    char *data;
    char *code;
};

typedef struct SourceMap SourceMap;
typedef struct SourceHeader SourceHeader;

struct SourceHeader {
  char *path;
  Source *source;
};

struct SourceMap {
  SourceHeader *headers;
  int size, used;
};

char    NOJA_SourceMap_init(SourceMap *map);
void    NOJA_SourceMap_free(SourceMap *map);
Source *NOJA_SourceMap_seek(SourceMap *map, char *path);
char    NOJA_SourceMap_insert(SourceMap *map, char *path, Source *source);


/* === Objects === */

typedef struct Object Object;
typedef struct ObjectType ObjectType;
typedef struct ObjectInt ObjectInt;
typedef struct ObjectFloat ObjectFloat;
typedef struct ObjectString ObjectString;
typedef struct ObjectDict ObjectDict;
typedef struct ObjectBucket ObjectBucket;
typedef struct ObjectBuckets ObjectBuckets;
typedef struct ObjectStringValue ObjectStringValue;
typedef struct ObjectArray ObjectArray;
typedef struct ObjectFunction ObjectFunction;
typedef struct ObjectCFunction ObjectCFunction;
typedef struct ObjectBool ObjectBool;
typedef struct ObjectModule ObjectModule;
typedef struct ObjectIstance ObjectIstance;

typedef struct Offset Offset;

struct Offset {
  u32 addr;
  Source *source;
};

typedef Object *(*Operator)(Object*, Object*);

extern Operator operator_matrix_add[6][6];
extern Operator operator_matrix_sub[6][6];
extern Operator operator_matrix_mul[6][6];
extern Operator operator_matrix_div[6][6];
extern Operator operator_matrix_lss[6][6];
extern Operator operator_matrix_leq[6][6];
extern Operator operator_matrix_grt[6][6];
extern Operator operator_matrix_geq[6][6];
extern Operator operator_matrix_eql[6][6];

char import_shared_library(char *name, Object *dest);

/* === Memory manager === */

typedef struct Memory_Manager Memory_Manager;
typedef struct Heap Heap;

struct Heap {
    u32   used,
          size;
    Heap *next;
    char chunk[];
};

struct Memory_Manager {
    u32 total_heaps_size;
    Heap *current_head,
         *current_tail,
         *temp;
};

void *Mem_allocate(u32 size);
void Mem_cycle();
void Mem_HeapList_destroy(Heap *heap);
void Mem_collect(Object **object_refr);
void Mem_release();
void Mem_init(u32 size);
Heap *Mem_Heap_create(u32 size);

extern Memory_Manager memory_man;

enum {
    OBJ_IS_GC_COLLECTABLE   = 1,
    OBJ_IS_FORWARDING_REFR  = 2,
};

enum {
    BUCKET_UNUSED,
    BUCKET_CLEARED,
    BUCKET_USED
};

#define OBJECT_HEAD \
  ObjectType *type;\
  Object *forwarding_refr;\
  u8 flags

struct Object {
  OBJECT_HEAD;
};

struct ObjectType {

    OBJECT_HEAD;

    char *name;
    u32   size;

    /* Methods */

    Object *methods;
    void    (*free)(Object *self);
    void    (*init)(Object *self, Object **argv, u32 argc);
    char    (*insert)(Object *self, Object *key, Object *value);
    Object *(*select)(Object *self, Object *key);
    void    (*setAttr)(Object *self, char *name, Object *value);
    Object *(*getAttr)(Object *self, char *name);
    Object *(*call)(Object *self, Object *parent, Object **argv, u32 argc);

    void  (*print)(Object *self);

    /* Casters */

    char (*to_cbool)(Object*);

    /* For operations */

    u32 expid;

    /* Garbage collector */

    void (*collectChildren)(Object *self);

};

struct ObjectBool {
  OBJECT_HEAD;
  char value;
};

struct ObjectFunction {
  OBJECT_HEAD;
  Offset offset;
};

struct ObjectInt {
  OBJECT_HEAD;
  i64 value;
};

struct ObjectFloat {
  OBJECT_HEAD;
  f64 value;
};

struct ObjectStringValue {
  OBJECT_HEAD;
  char value[];
};

struct ObjectString {
  OBJECT_HEAD;
  char *value;
  u32 size, hash;
};

struct ObjectBucket {
  OBJECT_HEAD;
  char name[16];
  u8 state;
  Object *ref;
};

struct ObjectBuckets {
  OBJECT_HEAD;
  ObjectBucket array[];
};

struct ObjectDict {
  OBJECT_HEAD;
  ObjectBucket *buckets;
  u32 size, used;
};

struct ObjectModule {
  OBJECT_HEAD;
  Object *members;
};

struct ObjectCFunction {
  OBJECT_HEAD;
  Object *(*call)(Object *parent, Object **argv, u32 argc);
};

struct ObjectArray {
  OBJECT_HEAD;
  Object **block;
  u32 size, used;
};

struct ObjectIstance {
  OBJECT_HEAD;
  Object *members;
};

extern ObjectType TypeTable_ObjectType;
extern ObjectType TypeTable_ObjectInt;
extern ObjectType TypeTable_ObjectFloat;
extern ObjectType TypeTable_ObjectString;
extern ObjectType TypeTable_Dict;
extern ObjectType TypeTable_Buckets;
extern ObjectType TypeTable_ObjectArray;
extern ObjectType TypeTable_ObjectFunction;
extern ObjectType TypeTable_ObjectCFunction;
extern ObjectType TypeTable_Module;
extern ObjectType TypeTable_ObjectBool;
extern Object *NOJA_True;
extern Object *NOJA_False;

char return_1(Object *o);
void    Object_destroy(Object *self);
Object *Object_create(ObjectType *type, Object **argv, u32 argc);
char    Object_isCallable(Object *self);
Offset  Object_stdCall(Object *self);
Object *Object_call(Object *self, Object *parent, Object **argv, u32 argc);
u32     Object_size(Object *self);
void    Object_setAttr(Object *self, char *name, Object *value);
Object *Object_getAttr(Object *self, char *name);
char    Object_insert(Object *self, Object *key, Object *value);
Object *Object_select(Object *self, Object *key);
void    Object_collectChildren(Object *self);
char    Object_to_cbool(Object *self);
Object *Object_eql(Object *a, Object *b);
Object *Object_lss(Object *a, Object *b);
Object *Object_grt(Object *a, Object *b);
Object *Object_leq(Object *a, Object *b);
Object *Object_geq(Object *a, Object *b);
Object *Object_add(Object *a, Object *b);
Object *Object_sub(Object *a, Object *b);
Object *Object_mul(Object *a, Object *b);
Object *Object_div(Object *a, Object *b);
void    Object_print(Object *a);

/* === Dict === */

void    Dict_collectChildren(Object *self);
void    Dict_init(Object *self, Object **argv, u32 argc);
u32     Dict_chash(char *string);
void    Dict_cinsert(Object *object, char *name, Object *child);
Object *Dict_cselect(Object *object, char *name);
void    Dict_cremove(Object *object, char *name);
char    Dict_to_cbool(Object *self);
void    Dict_print(Object *self);
char    Dict_insert(Object *self, Object *key, Object *value);
Object *Dict_select(Object *self, Object *key);
void    Dict_destroy(Object *self);

/* === ObjectInt === */

Object *ObjectInt_from_cint(i64 n);
void    ObjectInt_print(Object *self);
char    ObjectInt_to_cbool(Object *self);

/* === ObjectFloat === */

Object *ObjectFloat_from_cdouble(f64 n);
void    ObjectFloat_print(Object *self);
char    ObjectFloat_to_cbool(Object *self);

/* === ObjectString === */

void ObjectString_init(Object *self, Object *argv, u32 argc);
Object *ObjectString_from_cstring(char *s);
Object *ObjectString_wrap_cstring(char *value, u32 size);
void    ObjectString_print(Object *self);
char    ObjectString_to_cbool(Object *self);
void    ObjectString_collectChildren(Object *self);
void    ObjectString_destroy(Object *self);
char    ObjectString_insert(Object *self, Object *key, Object *value);
Object *ObjectString_select(Object *self, Object *key);

/* Methods */

Object *ObjectString_reverse(Object *parent, Object **argv, u32 agc);
Object *ObjectString_sub(Object *parent, Object **argv, u32 argc);
Object *ObjectString_find(Object *parent, Object **argv, u32 argc);
Object *ObjectString_length(Object *parent, Object **argv, u32 argc);
Object *ObjectString_split(Object *parent, Object **argv, u32 argc);
Object *ObjectString_replace(Object *parent, Object **argv, u32 argc);
Object *ObjectString_format(Object *parent, Object **argv, u32 argc);

/* === ObjectType === */

void    ObjectType_print(Object *self);
void    ObjectType_collectChildren(Object *self);
Object *ObjectType_call(Object *self, Object *parent, Object **argv, u32 argc);
Object *ObjectType_from_stackd(ObjectType *e_type);


/* === ObjectArray === */

void    ObjectArray_init(Object *self, Object **argv, u32 argc);
void    ObjectArray_destroy(Object *self);
void    ObjectArray_resize(Object *self);
void    ObjectArray_collectChildren(Object *self);
char    ObjectArray_to_cbool(Object *self);
void    ObjectArray_print(Object *self);
Object *ObjectArray_select(Object *self, Object *key);
char    ObjectArray_insert(Object *self, Object *key, Object *value);
Object *ObjectArray_cselect(Object *self, u32 i);
char    ObjectArray_cinsert(Object *self, u32 i, Object *value);
Object *ObjectArray_append(Object *parent, Object **argv, u32 argc);
Object *ObjectArray_pop(Object *parent, Object **argv, u32 argc);
Object *ObjectArray_reverse(Object *parent, Object **argv, u32 argc);
Object *ObjectArray_size(Object *parent, Object **argv, u32 argc);

/* === ObjectFunction === */

Object *ObjectFunction_call(Object *self, Object *parent, Object **argv, u32 argc);
Object *ObjectFunction_create(u32 addr, Source *source);

/* === ObjectCFunction === */

Object *ObjectCFunction_create(Object *(*call)(Object *parent, Object **argv, u32 argc));
Object *ObjectCFunction_call(Object *self, Object *parent, Object **argv, u32 argc);

/* === ObjectBool === */

void ObjectBool_print(Object *self);
char ObjectBool_to_cbool(Object *self);

/* === Module === */

Object *Module_getAttr(Object *self, char *s);
void    Module_setAttr(Object *self, char *s, Object *child);
void    Module_print(Object *self);
void    Module_collectChildren(Object *self);
void    Module_init(Object *self, Object **argv, u32 argc);

/* === Class === */

Object *Class_getAttr(Object *self, char *key);
void    Class_setAttr(Object *self, char *key, Object *value);
void    Class_init(Object *self, Object **argv, u32 argc);
Object *Class_call(Object *self, Object **argv, u32 argc);
void    Class_print(Object *self);
void    Class_collectChildren(Object *self);
void    Class_delete(Object *self);
Object *Class_select(Object *self, Object *key);
char Class_insert(Object *self, Object *key, Object *value);


/* === Operations === */

Object *Dict_eql(Object *a, Object *b);
Object *ObjectArray_eql(Object *a, Object *b);
Object *ObjectInt_eql(Object *a, Object *b);
Object *ObjectFloat_eql(Object *a, Object *b);
Object *ObjectString_eql(Object *a, Object *b);

// int R int

Object *ObjectInt_add(Object *a, Object *b);
Object *ObjectInt_sub(Object *a, Object *b);
Object *ObjectInt_mul(Object *a, Object *b);
Object *ObjectInt_div(Object *a, Object *b);
Object *ObjectInt_lss(Object *a, Object *b);
Object *ObjectIntObjectFloat_lss(Object *a, Object *b);
Object *ObjectInt_leq(Object *a, Object *b);
Object *ObjectIntObjectFloat_leq(Object *a, Object *b);
Object *ObjectInt_grt(Object *a, Object *b);
Object *ObjectIntObjectFloat_grt(Object *a, Object *b);
Object *ObjectInt_geq(Object *a, Object *b);
Object *ObjectIntObjectFloat_geq(Object *a, Object *b);

// float R float

Object *ObjectFloat_div(Object *a, Object *b);
Object *ObjectFloat_mul(Object *a, Object *b);
Object *ObjectFloat_sub(Object *a, Object *b);
Object *ObjectFloat_add(Object *a, Object *b);
Object *ObjectFloat_lss(Object *a, Object *b);
Object *ObjectFloatObjectInt_lss(Object *a, Object *b);
Object *ObjectFloat_grt(Object *a, Object *b);
Object *ObjectFloatObjectInt_grt(Object *a, Object *b);
Object *ObjectFloat_leq(Object *a, Object *b);
Object *ObjectFloatObjectInt_leq(Object *a, Object *b);
Object *ObjectFloat_geq(Object *a, Object *b);
Object *ObjectFloatObjectInt_geq(Object *a, Object *b);

// string R string
Object *ObjectString_add(Object *a, Object *b);


/* === Builtins === */

Object *typename_of(Object *parent, Object **argv, u32 argc);
Object *proto_attributes_of(Object *parent, Object **argv, u32 argc);

/* === Runtime === */

enum {
    BLOCK_WHILE,
    BLOCK_FUNC
};

typedef struct Context Context;
typedef struct ContextBlock ContextBlock;
typedef struct ActivationRecord ActivationRecord;

struct ContextBlock {
    u8 type;
    u32 beg, end;
};

struct ActivationRecord {
    Object *self;
    Object *args[32];
    u32 top, bot;
};


u8 ctx_read_u8(Context *context);
u16 ctx_read_u16(Context *context);
u32 ctx_read_u32(Context *context);
u64 ctx_read_u64(Context *context);
i8 ctx_read_i8(Context *context);
i16 ctx_read_i16(Context *context);
i32 ctx_read_i32(Context *context);
i64 ctx_read_i64(Context *context);
f32 ctx_read_f32(Context *context);
f64 ctx_read_f64(Context *context);
char *ctx_read_string(Context *context);
void ctx_push_self(Context *context, Object *object);
void ctx_create_activation_record(Context *context);
void ctx_push_argument(Context *context, Object *object);
void ctx_assign_argument(Context *context, char *name);
Object *ctx_pop(Context *context);
void ctx_pops(Context *context, int n);
void ctx_push(Context *context, Object *object);
Object *ctx_top(Context *context);
void ctx_call_pending(Context *context);
void ctx_throw_exception(Context *context, int exception_code);

typedef union {
  u8  _u8;
  u16 _u16;
  u32 _u32;
  u64 _u64;
  i8  _i8;
  i16 _i16;
  i32 _i32;
  i64 _i64;
  f32 _f32;
  f64 _f64;
  char * _str;
  Object *_obj;
  ObjectModule *_module;
} Register;

struct Context {

  ActivationRecord activation_records[16];
  u32 activation_records_count;

  Source *source_stack[128];
  u32 source_depth;

  ContextBlock blocks[128];
  u32 block_depth;

  Object *stack[128];
  u32 stack_size;

  Object *frames[128];
  u32 frame_depth;

  Object *root_frame;

  Object **roots[128];
  u32 root_count;

  u32 pc;
  u32 lineno;
  Offset pending_call_offset;

  int exception_code;
};

enum {
  Exception_None,
  Exception_ImportFailed,
  Exception_AttributeError,
  Exception_SetAttributeError,
  Exception_IndexError,
  Exception_ValueError,
  Exception_TypeError,
  Exception_OutOfMemory,
  Exception_UncallableCalled,
  Exception_NameError,
  Exception_InsertError,
  Exception_SelectError,
  Exception_badOperation,
  InternalException_0 = 21, // FUNC_END not in function
  InternalException_1, // PUSH_ARG on an empty stack
  InternalException_2, // INSERT with not enough elements on the stack
  InternalException_3, // Building array of size greather of the stack size
  InternalException_4, // JIFTP on empty stack
  InternalException_5, // JIFFP on empty stack
  InternalException_6, // PRINT on empty stack
  InternalException_7, // TYPE on empty stack
  InternalException_8, // TYPE_NAME on empty stack
  InternalException_9, // Operation on stack with size < 2
  InternalException_10, // Unknown opcode
  InternalException_11, // Invalid address
};

extern Source sources[128];
extern u32 source_count;

extern Context context;

extern char *code_stack[128];
extern u32 code_stack_size;

void NOJA_run();

char Sources_load(char *path);
void Sources_unload_all();