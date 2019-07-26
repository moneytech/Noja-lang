
#include "header.h"

Object *ObjectBool_eql(Object *a, Object *b) {
    // calling Bool() would create a new istance of a bool object, so pointer comparison wouldn't work.
    return a == b ? NOJA_True : NOJA_False;
}

Object *ObjectInt_eql(Object *a, Object *b) {
    return ((ObjectInt*) a)->value == ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloat_eql(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value == ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

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

Object *Dict_eql(Object *a, Object *b) {
    return NOJA_False;
}

Object *ObjectInt_lss(Object *a, Object *b) {
    return ((ObjectInt*) a)->value < ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloat_lss(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value < ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectIntObjectFloat_lss(Object *a, Object *b) {
    return ((ObjectInt*) a)->value < ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloatObjectInt_lss(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value < ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectInt_grt(Object *a, Object *b) {
    return ((ObjectInt*) a)->value > ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloat_grt(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value > ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectIntObjectFloat_grt(Object *a, Object *b) {
    return ((ObjectInt*) a)->value > ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloatObjectInt_grt(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value > ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectInt_leq(Object *a, Object *b) {
    return ((ObjectInt*) a)->value <= ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloat_leq(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value <= ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectIntObjectFloat_leq(Object *a, Object *b) {
    return ((ObjectInt*) a)->value <= ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloatObjectInt_leq(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value <= ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectInt_geq(Object *a, Object *b) {
    return ((ObjectInt*) a)->value >= ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloat_geq(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value >= ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectIntObjectFloat_geq(Object *a, Object *b) {
    return ((ObjectInt*) a)->value >= ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloatObjectInt_geq(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value >= ((ObjectInt*) b)->value ? NOJA_True : NOJA_False;
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


Object *ObjectFloat_add(Object *a, Object *b) {

    ObjectFloat *a2, *b2;

    a2 = (ObjectFloat*) a;
    b2 = (ObjectFloat*) b;

    ObjectFloat *result = (ObjectFloat*) Object_create(a->context, __ObjectFloat__, 0, 0);

    result->value = a2->value + b2->value;

    return (Object*) result;
}

Object *ObjectFloat_sub(Object *a, Object *b) {

    ObjectFloat *a2, *b2;

    a2 = (ObjectFloat*) a;
    b2 = (ObjectFloat*) b;

    ObjectFloat *result = (ObjectFloat*) Object_create(a->context, __ObjectFloat__, 0, 0);

    result->value = a2->value - b2->value;

    return (Object*) result;
}

Object *ObjectFloat_mul(Object *a, Object *b) {

    ObjectFloat *a2, *b2;

    a2 = (ObjectFloat*) a;
    b2 = (ObjectFloat*) b;

    ObjectFloat *result = (ObjectFloat*) Object_create(a->context, __ObjectFloat__, 0, 0);

    result->value = a2->value * b2->value;

    return (Object*) result;
}

Object *ObjectFloat_div(Object *a, Object *b) {

    ObjectFloat *a2, *b2;

    a2 = (ObjectFloat*) a;
    b2 = (ObjectFloat*) b;

    ObjectFloat *result = (ObjectFloat*) Object_create(a->context, __ObjectFloat__, 0, 0);

    result->value = a2->value / b2->value;

    return (Object*) result;
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
