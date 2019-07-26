
#include "../header.h"

ObjectTypeOperators object_int_operators = {
    .add = ObjectInt_add,
    .sub = ObjectInt_sub,
    .mul = ObjectInt_mul,
    .div = ObjectInt_div,
    .eql = ObjectInt_eql,
    .grt = ObjectInt_grt,
    .lss = ObjectInt_lss,
};

ObjectType ptable_ObjectInt = {
    .type = &ptable_ObjectType,
    .flags = 0,
    .name  = "Int",
    .size = sizeof(ObjectInt),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectInt_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = &ObjectInt_get_raw_repr,
    .get_raw_repr_size = &ObjectInt_get_raw_repr_size,
    .operators = &object_int_operators,
    .to_cbool = &ObjectInt_to_cbool,
    .collectChildren = 0
};

/* === Operators === */

Object *ObjectInt_eql(Object *a, Object *b) {

    return ((ObjectInt*) a)->value == ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;

}

Object *ObjectInt_grt(Object *a, Object *b) {

    return ((ObjectInt*) a)->value > ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;

}

Object *ObjectInt_lss(Object *a, Object *b) {

    return ((ObjectInt*) a)->value < ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;

}


Object *ObjectInt_add(Object *a, Object *b) {

    ObjectInt *a2, *b2;

    a2 = (ObjectInt*) a;
    b2 = (ObjectInt*) b;

    ObjectInt *result = (ObjectInt*) Object_create(a->context, __ObjectInt__, 0, 0);


    result->value = a2->value + b2->value;

    return (Object*) result;
}

Object *ObjectInt_sub(Object *a, Object *b) {

    ObjectInt *a2, *b2;

    a2 = (ObjectInt*) a;
    b2 = (ObjectInt*) b;

    ObjectInt *result = (ObjectInt*) Object_create(a->context, __ObjectInt__, 0, 0);

    i64 v1, v2;

    v1 = a2->value;
    v2 = b2->value;

    result->value = v1 - v2;

    return (Object*) result;
}


Object *ObjectInt_mul(Object *a, Object *b) {

    ObjectInt *a2, *b2;

    a2 = (ObjectInt*) a;
    b2 = (ObjectInt*) b;

    ObjectInt *result = (ObjectInt*) Object_create(a->context, __ObjectInt__, 0, 0);

    result->value = a2->value * b2->value;

    return (Object*) result;
}

Object *ObjectInt_div(Object *a, Object *b) {

    ObjectInt *a2, *b2;

    a2 = (ObjectInt*) a;
    b2 = (ObjectInt*) b;

    ObjectInt *result = (ObjectInt*) Object_create(a->context, __ObjectInt__, 0, 0);

    result->value = a2->value / b2->value;

    return (Object*) result;
}

/* === Factory functions === */

Object *ObjectInt_from_cint(Context *context, i64 n) {

    ObjectInt *i = (ObjectInt*) Object_create(context, __ObjectInt__, 0, 0);
    i->value = n;
    return (Object*) i;

}

/* === Handlers === */


void ObjectInt_get_raw_repr(Object *self, void *addr, u32 max_size) {

  ObjectInt *integer = (ObjectInt*) self;

  for(u32 i = 0; i < MIN(sizeof(i64), max_size); i++)
      ((char*) addr)[i] = ((char*) &integer->value)[i];

}

u32 ObjectInt_get_raw_repr_size(Object *self) {
  
  return sizeof(i64);

}


void ObjectInt_print(Object *self) {

    printf("%ld", ((ObjectInt*) self)->value);

}

char ObjectInt_to_cbool(Object *self) {

    return ((ObjectInt*) self)->value != 0;

}

/* === Methods === */

// none