
#include "header.h"

ObjectType TypeTable_ObjectType = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectType",
    .size = sizeof(ObjectType),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = &ObjectType_call,
    .print  = &ObjectType_print,
    .expid  = 1,
    .to_cbool = &return_1,
    .collectChildren = &ObjectType_collectChildren
};

ObjectType TypeTable_ObjectInt = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectInt",
    .size = sizeof(ObjectInt),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectInt_print,
    .expid  = 2,
    .to_cbool = &ObjectInt_to_cbool,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectFloat = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectFloat",
    .size = sizeof(ObjectFloat),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectFloat_print,
    .expid  = 3,
    .to_cbool = &ObjectFloat_to_cbool,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectString = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectString",
    .size = sizeof(ObjectString),
    .methods = 0,
    .free = &ObjectString_destroy,
    .select = &ObjectString_select,
    .insert = &ObjectString_insert,
    .init   = &ObjectString_init,
    .call   = 0,
    .print  = &ObjectString_print,
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
    .expid  = 5,
    .to_cbool = &Dict_to_cbool,
    .collectChildren = &Dict_collectChildren
};

ObjectType TypeTable_ObjectArray = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectArray",
    .size = sizeof(ObjectArray),
    .methods = 0,
    .free = &ObjectArray_destroy,
    .init   = &ObjectArray_init,
    .select = &ObjectArray_select,
    .insert = &ObjectArray_insert,
    .call   = 0,
    .print  = &ObjectArray_print,
    .expid  = 6,
    .to_cbool = &ObjectArray_to_cbool,
    .collectChildren = &ObjectArray_collectChildren
};

ObjectType TypeTable_ObjectBool = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectBool",
    .size = sizeof(ObjectBool),
    .methods = 0,
    .free = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectBool_print,
    .expid  = 7,
    .to_cbool = &ObjectBool_to_cbool,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectFunction = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectFunction",
    .size = sizeof(ObjectFunction),
    .methods = 0,
    .free = 0,
    .init   = 0,
    .call   = &ObjectFunction_call,
    .print  = 0,
    .expid  = 0,
    .to_cbool = &return_1,
    .collectChildren = 0
};

ObjectType TypeTable_ObjectCFunction = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "ObjectCFunction",
    .size = sizeof(ObjectCFunction),
    .methods = 0,
    .free = 0,
    .init   = 0,
    .call   = &ObjectCFunction_call,
    .print  = 0,
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
