
#include "../header.h"

ObjectTypeOperators object_array_operators = {
    .add = 0,
    .sub = 0,
    .mul = 0,
    .div = 0,
    .eql = ObjectArray_eql,
    .grt = 0,
    .lss = 0,
};

ObjectType ptable_ObjectArray = {
    .type = &ptable_ObjectType,
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
    .operators = &object_array_operators,
    .to_cbool = &ObjectArray_to_cbool,
    .collectChildren = &ObjectArray_collectChildren
};

/* === Operators === */


Object *ObjectArray_eql(Object *a, Object *b) {

  ObjectArray *a1 = (ObjectArray*) a,
        *a2 = (ObjectArray*) b;

  if(a1->used != a2->used)
    return NOJA_False;

  for(int i = 0; i < a1->used; i++)

    if(Object_eql(a1->block[i], a2->block[i]) == NOJA_False)
      return NOJA_False;

  return NOJA_True;
}

/* === C Handles === */


char ObjectArray_cinsert(Object *self, u32 index, Object *elem) {

    ObjectArray *array = (ObjectArray*) self;

    if(array->used <= index) {

        // Exception: Index out of range

        ctx_throw_exception(self->context, Exception_IndexError);

        return 0;
    }

    array->block[index] = elem;

    return 1;
}

Object *ObjectArray_cselect(Object *self, u32 index) {

    ObjectArray *array = (ObjectArray*) self;

    if(array->used <= index) {

        // Exception: Index out of range

        ctx_throw_exception(self->context, Exception_IndexError);

        return 0;
    }

    return array->block[index];
}

/* === Handles === */

void ObjectArray_iter(Object *self, Object *iter) {

  ObjectArray *array = (ObjectArray*) self;
  ObjectIterator *iterator = (ObjectIterator*) iter;


}

Object *ObjectArray_next(Object *self, Object *iter) {

  ObjectArray *array = (ObjectArray*) self;
  ObjectIterator *iterator = (ObjectIterator*) iter;

  i64 index;

  if(iterator->ended)
    return NOJA_False;

  if(iterator->index->type == __ObjectInt__) {

    index = ((ObjectInt*) iterator->index)->value + 1;

  } else {

    index = 0;

  }

  iterator->index = ObjectInt_from_cint(self->context, index);

  Object *object = array->block[index];

  if(index+1 == array->used)
    iterator->ended = 1;

  return object;
}

char ObjectArray_to_cbool(Object *self) {
    return ((ObjectArray*) self)->used;
}

void ObjectArray_print(Object *self) {

    ObjectArray *array = (ObjectArray*) self;

    printf("[");

    for(u32 i = 0; i < array->used; i++) {

        Object_print(array->block[i]);
        //printf("%p", array->block[i]);
        if(i < array->used-1)
            printf(", ");

    }


    printf("]");
}

void ObjectArray_init(Object *self, Object **argv, u32 argc) {

    ObjectArray *array = (ObjectArray*) self;

    array->block = malloc(sizeof(Object*)*10);
    memset(array->block, 0, sizeof(Object*)*10);
    array->size  = 10;

}

void ObjectArray_destroy(Object *self) {

    ObjectArray *array = (ObjectArray*) self;

    free(array->block);
}

void ObjectArray_resize(Object *self) {

    ObjectArray *array = (ObjectArray*) self;

    u32 size = array->size * 2;

    Object **block = malloc(sizeof(Object*)*size);

    memcpy(block, array->block, array->used*sizeof(Object*));

    free(array->block);

    array->block = block;
    array->size  = size;

}

void ObjectArray_collectChildren(Object *self) {

    ObjectArray *array = (ObjectArray*) self;

    for(u32 i = 0; i < array->used; i++)
        Mem_collect(&array->block[i]);

}

char ObjectArray_insert(Object *self, Object *key, Object *value) {

    return ObjectArray_cinsert(self, ((ObjectInt*) key)->value, value);

}

Object *ObjectArray_select(Object *self, Object *key) {

    return ObjectArray_cselect(self, ((ObjectInt*) key)->value);

}

/* === Methods === */

Object *ObjectArray_pop(Object *parent, Object **argv, u32 argc) {

    Object *self = parent;

    ObjectArray *array = (ObjectArray*) self;

    if(array->used == 0)
        return NOJA_False;

    return array->block[--array->used];
}

Object *ObjectArray_size(Object *parent, Object **argv, u32 argc) {

    ObjectArray *array = (ObjectArray*) parent;

    return ObjectInt_from_cint(parent->context, array->used);
}

Object *ObjectArray_reverse(Object *parent, Object **argv, u32 argc) {

    ObjectArray *self = (ObjectArray*) parent;

    Object *reversed = Object_create(parent->context, __ObjectArray__, 0, 0);

    for(u32 i = self->used; i > 0; i--) {
       ObjectArray_append(reversed, (Object*[]) {self->block[i-1]}, 1);
    }

    return reversed;
}

Object *ObjectArray_append(Object *parent, Object **argv, u32 argc) {

    Object *self    = parent;
    Object *child   = argv[0];

    ObjectArray *array = (ObjectArray*) self;

    if(array->used == array->size)
        ObjectArray_resize(self);

    array->block[array->used] = child;

    array->used++;

    return self;
}