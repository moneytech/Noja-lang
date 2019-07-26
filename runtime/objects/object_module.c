
#include "../header.h"

ObjectType ptable_ObjectModule = {
    .type = &ptable_ObjectType,
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
    .operators = 0,
    .to_cbool = &return_1,
    .collectChildren = &Module_collectChildren
};

/* === Handles === */


Object *Module_getAttr(Object *self, char *s) {

  ObjectModule *module = (ObjectModule*) self;

  return Dict_cselect(module->members, s);

}

void Module_setAttr(Object *self, char *s, Object *child) {

  // What to do here?

}

void Module_print(Object *self) {

  Object_print(((ObjectModule*) self)->members);

}

void Module_collectChildren(Object *self) {

  ObjectModule *module = (ObjectModule*) self;

  Mem_collect(&module->members);

}

void Module_init(Object *self, Object **argv, u32 argc) {

  ObjectModule *module = (ObjectModule*) self;

  module->members = Object_create(self->context, __ObjectDict__, 0, 0);

}
