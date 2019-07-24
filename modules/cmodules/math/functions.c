
#include "math.h"

Object *Math_arccos(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(acos(x));
}

Object *Math_arcsin(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(asin(x));
}

Object *Math_arctan(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(atan(x));
}

Object *Math_arctan2(Object *self, Object **argv, u32 argc) {

	if(argc < 2)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	if(argv[1]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;
	double y = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(atan2(x, y));
}

Object *Math_cos(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(cos(x));
}

Object *Math_sin(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(sin(x));
}

Object *Math_cosh(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(cosh(x));
}

Object *Math_sinh(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(sinh(x));
}

Object *Math_tanh(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(tanh(x));
}

Object *Math_exp(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(exp(x));
}

Object *Math_pow(Object *self, Object **argv, u32 argc) {

	if(argc < 2)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	if(argv[1]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;
	double y = ((ObjectFloat*) argv[1])->value;

	return ObjectFloat_from_cdouble(pow(x, y));
}

Object *Math_log(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(log(x));
}

Object *Math_log10(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(log10(x));
}

Object *Math_sqrt(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	return ObjectFloat_from_cdouble(sqrt(x));
}

Object *Math_sigmoid(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	double y = 1 / (1 + exp(-x)); 

	return ObjectFloat_from_cdouble(y);
}

Object *Math_sigmoid_deriv(Object *self, Object **argv, u32 argc) {

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	double x = ((ObjectFloat*) argv[0])->value;

	double y = 1 / (1 + exp(-x)); 

	double z = y * (1 - y);

	return ObjectFloat_from_cdouble(z);
}