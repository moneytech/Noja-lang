
#include "math.h"

char Module_math_init(Object *dest) {

    Object *methods = Object_create(dest->context, __ObjectDict__, 0, 0);

    Dict_cinsert(methods, "width" , ObjectCFunction_create(dest->context, &Matrix_width));
    Dict_cinsert(methods, "height" , ObjectCFunction_create(dest->context, &Matrix_height));
    Dict_cinsert(methods, "mul" , ObjectCFunction_create(dest->context, &Matrix_mul));
    Dict_cinsert(methods, "set" , ObjectCFunction_create(dest->context, &Matrix_set));
    Dict_cinsert(methods, "add" , ObjectCFunction_create(dest->context, &Matrix_add));
    Dict_cinsert(methods, "sub" , ObjectCFunction_create(dest->context, &Matrix_sub));
    Dict_cinsert(methods, "scale" , ObjectCFunction_create(dest->context, &Matrix_scale));
    Dict_cinsert(methods, "equals" , ObjectCFunction_create(dest->context, &Matrix_equals));

    TypeTable_Matrix.methods = methods;

    Dict_cinsert(dest, "PI", ObjectFloat_from_cdouble(dest->context, M_PI));

    Dict_cinsert(dest, "Matrix", (Object*) &TypeTable_Matrix);
    Dict_cinsert(dest, "arccos", ObjectCFunction_create(dest->context, &Math_arccos));
    Dict_cinsert(dest, "arcsin", ObjectCFunction_create(dest->context, &Math_arcsin));
    Dict_cinsert(dest, "arctan", ObjectCFunction_create(dest->context, &Math_arctan));
    Dict_cinsert(dest, "arctan2", ObjectCFunction_create(dest->context, &Math_arctan2));
    Dict_cinsert(dest, "cosh", ObjectCFunction_create(dest->context, &Math_cosh));
    Dict_cinsert(dest, "sinh", ObjectCFunction_create(dest->context, &Math_sinh));
    Dict_cinsert(dest, "tanh", ObjectCFunction_create(dest->context, &Math_tanh));
    Dict_cinsert(dest, "cos", ObjectCFunction_create(dest->context, &Math_cos));
    Dict_cinsert(dest, "sin", ObjectCFunction_create(dest->context, &Math_sin));
    Dict_cinsert(dest, "log", ObjectCFunction_create(dest->context, &Math_log));
    Dict_cinsert(dest, "log10", ObjectCFunction_create(dest->context, &Math_log10));
    Dict_cinsert(dest, "exp", ObjectCFunction_create(dest->context, &Math_exp));
    Dict_cinsert(dest, "pow", ObjectCFunction_create(dest->context, &Math_pow));
    Dict_cinsert(dest, "sqrt", ObjectCFunction_create(dest->context, &Math_sqrt));

    Dict_cinsert(dest, "sigmoid", ObjectCFunction_create(dest->context, &Math_sigmoid));
    Dict_cinsert(dest, "sigmoid_deriv", ObjectCFunction_create(dest->context, &Math_sigmoid_deriv));

    return 1;
}
