
#include "../../../runtime/header.h"

#include <gsl/gsl_vector.h> // vectors
#include <gsl/gsl_rng.h> // random numbers

typedef struct GSLVector GSLVector;

struct GSLVector {
	OBJECT_HEAD;
	gsl_vector *addr;
	u32 size;
};

/* === Vectors === */

extern ObjectType ptable_GSLVector;

void 	GSLVector_init(Object *self, Object **argv, u32 argc);
void 	GSLVector_destroy(Object *self);
void 	GSLVector_print(Object *self);
Object *GSLVector_select(Object *self, Object *key);
char 	GSLVector_insert(Object *self, Object *key_obj, Object *value_obj);
void 	GSLVector_iter(Object *self, Object *iter);
Object *GSLVector_next(Object *self, Object *iter);
u32 	GSLVector_get_raw_repr_size(Object *self);
void 	GSLVector_get_raw_repr(Object *self, void *addr, u32 max_size);
Object *GSLVector_add(Object *self, Object **argv, u32 argc);
Object *GSLVector_sub(Object *self, Object **argv, u32 argc);
Object *GSLVector_mul(Object *self, Object **argv, u32 argc);
Object *GSLVector_div(Object *self, Object **argv, u32 argc);
Object *GSLVector_max(Object *self, Object **argv, u32 argc);
Object *GSLVector_min(Object *self, Object **argv, u32 argc);
Object *GSLVector_maxIndex(Object *self, Object **argv, u32 argc);
Object *GSLVector_minIndex(Object *self, Object **argv, u32 argc);
Object *GSLVector_equal(Object *self, Object **argv, u32 argc);
Object *GSLVector_setAll(Object *self, Object **argv, u32 argc);
Object *GSLVector_scale(Object *self, Object **argv, u32 argc);