
#include "gsl.h"

char Module_gsl_init(Object *dest) {

    Object *methods = Object_create(dest->context, __ObjectDict__, 0, 0);

    Dict_cinsert(methods, "add" , ObjectCFunction_create(dest->context, &GSLVector_add));
    Dict_cinsert(methods, "sub" , ObjectCFunction_create(dest->context, &GSLVector_sub));
    Dict_cinsert(methods, "mul" , ObjectCFunction_create(dest->context, &GSLVector_mul));
    Dict_cinsert(methods, "div" , ObjectCFunction_create(dest->context, &GSLVector_div));
    Dict_cinsert(methods, "scale" , ObjectCFunction_create(dest->context, &GSLVector_scale));
    Dict_cinsert(methods, "max" , ObjectCFunction_create(dest->context, &GSLVector_max));
    Dict_cinsert(methods, "min" , ObjectCFunction_create(dest->context, &GSLVector_min));
    Dict_cinsert(methods, "maxIndex" , ObjectCFunction_create(dest->context, &GSLVector_maxIndex));
    Dict_cinsert(methods, "minIndex" , ObjectCFunction_create(dest->context, &GSLVector_minIndex));
    Dict_cinsert(methods, "setAll" , ObjectCFunction_create(dest->context, &GSLVector_setAll));
    Dict_cinsert(methods, "equal" , ObjectCFunction_create(dest->context, &GSLVector_equal));

    ptable_GSLVector.methods = methods;

    Dict_cinsert(dest, "Vector"		      , (Object*) &ptable_GSLVector);
    //Dict_cinsert(dest, "readDir"		  , ObjectCFunction_create(&FS_readDir));

    return 1;
}
