
#include "header.h"

Object *bi_exit(Object *parent, Object **argv, u32 argc) {

  // parent will always be null! There's no way the context address could get here!!

  ctx_throw_exception(parent->context, Exception_ExplicitAbort);
  return NOJA_False;
}

Object *typename_of(Object *parent, Object **argv, u32 argc) {

  if(argc == 0)
    return NOJA_False;

  return ObjectString_from_cstring(parent->context, argv[0]->type->name);

}

Object *prototype(Object *parent, Object **argv, u32 argc) {

  if(argc == 0)
    return NOJA_False;

  return (Object*) argv[0]->type;

}

Object *proto_attributes_of(Object *parent, Object **argv, u32 argc) {

  Object *array = Object_create(parent->context, __ObjectArray__, 0, 0);

  if(argc == 0)
    return array;

  if(argv[0]->type->methods == 0)
    return array;

  ObjectDict *dict;

  dict = (ObjectDict*) argv[0]->type->methods;

  Object *temp;

  for(u32 i = 0; i < dict->size; i++) {

      if(dict->buckets[i].state == BUCKET_USED) {

        temp = ObjectString_from_cstring(parent->context, dict->buckets[i].name);

        ObjectArray_append(array, &temp, 1);
      }
  }

  return array;
}
