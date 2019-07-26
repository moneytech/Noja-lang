
#include "../header.h"

ObjectTypeOperators object_bool_operators = {
    .add = 0,
    .sub = 0,
    .mul = 0,
    .div = 0,
    .eql = ObjectBool_eql,
    .grt = 0,
    .lss = 0,
};

ObjectType ptable_ObjectBool = {
    .type = &ptable_ObjectType,
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
    .operators = &object_bool_operators,
    .to_cbool = &ObjectBool_to_cbool,
    .collectChildren = 0
};

Object *NOJA_True = (Object*) &(ObjectBool) {
    .type = &ptable_ObjectBool,
    .flags = 0,
    .value = 1
};

Object *NOJA_False = (Object*) &(ObjectBool) {
    .type = &ptable_ObjectBool,
    .flags = 0,
    .value = 0
};

char ObjectBool_to_cbool(Object *self) {

    ObjectBool *b = (ObjectBool*) self;

    return b->value;
}

void ObjectBool_print(Object *self) {

    ObjectBool *b = (ObjectBool*) self;

    printf("%s", b->value ? "true" : "false");
}

/* === Operators === */

Object *ObjectBool_eql(Object *a, Object *b) {
    // calling Bool() would create a new istance of a bool object, so pointer comparison wouldn't work.
    return a == b ? NOJA_True : NOJA_False;
}
