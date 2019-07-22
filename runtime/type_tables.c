
#include "header.h"

ObjectType TypeTable_ObjectType = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Type",
    .size = sizeof(ObjectType),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = &ObjectType_call,
    .print  = &ObjectType_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 1,
    .to_cbool = &return_1,
    .collectChildren = &ObjectType_collectChildren
};

ObjectType TypeTable_ObjectIterator = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Iterator",
    .size = sizeof(ObjectIterator),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = &ObjectIterator_init,
    .call   = 0,
    .print  = &ObjectIterator_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 1,
    .to_cbool = &return_1,
    .collectChildren = &ObjectIterator_collectChildren
};


ObjectType TypeTable_ObjectInt = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Int",
    .size = sizeof(ObjectInt),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectInt_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 2,
    .to_cbool = &ObjectInt_to_cbool,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectFloat = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Float",
    .size = sizeof(ObjectFloat),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectFloat_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 3,
    .to_cbool = &ObjectFloat_to_cbool,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectString = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "String",
    .size = sizeof(ObjectString),
    .methods = 0,
    .free = &ObjectString_destroy,
    .select = &ObjectString_select,
    .insert = &ObjectString_insert,
    .init   = &ObjectString_init,
    .call   = 0,
    .print  = &ObjectString_print,
    .iter   = &ObjectString_iter,
    .next   = &ObjectString_next,
    .get_raw_repr = &ObjectString_get_raw_repr,
    .get_raw_repr_size = &ObjectString_get_raw_repr_size,
    .expid  = 4,
    .to_cbool = &ObjectString_to_cbool,
    .collectChildren = 0
};

ObjectType TypeTable_Dict = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Dict",
    .size = sizeof(ObjectDict),
    .methods = 0,
    .free = &Dict_destroy,
    .init   = &Dict_init,
    .call   = 0,
    .insert = &Dict_insert,
    .select = &Dict_select,
    .print  = &Dict_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 5,
    .to_cbool = &Dict_to_cbool,
    .collectChildren = &Dict_collectChildren
};

ObjectType TypeTable_ObjectArray = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Array",
    .size = sizeof(ObjectArray),
    .methods = 0,
    .free = &ObjectArray_destroy,
    .init   = &ObjectArray_init,
    .select = &ObjectArray_select,
    .insert = &ObjectArray_insert,
    .call   = 0,
    .print  = &ObjectArray_print,
    .iter = &ObjectArray_iter,
    .next = &ObjectArray_next,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 6,
    .to_cbool = &ObjectArray_to_cbool,
    .collectChildren = &ObjectArray_collectChildren
};

ObjectType TypeTable_ObjectBool = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Bool",
    .size = sizeof(ObjectBool),
    .methods = 0,
    .free = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectBool_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 7,
    .to_cbool = &ObjectBool_to_cbool,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectFunction = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Function",
    .size = sizeof(ObjectFunction),
    .methods = 0,
    .free = 0,
    .init   = 0,
    .call   = &ObjectFunction_call,
    .print  = 0,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 0,
    .to_cbool = &return_1,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectCFunction = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "CFunction",
    .size = sizeof(ObjectCFunction),
    .methods = 0,
    .free = 0,
    .init   = 0,
    .call   = &ObjectCFunction_call,
    .print  = 0,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 0,
    .to_cbool = &return_1,
    .collectChildren = 0
};

ObjectType TypeTable_Module = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name = "Module",
    .size = sizeof(ObjectModule),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .getAttr = &Module_getAttr,
    .setAttr = &Module_setAttr,
    .init = &Module_init,
    .call = 0,
    .print = &Module_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid = 0,
    .to_cbool = &return_1,
    .collectChildren = &Module_collectChildren
};

Object *NOJA_True = (Object*) &(ObjectBool) {
    .type = &TypeTable_ObjectBool,
    .flags = 0,
    .value = 1
};

Object *NOJA_False = (Object*) &(ObjectBool) {
    .type = &TypeTable_ObjectBool,
    .flags = 0,
    .value = 0
};
