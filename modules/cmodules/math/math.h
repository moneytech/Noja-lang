
#include "../../../runtime/header.h"

#include <math.h>

typedef struct Matrix_inner Matrix_inner;
typedef struct Matrix Matrix;

typedef double vector8 __attribute__ ((vector_size (8)));

struct Matrix_inner {
	int refcount;
	double chunk[];
};

struct Matrix {
	OBJECT_HEAD;
	u32 w, h, rw, rh;
	int displacement;
	Matrix_inner *inner;
	Matrix_inner *inner_t;
};

/* === Functions === */

Object *Math_arccos(Object *self, Object **argv, u32 argc);
Object *Math_arcsin(Object *self, Object **argv, u32 argc);
Object *Math_arctan(Object *self, Object **argv, u32 argc);
Object *Math_arctan2(Object *self, Object **argv, u32 argc);

Object *Math_cosh(Object *self, Object **argv, u32 argc);
Object *Math_sinh(Object *self, Object **argv, u32 argc);
Object *Math_tanh(Object *self, Object **argv, u32 argc);

Object *Math_cos(Object *self, Object **argv, u32 argc);
Object *Math_sin(Object *self, Object **argv, u32 argc);

Object *Math_log(Object *self, Object **argv, u32 argc);
Object *Math_log10(Object *self, Object **argv, u32 argc);

Object *Math_exp(Object *self, Object **argv, u32 argc);
Object *Math_pow(Object *self, Object **argv, u32 argc);
Object *Math_sqrt(Object *self, Object **argv, u32 argc);

Object *Math_sigmoid(Object *self, Object **argv, u32 argc);
Object *Math_sigmoid_deriv(Object *self, Object **argv, u32 argc);


/* === Matrix === */

extern ObjectType ptable_Matrix;

char build_transposed(Matrix *m);

void 	Matrix_init(Object *self, Object **argv, u32 argc);
void 	Matrix_destroy(Object *self);
Object *Matrix_select(Object *self, Object *key_obj);
char 	Matrix_insert(Object *self, Object *key_obj, Object *value_obj);
void    Matrix_print(Object *self);
Object *Matrix_width(Object *self, Object **argv, u32 argc);
Object *Matrix_height(Object *self, Object **argv, u32 argc);

Object *Matrix_mul(Object *self, Object **argv, u32 argc);
Object *Matrix_set(Object *self, Object **argv, u32 argc);
Object *Matrix_add(Object *self, Object **argv, u32 argc);
Object *Matrix_sub(Object *self, Object **argv, u32 argc);
Object *Matrix_scale(Object *self, Object **argv, u32 argc);
Object *Matrix_equals(Object *self, Object **argv, u32 argc);
