
#include "../header.h"

ObjectTypeOperators object_string_operators = {
    .add = ObjectString_add,
    .sub = 0,
    .mul = 0,
    .div = 0,
    .eql = ObjectString_eql,
    .grt = 0,
    .lss = 0,
};

ObjectType ptable_ObjectString = {
    .type = &ptable_ObjectType,
    .flags = 0,
    .name  = "String",
    .size = sizeof(ObjectString),
    .methods = 0,
    .free = &ObjectString_destroy,
    .select = &ObjectString_select,
    .insert = &ObjectString_insert,
    .init   = &ObjectString_init,
    .call   = 0,
    .print  = &ObjectString_print,
    .iter   = &ObjectString_iter,
    .next   = &ObjectString_next,
    .get_raw_repr = &ObjectString_get_raw_repr,
    .get_raw_repr_size = &ObjectString_get_raw_repr_size,
    .operators = &object_string_operators,
    .to_cbool = &ObjectString_to_cbool,
    .collectChildren = 0
};

/* === Operators === */


Object *ObjectString_eql(Object *a, Object *b) {

  ObjectString *s1 = (ObjectString*) a,
         *s2 = (ObjectString*) b;

  if(s1->size != s2->size)

    return NOJA_False;

  for(int i = 0; i < s1->size; i++)

    if(s1->value[i] != s2->value[i])

      return NOJA_False;

  return NOJA_True;
}


Object *ObjectString_add(Object *a, Object *b) {

    ObjectString *a2, *b2, *c;

    a2 = (ObjectString*) a;
    b2 = (ObjectString*) b;

    c = (ObjectString*) Object_create(a->context, __ObjectString__, 0, 0);

    c->size = a2->size + b2->size;
    c->value = (char*) malloc(c->size+1);

    strcpy(c->value, a2->value);
    strcat(c->value, b2->value);

    return (Object*) c;
}


/* === Factory === */

Object *ObjectString_wrap_cstring(Context *context, char *value, u32 size) {

    ObjectString *string = (ObjectString*) Object_create(context, __ObjectString__, 0, 0);

    string->value = value;
    string->size  = size;

    return (Object*) string;
}


Object *ObjectString_from_cstring(Context *context, char *s) {

    ObjectString *string = (ObjectString*) Object_create(context, __ObjectString__, 0, 0);

    u32 len = strlen(s);

    string->value = malloc(len+1);
    string->size  = len;

    strcpy(string->value, s);

    return (Object*) string;
}

/* === Handles === */


void ObjectString_init(Object *self, Object **argv, u32 argc) {

}

void ObjectString_get_raw_repr(Object *self, void *addr, u32 max_size) {

  ObjectString *string = (ObjectString*) self;

  for(u32 i = 0; i < MIN(string->size, max_size); i++)
      ((char*) addr)[i] = string->value[i];

}

u32 ObjectString_get_raw_repr_size(Object *self) {
  return ((ObjectString*) self)->size;
}

void ObjectString_destroy(Object *self) {
    ObjectString *string = (ObjectString*) self;
    free(string->value);
}

void ObjectString_print(Object *self) {

    printf("%s", ((ObjectString*) self)->value);

}

char ObjectString_to_cbool(Object *self) {
    return ((ObjectString*) self)->size != 0;
}

Object *ObjectString_select(Object *self, Object *key) {

    if(key->type != __ObjectInt__) {
      ctx_throw_exception(self->context, Exception_TypeError);
      return 0;
    }

    ObjectString *string = (ObjectString*) self;
    ObjectInt    *index  = (ObjectInt*) key;

    char c[2];

    i64 i = index->value;

    if(i < 0) {

      i = string->size + i + 1;

      if(i < 0) {
        // index out of range
        return 0;
      }
    }

    c[0] = string->value[index->value];
    c[1] = 0;

    return ObjectString_from_cstring(self->context, c);
}

char ObjectString_insert(Object *self, Object *key, Object *value) {

    if(key->type != __ObjectInt__) {
      ctx_throw_exception(self->context, Exception_IndexError);
      return 0;
    }

    if(value->type != __ObjectString__) {
      ctx_throw_exception(self->context, Exception_TypeError);
      return 0;
    }

    ObjectString *string       = (ObjectString*) self,
                 *substring    = (ObjectString*) value;
    ObjectInt    *index        = (ObjectInt*)    key;

    if(index->value >= string->size) {
      ctx_throw_exception(self->context, Exception_IndexError);
      return 0;
    }

    u32   new_length = string->size + substring->size - 1;
    char *new_value  = malloc(new_length + 1);

    u32    n = index->value;
    char *s1 = string->value;
    char *s2 = substring->value;

    for(u32 i = 0; i < n; i++)
        new_value[i] = s1[i];

    for(u32 i = 0; i < substring->size; i++)
        new_value[i + n] = s2[i];

    for(u32 i = 0; i < string->size - n; i++) {

        new_value[i + n + substring->size] = s1[i + n + 1];

    }

    free(string->value);

    string->value = new_value;
    string->size  = new_length;

    return 1;
}

void ObjectString_iter(Object *self, Object *iter) {


  ObjectString *string = (ObjectString*) self;
  ObjectIterator *iterator = (ObjectIterator*) iter;

}

Object *ObjectString_next(Object *self, Object *iter) {

  /*
    returning 0 will end the iteration
  */

  ObjectString *string = (ObjectString*) self;
  ObjectIterator *iterator = (ObjectIterator*) iter;

  i64 index;

  if(iterator->ended == 1)
    return NOJA_False;

  if(iterator->index->type == __ObjectInt__) {

    index = ((ObjectInt*) iterator->index)->value + 1;

  } else {

    index = 0;

  }

  char buffer[2];

  buffer[0] = string->value[index];
  buffer[1] = 0;

  iterator->index = ObjectInt_from_cint(self->context, index);

  if(index+1 == string->size)
    iterator->ended = 1;

  return ObjectString_from_cstring(self->context, buffer);

}

/* === Methods === */

Object *ObjectString_reverse(Object *parent, Object **argv, u32 argc) {
  return 0;
}

Object *ObjectString_findAll(Object *parent, Object **argv, u32 argc) {
  return 0;
}


Object *ObjectString_sub(Object *self, Object **argv, u32 argc) {

  int from, to;

  if(argc == 0) {
    // meh
    return NOJA_False;
  }

  char *source = ((ObjectString*) self)->value;

  if(argv[0]->type != __ObjectInt__) {
    ctx_throw_exception(self->context, Exception_TypeError);
    return 0;
  }

  from = ((ObjectInt*) argv[0])->value;

  if(argc == 2) {

    if(argv[1]->type != __ObjectInt__) {
      ctx_throw_exception(self->context, Exception_TypeError);
      return 0;
    }

    to = ((ObjectInt*) argv[1])->value;

    if(to < 0) {
      to = ((ObjectString*) self)->size + to + 1;
    }

  } else {

    to = ((ObjectString*) self)->size - 1;

  }

  if(to <= from) {

    // return empty string

    return ObjectString_from_cstring(self->context, "");

  }

  char *sub = malloc(to - from + 1); // +1?

  strncpy(sub, source + from, to - from + 1);

  sub[to-from] = 0;

  return ObjectString_wrap_cstring(self->context, sub, from - to + 1);

}

Object *ObjectString_find(Object *self, Object **argv, u32 argc) {

  if(argc == 0)
    return ObjectInt_from_cint(self->context, -1);

  if(argv[0]->type != __ObjectString__) {
    ctx_throw_exception(self->context, Exception_TypeError);
    return 0;
  }

  char *needle = ((ObjectString*) argv[0])->value;
  char *text   = ((ObjectString*) self)->value;
  int   needle_len = ((ObjectString*) argv[0])->size;
  int   text_len = ((ObjectString*) self)->size;

  if(needle_len >= text_len)

    return ObjectInt_from_cint(self->context, -1);

  int index = -1;

  for(int i = 0, j = 0; i < text_len; i++) {

    if(text[i] == needle[j]) {

      if(j == 0) index = i;

      j++;

      if(j == needle_len) {

        break;

      }

    } else {

      j = 0;

    }

  }

  return ObjectInt_from_cint(self->context, index);
}

Object *ObjectString_length(Object *self, Object **argv, u32 argc) {
  return ObjectInt_from_cint(self->context, ((ObjectString*) self)->size);
}

Object *ObjectString_split(Object *self, Object **argv, u32 argc) {

  /* Not tested */

  char *source = ((ObjectString*) self)->value;
  char *needle = ((ObjectString*) argv[0])->value;
  int   source_len = ((ObjectString*) self)->size;
  int   needle_len = ((ObjectString*) argv[0])->size;

  int i = 0;
  char c;

  char *buffer = malloc(1024);
  int buffer_size = 1024;
  int buffer_used = 0;
  char was_needle;

  Object *array = Object_create(self->context, __ObjectArray__, 0, 0);

  while(1) {

    c = source[i];

    if(c == needle[0] && source_len - i >= needle_len) { // > ?

      was_needle = 1;

      for(int j = 0; j < needle_len; j++) {
        if(source[i + j] != needle[j]) {
          was_needle = 0;
          break;
        }
      }

      if(was_needle) {

        ObjectArray_append(array, (Object*[]) {ObjectString_wrap_cstring(self->context, buffer, buffer_used)}, 1);

        buffer = (char*) malloc(buffer_size);
        buffer_used = 0;

        i += needle_len; // -1?

      } else {

        assert(buffer_size > buffer_used);

        buffer[buffer_used++] = c;

      }

      // needle maybe started

    } else {

      assert(buffer_size > buffer_used);

      buffer[buffer_used++] = c;
    }

    i++;
  }


  return array;
}

Object *ObjectString_replace(Object *self, Object **argv, u32 argc) {
  return 0;
}

Object *ObjectString_format(Object *self, Object **argv, u32 argc) {
  return 0;
}
