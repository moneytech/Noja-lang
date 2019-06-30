
#include "header.h"

/* === Object === */

char return_1(Object *o) {
    return 1;
}

void Object_destroy(Object *self) {

    if(self->type->free) {
        self->type->free(self);
    }
}

Object *Object_create(ObjectType *type, Object **argv, u32 argc) {

    Object *object = (Object*) Mem_allocate(type->size);

    if(!object)
      return 0;

    object->flags |= OBJ_IS_GC_COLLECTABLE;
    object->type = type;

    if(type->init)

        type->init(object, argv, argc);

    return object;
}

Object *Object_call(Object *self, Object *parent, Object **argv, u32 argc) {

  if(!self->type->call) {
    ctx_throw_exception(&context, Exception_UncallableCalled);
    return 0;
  }

    return self->type->call(self, parent, argv, argc);
}

u32 Object_size(Object *self) {
    return self->type->size;
}

void Object_setAttr(Object *self, char *name, Object *value) {

    if(!self->type->setAttr) {


      ctx_throw_exception(&context, Exception_SetAttributeError);

      return;
    }

    self->type->setAttr(self, name, value);
}

Object *Object_getAttr(Object *self, char *name) {

    if(!self->type->getAttr) {

        if(!self->type->methods) {

          ctx_throw_exception(&context, Exception_AttributeError);

          return 0;

        }

        Object *value = Dict_cselect(self->type->methods, name);

        if(!value) {

          ctx_throw_exception(&context, Exception_AttributeError);

          return 0;

        }

        return value;
    }

    return self->type->getAttr(self, name);
}

char Object_insert(Object *self, Object *key, Object *value) {

    if(!self->type->insert) {

      ctx_throw_exception(&context, Exception_InsertError);

      return 0;
    }

    return self->type->insert(self, key, value);
}

Object *Object_select(Object *self, Object *key) {

    if(!self->type->select) {

      ctx_throw_exception(&context, Exception_SelectError);

      return 0;
    }

    return self->type->select(self, key);
}


void Object_collectChildren(Object *self) {

  if(self->type->flags & OBJ_IS_GC_COLLECTABLE)
    Mem_collect((Object**) &self->type);

    if(self->type->collectChildren) {

        self->type->collectChildren(self);

    }
}

char Object_to_cbool(Object *self) {

    if(!self->type->to_cbool) {

      ctx_throw_exception(&context, Exception_TypeError);

      return 0;
    }

    return self->type->to_cbool(self);
}

Object *Object_lss(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
      return 0;

    f = operator_matrix_lss[a->type->expid-1][b->type->expid-1];

    if(!f)
      return 0;

    return f(a, b);
}

Object *Object_grt(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_grt[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

Object *Object_eql(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_eql[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

Object *Object_leq(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_leq[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

Object *Object_geq(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_geq[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

Object *Object_add(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_add[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

Object *Object_sub(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_sub[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

Object *Object_mul(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_mul[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

Object *Object_div(Object *a, Object *b) {

    Operator f;

    if(a->type->expid == 0 || b->type->expid == 0)
        return 0;

    f = operator_matrix_div[a->type->expid-1][b->type->expid-1];

    if(!f)
        return 0;

    return f(a, b);
}

void Object_print(Object *a) {

    if(!a->type->print) {
        printf("<type %s is unprintable>", a->type->name);
        return;
    }

    a->type->print(a);
}

/* === ObjectType === */

void ObjectType_print(Object *self) {
    printf("<type %s>", ((ObjectType*) self)->name);
}


Object *ObjectType_call(Object *self, Object *parent, Object **argv, u32 argc) {

    return Object_create((ObjectType*) self, argv, argc);
}

void ObjectType_collectChildren(Object *self) {

    ObjectType *type = (ObjectType*) self;

    Mem_collect(&type->methods);
}

Object *ObjectType_from_stackd(ObjectType *e_type) {

  ObjectType *type = (ObjectType*) Object_create(__ObjectType__, 0, 0);

  memcpy(type, e_type, sizeof(ObjectType));

  type->flags &= OBJ_IS_GC_COLLECTABLE;

  return (Object*) type;
}

/* === Module === */

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

  module->members = Object_create(&TypeTable_Dict, argv, argc);

}


/* === ObjectString === */

void ObjectString_init(Object *self, Object *argv, u32 argc) {

}

Object *ObjectString_wrap_cstring(char *value, u32 size) {

    ObjectString *string = (ObjectString*) Object_create(__ObjectString__, 0, 0);

    string->value = value;
    string->size  = size;

    return (Object*) string;
}


Object *ObjectString_from_cstring(char *s) {

    ObjectString *string = (ObjectString*) Object_create(__ObjectString__, 0, 0);

    u32 len = strlen(s);

    string->value = malloc(len+1);
    string->size  = len;

    strcpy(string->value, s);

    return (Object*) string;
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

    if(key->type == &TypeTable_ObjectInt) {
      ctx_throw_exception(&context, Exception_TypeError);
      return 0;
    }

    ObjectString *string = (ObjectString*) self;
    ObjectInt *index = (ObjectInt*) key;

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

    return ObjectString_from_cstring(c);
}

char ObjectString_insert(Object *self, Object *key, Object *value) {

    ObjectString *string       = (ObjectString*) self,
                 *substring    = (ObjectString*) value;
    ObjectInt    *index        = (ObjectInt*)    key;

    u32   new_length = string->size + substring->size - 1;
    char *new_value = malloc(new_length+1);

    u32 n = index->value;
    char *s1 = string->value;
    char *s2 = substring->value;

    for(u32 i = 0; i < n; i++)
        new_value[i] = s1[i];

    for(u32 i = 0; i < substring->size; i++)
        new_value[i+n] = s2[i];

    for(u32 i = 0; i < string->size-(n+substring->size); i++)
        new_value[i+n+substring->size] = s1[i+n+1];

    free(string->value);

    string->value = new_value;
    string->size  = new_length;

    return 1;
}

Object *ObjectString_reverse(Object *parent, Object **argv, u32 argc) {}
Object *ObjectString_sub(Object *parent, Object **argv, u32 argc) {}
Object *ObjectString_find(Object *parent, Object **argv, u32 argc) {}

Object *ObjectString_length(Object *parent, Object **argv, u32 argc) {
  return ObjectInt_from_cint(((ObjectString*) parent)->size);
}

Object *ObjectString_split(Object *parent, Object **argv, u32 argc) {

  /* Not tested */

  char *source = ((ObjectString*) parent)->value;
  char *needle = ((ObjectString*) argv[0])->value;
  int   source_len = ((ObjectString*) parent)->size;
  int   needle_len = ((ObjectString*) argv[0])->size;

  int i = 0;
  char c;

  char *buffer = malloc(1024);
  int buffer_size = 1024;
  int buffer_used = 0;
  char was_needle;

  Object *array = Object_create(__ObjectArray__, 0, 0);

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

        ObjectArray_append(array, (Object*[]) {ObjectString_wrap_cstring(buffer, buffer_used)}, 1);

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

Object *ObjectString_replace(Object *parent, Object **argv, u32 argc) {}
Object *ObjectString_format(Object *parent, Object **argv, u32 argc) {}

/* === ObjectInt === */

void ObjectInt_print(Object *self) {
    printf("%ld", ((ObjectInt*) self)->value);
}

Object *ObjectInt_from_cint(i64 n) {
    ObjectInt *i = (ObjectInt*) Object_create(__ObjectInt__, 0, 0);
    i->value = n;
    return (Object*) i;
}

char ObjectInt_to_cbool(Object *self) {
    return ((ObjectInt*) self)->value != 0;
}

/* === ObjectFunction === */

Object *ObjectFunction_call(Object *self, Object *parent, Object **argv, u32 argc) {

    ObjectFunction *f = (ObjectFunction*) self;

    context.pending_call_offset = f->offset;

    return 0;
}

Object *ObjectFunction_create(u32 addr, Source *source) {

    ObjectFunction *f = (ObjectFunction*) Object_create(__ObjectFunction__, 0, 0);
    f->offset.source = source;
    f->offset.addr   = addr;

    return (Object*) f;
}

/* === ObjectFloat === */

void ObjectFloat_print(Object *self) {
    printf("%lf", ((ObjectFloat*) self)->value);
}

Object *ObjectFloat_from_cdouble(f64 n) {
    ObjectFloat *i = (ObjectFloat*) Object_create(__ObjectFloat__, 0, 0);
    i->value = n;
    return (Object*) i;
}

char ObjectFloat_to_cbool(Object *self) {
    return ((ObjectFloat*) self)->value != 0;
}

/* === Dictionary === */



void Dict_destroy(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    free(dict->buckets);
}

void Dict_print(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    printf("{");
    for(u32 i = 0, j = 0; i < dict->size; i++) {

        if(i == 0) printf("\n");

        if(dict->buckets[i].state == BUCKET_USED) {
            printf("%-20s: %s", dict->buckets[i].name, dict->buckets[i].ref->type->name);
            //Object_print(dict->buckets[i].ref);
            if(j < dict->used-1) {
                printf(", ");
            }
            printf("\n");
            j++;
        }
    }
    printf("}");
}

void Dict_collectChildren(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    for(u32 i = 0; i < dict->size; i++) {
        if(dict->buckets[i].state == BUCKET_USED) {
            Mem_collect(&dict->buckets[i].ref);
        }
    }
}

char Dict_to_cbool(Object *self) {
    return ((ObjectDict*) self)->used != 0;
}

void Dict_init(Object *self, Object **argv, u32 argc) {

    ObjectDict *dict = (ObjectDict*) self;

    dict->buckets = malloc(sizeof(ObjectBucket)*8);
    dict->size = 8;

    memset(dict->buckets, 0, sizeof(ObjectBucket)*8);

}

u32 Dict_chash(char *string) {

    char c;
    u32 i = 0, x = 0;

    while((c = string[i++]))
        x += c*c*i;

    return x;
}

char Dict_insert(Object *self, Object *key, Object *value) {

    Dict_cinsert(self, ((ObjectString*) key)->value, value);
    return 1;
}

void Dict_resize(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    ObjectBucket *old_buckets  = dict->buckets;
    u32        old_size     = dict->size;

    dict->buckets = calloc(dict->size*2, sizeof(ObjectBucket));
    dict->size *= 2;

    for(u32 i = 0; i < old_size; i++) {
        if(old_buckets[i].state == BUCKET_USED) {
            Dict_cinsert(self, old_buckets[i].name, old_buckets[i].ref);
        }
    }

    free(old_buckets);

}

void Dict_cinsert(Object *object, char *name, Object *child) {

    ObjectDict *dict = (ObjectDict*) object;

    if(dict->used == dict->size - 1)
        Dict_resize(object);

    char bucket_already_there = 0;

    u32 x = Dict_chash(name);
    u32 p = x;
    u32 i = x & (dict->size - 1);

    while(1) {

        if(dict->buckets[i].state == BUCKET_UNUSED) {

            // empty
            break;

        } else if(dict->buckets[i].state == BUCKET_CLEARED) {

            break;

        } else {

            // used

            if(strcmp(dict->buckets[i].name, name) == 0) {

                bucket_already_there = 1;
                // already here! Overwrite!
                // insert
                break;
            }
        }

        p >>= 1;
        i = (i*5 + p + 1) & (dict->size - 1);
    }

    dict->buckets[i].state = BUCKET_USED;
    strcpy(dict->buckets[i].name, name);
    dict->buckets[i].ref   = child;

    if(!bucket_already_there)
        dict->used++;
}

Object *Dict_select(Object *self, Object *key) {

    return Dict_cselect(self, ((ObjectString*) key)->value);
}

Object *Dict_cselect(Object *object, char *name) {

    ObjectDict *dict = (ObjectDict*) object;

    u32 x = Dict_chash(name);
    u32 p = x;
    u32 i = x & (dict->size - 1);

    while(1) {

        if(dict->buckets[i].state == BUCKET_UNUSED) {

            // empty
            return 0;

        } else {

            // used

            if(strcmp(dict->buckets[i].name, name) == 0) {

                // Found it!

                return dict->buckets[i].ref;
            }
        }

        p >>= 1;
        i = (i*5 + p + 1) & (dict->size - 1);
    }

    assert(0);
    /* Unreachable */
}

void Dict_cremove(Object *object, char *name) {

    ObjectDict *dict = (ObjectDict*) object;

    u32 x = Dict_chash(name);
    u32 p = x;
    u32 i = x & (dict->size - 1);

    while(1) {

        if(dict->buckets[i].state == BUCKET_UNUSED) {

            // empty
            return;

        } else {

            // used

            if(strcmp(dict->buckets[i].name, name) == 0) {

                // Found it!
                dict->buckets[i].name[0]  = 0;
                dict->buckets[i].state = BUCKET_CLEARED;
                dict->buckets[i].ref = 0;

                return;
            }
        }

        p >>= 1;
        i = (i*5 + p + 1) & (dict->size - 1);
    }

    assert(0);
    /* Unreachable */

}

/* === ObjectCFunction === */

Object *ObjectCFunction_call(Object *self, Object *parent, Object **argv, u32 argc) {

    return ((ObjectCFunction*) self)->call(parent, argv, argc);

}

Object *ObjectCFunction_create(Object *(*call)(Object *parent, Object **argv, u32 argc)) {

    Object *o = Object_create(__ObjectCFunction__, 0, 0);

    ((ObjectCFunction*) o)->call = call;

    return o;
}

/* === ObjectBool === */

char ObjectBool_to_cbool(Object *self) {

    ObjectBool *b = (ObjectBool*) self;

    return b->value;
}

void ObjectBool_print(Object *self) {

    ObjectBool *b = (ObjectBool*) self;

    printf("%s", b->value ? "true" : "false");
}

/* === ObjectArray === */


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

Object *ObjectArray_pop(Object *parent, Object **argv, u32 argc) {

    Object *self = parent;

    ObjectArray *array = (ObjectArray*) self;

    if(array->used == 0)
        return NOJA_False;

    return array->block[--array->used];
}

Object *ObjectArray_size(Object *parent, Object **argv, u32 argc) {

    ObjectArray *array = (ObjectArray*) parent;

    return ObjectInt_from_cint(array->used);
}

Object *ObjectArray_reverse(Object *parent, Object **argv, u32 argc) {

    ObjectArray *self = (ObjectArray*) parent;

    Object *reversed = Object_create(__ObjectArray__, 0, 0);

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

char ObjectArray_cinsert(Object *self, u32 index, Object *elem) {

    ObjectArray *array = (ObjectArray*) self;

    if(array->used <= index) {

        // Exception: Index out of range

        ctx_throw_exception(&context, Exception_IndexError);


        return 0;
    }

    array->block[index] = elem;

    return 1;
}

Object *ObjectArray_cselect(Object *self, u32 index) {

    ObjectArray *array = (ObjectArray*) self;

    if(array->used <= index) {

        // Exception: Index out of range

        ctx_throw_exception(&context, Exception_IndexError);

        return 0;
    }

    return array->block[index];
}

char ObjectArray_insert(Object *self, Object *key, Object *value) {

    return ObjectArray_cinsert(self, ((ObjectInt*) key)->value, value);
}

Object *ObjectArray_select(Object *self, Object *key) {

    return ObjectArray_cselect(self, ((ObjectInt*) key)->value);
}

/* === Class === */

void Class_delete(Object *self) {

}

Object *Class_select(Object *self, Object *key) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__select__");

  if(!method) {
    ctx_throw_exception(&context, Exception_AttributeError);
    return 0;
  }

  if(method->type != &TypeTable_ObjectFunction) {
    ctx_throw_exception(&context, Exception_TypeError);
    return 0;
  }

  ctx_create_activation_record(&context);
  ctx_push_self(&context, self);
  ctx_push_argument(&context, key);

  context.pending_call_offset = ((ObjectFunction*) method)->offset;

  return 0;
}

char Class_insert(Object *self, Object *key, Object *value) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__insert__");

  if(!method) {
    ctx_throw_exception(&context, Exception_AttributeError);
    return 0;
  }

  if(method->type != &TypeTable_ObjectFunction) {
    ctx_throw_exception(&context, Exception_TypeError);
    return 0;
  }

  ctx_create_activation_record(&context);
  ctx_push_self(&context, self);
  ctx_push_argument(&context, key);
  ctx_push_argument(&context, value);

  context.pending_call_offset = ((ObjectFunction*) method)->offset;

  return 1;
}

Object *Class_getAttr(Object *self, char *key) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *result = Dict_cselect(istance->members, key);

  if(!result)
    result = Dict_cselect(istance->type->methods, key);

  return result;
}

void Class_setAttr(Object *self, char *key, Object *value) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Dict_cinsert(istance->members, key, value);
}

void Class_init(Object *self, Object **argv, u32 argc) {

  ObjectIstance *istance = (ObjectIstance*) self;

  istance->members = Object_create(__ObjectDict__, 0, 0);

  Object *method = Dict_cselect(istance->type->methods, "__init__");

  if(!method) {
    ctx_throw_exception(&context, Exception_AttributeError);
    return;
  }

  if(method->type != &TypeTable_ObjectFunction) {
    ctx_throw_exception(&context, Exception_TypeError);
    return;
  }

  ctx_push_self(&context, self);

  context.pending_call_offset = ((ObjectFunction*) method)->offset;

}

Object *Class_call(Object *self, Object **argv, u32 argc) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__call__");

  if(!method) {
    ctx_throw_exception(&context, Exception_AttributeError);
    return 0;
  }

  if(method->type != &TypeTable_ObjectFunction) {
    ctx_throw_exception(&context, Exception_TypeError);
    return 0;
  }

  ctx_push_self(&context, self);

  context.pending_call_offset = ((ObjectFunction*) method)->offset;

  return 0;
}

void Class_print(Object *self) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__print__");

  if(!method) {
    ctx_throw_exception(&context, Exception_AttributeError);
    return;
  }

  if(method->type != &TypeTable_ObjectFunction) {
    ctx_throw_exception(&context, Exception_TypeError);
    return;
  }

  ctx_create_activation_record(&context);
  ctx_push_self(&context, self);

  context.pending_call_offset = ((ObjectFunction*) method)->offset;

}

void Class_collectChildren(Object *self) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Mem_collect(&istance->members);

}
