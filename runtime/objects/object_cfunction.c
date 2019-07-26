
#include "../header.h"

ObjectType ptable_ObjectCFunction = {
    .type = &ptable_ObjectType,
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
    .operators = 0,
    .to_cbool = &return_1,
    .collectChildren = 0
};

/* === Handlers === */

Object *ObjectCFunction_call(Object *self, Object *parent, Object **argv, u32 argc) {

    return ((ObjectCFunction*) self)->call(parent, argv, argc);

}

Object *ObjectCFunction_create(Context *context, Object *(*call)(Object *parent, Object **argv, u32 argc)) {

    Object *o = Object_create(context, __ObjectCFunction__, 0, 0);

    ((ObjectCFunction*) o)->call = call;

    return o;
}
