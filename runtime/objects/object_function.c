
#include "../header.h"

ObjectType ptable_ObjectFunction = {
    .type = &ptable_ObjectType,
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
    .operators = 0,
    .to_cbool = &return_1,
    .collectChildren = 0
};

/* === Handles === */


Object *ObjectFunction_call(Object *self, Object *parent, Object **argv, u32 argc) {

    ObjectFunction *f = (ObjectFunction*) self;

    self->context->pending_call_offset = f->offset;

    return 0;
}

Object *ObjectFunction_create(Context *context, u32 addr, Source *source) {

    ObjectFunction *f = (ObjectFunction*) Object_create(context, __ObjectFunction__, 0, 0);
    f->offset.source = source;
    f->offset.addr   = addr;

    return (Object*) f;
}