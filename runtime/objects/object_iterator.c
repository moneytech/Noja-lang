
#include "../header.h"

ObjectType ptable_ObjectIterator = {
    .type = &ptable_ObjectType,
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
    .operators = 0,
    .to_cbool = &return_1,
    .collectChildren = &ObjectIterator_collectChildren
};

/* === Operators === */

/* === Handles === */

void ObjectIterator_init(Object *self, Object **argv, u32 argc) {

  assert(argc != 0);

  ObjectIterator *iterator = (ObjectIterator*) self;

  Object *iterated = argv[0];

  if(iterated->type->iter == NULL) {
    // object can't be iterated
    ctx_throw_exception(self->context, Exception_UniterableIterated);
    return;
  }

  iterator->iterated = iterated;
  iterator->index = NOJA_False;

  iterated->type->iter(iterated, (Object*) iterator);

}

Object *ObjectIterator_ended(Object *self, Object **argv, u32 argc) {
  return ((ObjectIterator*) self)->ended ? NOJA_True : NOJA_False;
}

Object *ObjectIterator_next(Object *self, Object **argv, u32 argc) {

  ObjectIterator *iterator = (ObjectIterator*) self;

  Object *object = iterator->iterated->type->next(iterator->iterated, self);

  return object;
}

Object *ObjectIterator_index(Object *self, Object **argv, u32 argc) {
  return ((ObjectIterator*) self)->index;
}

Object *ObjectIterator_iterated(Object *self, Object **argv, u32 argc) {
  return ((ObjectIterator*) self)->iterated;
}

void ObjectIterator_print(Object *self) {

  ObjectIterator *iterator = (ObjectIterator*) self;

  printf("<Iterator on %s>", iterator->iterated->type->name);

}

void ObjectIterator_collectChildren(Object *self) {

  ObjectIterator *iterator = (ObjectIterator*) self;

  Mem_collect(&iterator->iterated);
  Mem_collect(&iterator->index);

}

/* === Methods === */