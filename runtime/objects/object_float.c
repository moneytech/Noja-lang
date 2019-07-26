
#include "../header.h"

ObjectTypeOperators object_float_operators = {
    .add = ObjectFloat_add,
    .sub = ObjectFloat_sub,
    .mul = ObjectFloat_mul,
    .div = ObjectFloat_div,
    .eql = ObjectFloat_eql,
    .grt = ObjectFloat_grt,
    .lss = ObjectFloat_lss,
};

ObjectType ptable_ObjectFloat = {
    .type = &ptable_ObjectType,
    .flags = 0,
    .name  = "Float",
    .size = sizeof(ObjectFloat),
    .methods = 0,
    .free = 0,
    .select = 0,
    .insert = 0,
    .init   = 0,
    .call   = 0,
    .print  = &ObjectFloat_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .operators = &object_float_operators,
    .to_cbool = &ObjectFloat_to_cbool,
    .collectChildren = 0
};

/* === Operators === */

Object *ObjectFloat_eql(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value == ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloat_lss(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value < ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
}

Object *ObjectFloat_grt(Object *a, Object *b) {
    return ((ObjectFloat*) a)->value > ((ObjectFloat*) b)->value ? NOJA_True : NOJA_False;
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

/* === Factory functions === */

Object *ObjectFloat_from_cdouble(Context *context, f64 n) {
    ObjectFloat *i = (ObjectFloat*) Object_create(context, __ObjectFloat__, 0, 0);
    i->value = n;
    return (Object*) i;
}

/* === Handlers === */

void ObjectFloat_print(Object *self) {
    printf("%g", ((ObjectFloat*) self)->value);
}

char ObjectFloat_to_cbool(Object *self) {
    return ((ObjectFloat*) self)->value != 0;
}

/* === Methods === */
