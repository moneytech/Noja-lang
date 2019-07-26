
#include "gsl.h"

ObjectType TypeTable_GSLVector = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "GSLVector",
    .size = sizeof(GSLVector),
    .methods = 0,
    .free = GSLVector_destroy,
    .select = GSLVector_select,
    .insert = GSLVector_insert,
    .init   = GSLVector_init,
    .call   = 0,
    .print  = GSLVector_print,
    .iter = GSLVector_iter,
    .next = GSLVector_next,
    .get_raw_repr = &GSLVector_get_raw_repr,
    .get_raw_repr_size = &GSLVector_get_raw_repr_size,
    .expid  = 2,
    .to_cbool = &return_1,
    .collectChildren = 0
};

void GSLVector_init(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;

	if(argc == 0)
		return;

	if(argv[0]->type != __ObjectInt__)
		return;

	i64 size = ((ObjectInt*) argv[0])->value;

	if(size <= 0)
		return;

	vector->addr = gsl_vector_alloc(size);
	vector->size = size;

}

void GSLVector_destroy(Object *self) {

	GSLVector *vector = (GSLVector*) self;

	gsl_vector_free(vector->addr);
}

void GSLVector_print(Object *self) {

	GSLVector *vector = (GSLVector*) self;

	printf("[");

	for(u32 i = 0; i < vector->size; i++) {

		printf("%g", gsl_vector_get(vector->addr, i));

		if(i + 1 < vector->size)
			printf(", ");
	}

	printf("]");
}

Object *GSLVector_select(Object *self, Object *key) {

	GSLVector *vector = (GSLVector*) self;
	i64 index;

	if(vector->addr == NULL) {
		ctx_throw_exception(self->context, Exception_IndexError);
		return NOJA_False;
	}

	if(key->type != __ObjectInt__) {
		ctx_throw_exception(self->context, Exception_IndexError);
		return NOJA_False;
	}

	index = ((ObjectInt*) key)->value;

	if(index < 0) {

		index = vector->size + index; // +-1?

	} else if(index >= vector->size) {

		ctx_throw_exception(self->context, Exception_IndexError);

		return NOJA_False;

	}

	double value = gsl_vector_get(vector->addr, index);

	return ObjectFloat_from_cdouble(self->context, value);
}

char GSLVector_insert(Object *self, Object *key_obj, Object *value_obj) {

	GSLVector *vector = (GSLVector*) self;
	i64 key;
	double value;

	if(vector->addr == NULL)
		return 0;

	if(key_obj->type != __ObjectInt__) {
		ctx_throw_exception(self->context, Exception_IndexError);
		return 0;
	}

	key = ((ObjectInt*) key_obj)->value;

	if(key < 0) {

		key = vector->size + key; // +-1?

	} else if(key >= vector->size) {

		ctx_throw_exception(self->context, Exception_IndexError);

		return 0;

	}

	if(value_obj->type == __ObjectInt__) {

		value = (double) ((ObjectInt*) value_obj)->value;

	} else if(value_obj->type == __ObjectFloat__) {

		value = ((ObjectFloat*) value_obj)->value;

	} else {

		ctx_throw_exception(self->context, Exception_TypeError);

		return 0;

	}

	gsl_vector_set(vector->addr, key, value);

	return 1;
}

void GSLVector_iter(Object *self, Object *iter) {

}

Object *GSLVector_next(Object *self, Object *iter) {

	GSLVector *vector = (GSLVector*) self;
	ObjectIterator *iterator = (ObjectIterator*) iter;
	i64 index;

	if(iterator->ended)
		return NOJA_False;

	if(iterator->index->type == __ObjectInt__) {
		index = ((ObjectInt*) iterator->index)->value + 1;
	} else {
		index = 0;
	}

	if(index+1 == vector->size)
		iterator->ended = 1;

	iterator->index = ObjectInt_from_cint(self->context, index);

	double value = gsl_vector_get(vector->addr, index);

	return ObjectFloat_from_cdouble(self->context, value);
}

u32 GSLVector_get_raw_repr_size(Object *self) {

	GSLVector *vector = (GSLVector*) self;

	return vector->size * sizeof(double);
}

void GSLVector_get_raw_repr(Object *self, void *addr, u32 max_size) {

	GSLVector *vector = (GSLVector*) self;

	int remaining = max_size;

	for(u32 i = 0; i < vector->size && remaining > 0; i++) {

		double value = gsl_vector_get(vector->addr, i);

		memcpy(addr, &value, MIN(sizeof(double), remaining)); // ignoring allignment

		remaining -= sizeof(double);

	}

}

Object *GSLVector_add(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;
	GSLVector *temp;

	if(vector->addr == NULL)
		return NOJA_False;

	for(u32 i = 0; i < argc; i++) {

		if(argv[i]->type != &TypeTable_GSLVector) {
			ctx_throw_exception(self->context, Exception_TypeError);
			return NOJA_False;
		}

		temp = (GSLVector*) argv[i];

		if(temp->addr == NULL) continue;

		gsl_vector_add(vector->addr, temp->addr);

	}

	return NOJA_True;
}

Object *GSLVector_sub(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;
	GSLVector *temp;

	if(vector->addr == NULL)
		return NOJA_False;

	for(u32 i = 0; i < argc; i++) {

		if(argv[i]->type != &TypeTable_GSLVector) {
			ctx_throw_exception(self->context, Exception_TypeError);
			return NOJA_False;
		}

		temp = (GSLVector*) argv[i];

		if(temp->addr == NULL) continue;

		// compare vector shapes maybe?

		gsl_vector_sub(vector->addr, temp->addr);

	}

	return NOJA_True;
}

Object *GSLVector_mul(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;
	GSLVector *temp;

	if(vector->addr == NULL)
		return NOJA_False;

	for(u32 i = 0; i < argc; i++) {

		if(argv[i]->type != &TypeTable_GSLVector) {
			ctx_throw_exception(self->context, Exception_TypeError);
			return NOJA_False;
		}

		temp = (GSLVector*) argv[i];

		if(temp->addr == NULL) continue;

		if(vector->size != temp->size)

			return NOJA_False;

		gsl_vector_mul(vector->addr, temp->addr);

	}

	return NOJA_True;
}

Object *GSLVector_div(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;
	GSLVector *temp;

	if(vector->addr == NULL)
		return NOJA_False;

	for(u32 i = 0; i < argc; i++) {

		if(argv[i]->type != &TypeTable_GSLVector) {
			ctx_throw_exception(self->context, Exception_TypeError);
			return NOJA_False;
		}

		temp = (GSLVector*) argv[i];

		if(temp->addr == NULL) continue;

		if(vector->size != temp->size)

			return NOJA_False;

		gsl_vector_div(vector->addr, temp->addr);

	}

	return NOJA_True;
}

Object *GSLVector_scale(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;
	GSLVector *temp;

	if(vector->addr == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	double factor;

	if(argv[0]->type == __ObjectInt__) {

		factor = (double) ((ObjectInt*) argv[0])->value;

	} else if(argv[0]->type == __ObjectFloat__) {

		factor = ((ObjectFloat*) argv[0])->value;

	} else {
		ctx_throw_exception(self->context, Exception_TypeError);
		return NOJA_False;
	}

	gsl_vector_scale(vector->addr, factor);

	return NOJA_True;
}

Object *GSLVector_max(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;

	if(vector->addr == NULL)
		return NOJA_False;

	return ObjectFloat_from_cdouble(self->context, gsl_vector_max(vector->addr));
}

Object *GSLVector_min(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;

	if(vector->addr == NULL)
		return NOJA_False;

	return ObjectFloat_from_cdouble(self->context, gsl_vector_min(vector->addr));
}

Object *GSLVector_maxIndex(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;

	if(vector->addr == NULL)
		return NOJA_False;

	return ObjectInt_from_cint(self->context, gsl_vector_max_index(vector->addr));
}

Object *GSLVector_minIndex(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;

	if(vector->addr == NULL)
		return NOJA_False;

	return ObjectInt_from_cint(self->context, gsl_vector_min_index(vector->addr));

}

Object *GSLVector_equal(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;

	if(vector->addr == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != &TypeTable_GSLVector)
		return NOJA_False;

	return gsl_vector_equal(vector->addr, ((GSLVector*) argv[0])->addr) ? NOJA_True : NOJA_False;
}


Object *GSLVector_setAll(Object *self, Object **argv, u32 argc) {

	GSLVector *vector = (GSLVector*) self;
	double value;

	if(vector->addr == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type == __ObjectInt__) {

		value = (double) ((ObjectInt*) argv[0])->value;

	} else if(argv[0]->type == __ObjectFloat__) {

		value = ((ObjectInt*) argv[0])->value;

	} else {

		ctx_throw_exception(self->context, Exception_TypeError);
		return NOJA_False;

	}

	gsl_vector_set_all(vector->addr, value);

	return NOJA_True;
}
