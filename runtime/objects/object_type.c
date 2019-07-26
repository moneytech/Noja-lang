
#include "../header.h"

ObjectType ptable_ObjectType = {
    .type = &ptable_ObjectType,
    .flags = 0,
    .name  = "Type",
    .size = sizeof(ObjectType),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .getAttr = &ObjectType_getAttr,
    .setAttr = &ObjectType_setAttr,
    .init   = 0,
    .call   = &ObjectType_call,
    .print  = &ObjectType_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .operators = 0,
    .to_cbool = &return_1,
    .collectChildren = &ObjectType_collectChildren
};

/* === Handles === */

void ObjectType_setAttr(Object *self, char *s, Object *child) {

  ObjectType *type = (ObjectType*) self;

  Dict_cinsert(type->methods, s, child);

}

Object *ObjectType_getAttr(Object *self, char *s) {

  ObjectType *type = (ObjectType*) self;

  return Dict_cselect(type->methods, s);

}

void ObjectType_print(Object *self) {

    printf("<type %s>", ((ObjectType*) self)->name);
}


Object *ObjectType_call(Object *self, Object *parent, Object **argv, u32 argc) {

    // IMPORTANT: self could refer to a built-in stack-allocated type structure.
    // such structures don't contain references to the context (since they are 
    // shared between contexts).

    // Since parent could be null (it's not null only when the object is called
    // after the dot operator), the context reference can't be provided by parent.

    return Object_create(parent->context, (ObjectType*) self, argv, argc);
}

void ObjectType_collectChildren(Object *self) {

    ObjectType *type = (ObjectType*) self;

    Mem_collect(&type->methods);
}