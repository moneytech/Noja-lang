
#include "header.h"

Object *bi_exit(Object *parent, Object **argv, u32 argc) {
  ctx_throw_exception(&context, Exception_ExplicitAbort);
  return NOJA_False;
}

Object *typename_of(Object *parent, Object **argv, u32 argc) {

  if(argc == 0)
    return NOJA_False;

  return ObjectString_from_cstring(argv[0]->type->name);

}

Object *proto_attributes_of(Object *parent, Object **argv, u32 argc) {

  Object *array = Object_create(__ObjectArray__, 0, 0);

  if(argc == 0)
    return array;

  if(argv[0]->type->methods == 0)
    return array;

  ObjectDict *dict;

  dict = (ObjectDict*) argv[0]->type->methods;

  Object *temp;

  for(u32 i = 0; i < dict->size; i++) {

      if(dict->buckets[i].state == BUCKET_USED) {

        temp = ObjectString_from_cstring(dict->buckets[i].name);

        ObjectArray_append(array, &temp, 1);
      }
  }

  return array;
}
