
#include "math.h"

ObjectType TypeTable_Matrix = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .name  = "Matrix",
    .size = sizeof(Matrix),
    .methods = 0,
    .free = Matrix_destroy,
    .select = Matrix_select,
    .insert = Matrix_insert,
    .init   = Matrix_init,
    .call   = 0,
    .print  = Matrix_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .expid  = 0,
    .to_cbool = &return_1,
    .collectChildren = 0
};

char build_transposed(Matrix *m) {

	if(m->inner_t)
		return 0;

	Matrix_inner *mt = malloc(sizeof(Matrix_inner) * m->rw * m->rh * sizeof(double));
		
	if(mt == NULL)
		return 0;

	mt->refcount = 0;

	for(u32 i = 0; i < m->h; i++)
		for(u32 j = 0; j < m->w; j++)
			mt->chunk[j * m->rw + i] = m->inner->chunk[i * m->rw + i];
	
	m->inner_t = mt;

	return 1;
}

void Matrix_print(Object *self) {
	
	Matrix *m = (Matrix*) self;

	int i, j;

	i = 0; // row
	j = 0; // col

	if(m->h > 1) printf("[");

	printf("[", m->rw, m->rh);

	while(1) {

		printf("%g", m->inner->chunk[m->displacement + i * m->rw + j]);

		j++;

		if(j == m->w) {

			i++;

			j = 0;

			printf("]");
			
			if(i == m->h)
				break;
		
			printf(", [");
		} else {
			printf(", ");
		}

	}

	if(m->h > 1) printf("]");

}

void Matrix_init(Object *self, Object **argv, u32 argc) {
	
	Matrix *m = (Matrix*) self;
	i64 w, h, rw, rh;
	Matrix_inner *inner;
	double default_value = 0;

	if(argc < 2) {
		return;
	}

	if(argv[0]->type != __ObjectInt__ &&
	   argv[1]->type != __ObjectInt__) {
		return;
	}

	if(argc > 2) {
		if(argv[2]->type == __ObjectInt__) {
			
			default_value = (double) ((ObjectInt*) argv[2])->value;

		} else if(argv[2]->type == __ObjectFloat__) {

			default_value = ((ObjectFloat*) argv[2])->value;

		}
	}

	w = ((ObjectInt*) argv[0])->value;
	h = ((ObjectInt*) argv[1])->value;

	if(w <= 0 || h <= 0)
		return;

	if(w == 0 && h == 0)
		return;

	if(w == 1) {
		printf(">>> vertical vectors not supported\n");
		assert(0);
	}

	if(w < 8) { rw = 8; } else { rw = w + 8 - (w % 8); }
	if(h < 8) { rh = 8; } else { rh = h + 8 - (h % 8); }

	inner = malloc(sizeof(Matrix_inner) + rw * rh * sizeof(double));

	if(inner == NULL)
		return;

	inner->refcount = 0;
	memset(inner->chunk, default_value, rw * rh * sizeof(double));

	m->inner = inner;
	m->w = w;
	m->h = h;
	m->rw = rw;
	m->rh = rh;

	inner->refcount++;

}

void Matrix_destroy(Object *self) {
	
	Matrix *m = (Matrix*) self;

	m->inner->refcount--;

	if(m->inner->refcount == 0)
		free(m->inner);

}

Object *Matrix_select(Object *self, Object *key_obj) {
	
	Matrix *m = (Matrix*) self;
	i64 key;

	if(m->inner == NULL) {
		ctx_throw_exception(&context, Exception_IndexError);
		return NOJA_False;
	}

	if(key_obj->type != __ObjectInt__) {
		ctx_throw_exception(&context, Exception_IndexError);
		return NOJA_False;
	}

	key = ((ObjectInt*) key_obj)->value;

	if(m->w == 1) {

		// vertical vector
		printf(">>> vertical vectors not supported\n");
		assert(0);

		/*
		if(key < 0)
			key = m->h + key;

		double value = m->inner->chunk[m->displacement + key];

		return ObjectFloat_from_cdouble(value);
		*/

	} else if(m->h == 1) {
		
		// horizontal vector

		if(key < 0)
			key = m->w + key;
		
		double value = m->inner->chunk[m->displacement + key];

		return ObjectFloat_from_cdouble(value);

	} else {

		// matrix

		if(key < 0)
			key = m->h + key;

		Matrix *child = (Matrix*) Object_create(&TypeTable_Matrix, 0, 0);

		child->inner = m->inner;
		child->displacement = m->rw * key;
		child->h = 1;
		child->w = m->w;
		m->inner->refcount++;

		return (Object*) child;

	}

}


char Matrix_insert(Object *self, Object *key_obj, Object *value_obj) {
	
	Matrix *m = (Matrix*) self;
	i64 key;
	double value;

	if(m->inner == NULL) {
		ctx_throw_exception(&context, Exception_IndexError);
		return 0;
	}

	if(key_obj->type != __ObjectInt__) {
		ctx_throw_exception(&context, Exception_IndexError);
		return 0;
	}

	key = ((ObjectInt*) key_obj)->value;

	if(m->w == 1) {

		// vertical vector
		printf(">>> vertical vectors not supported\n");
		assert(0);

		/*
		if(key < 0)
			key = m->h + key;

		double value = m->inner->chunk[m->displacement + key];

		return ObjectFloat_from_cdouble(value);
		*/

	} else if(m->h == 1) {
		
		// horizontal vector

		if(value_obj->type != __ObjectFloat__) {
			ctx_throw_exception(&context, Exception_TypeError);
			return 0;
		}

		value = ((ObjectFloat*) value_obj)->value;

		if(key < 0) {
			key = m->w + key;
		}

		if(key >= m->w) {
			ctx_throw_exception(&context, Exception_IndexError);
			return 0;
		}
		
		m->inner->chunk[m->displacement + key] = value;

	} else {

		// matrix

		if(key < 0) {
			key = m->h + key;
		}

		if(key >= m->h) {
			ctx_throw_exception(&context, Exception_IndexError);
			return 0;
		}

		Matrix *m2;

		if(value_obj->type != &TypeTable_Matrix) {
			ctx_throw_exception(&context, Exception_TypeError);
			return 0;
		}

		m2 = ((Matrix*) value_obj);

		if(m2->w == 1) {
			printf(">>> vertical vectors not supported\n");
			assert(0);
		}

		if(m2->w != m->w || m2->h != 1)
			return 0;

		for(u32 i = 0; i < m->w; i++)
			m->inner->chunk[m->displacement + m->rw * key + i] = m2->inner->chunk[m2->displacement + i];

	}

	return 1;
}

Object *Matrix_width(Object *self, Object **argv, u32 argc) {
	return ObjectInt_from_cint(((Matrix*) self)->w);
}

Object *Matrix_height(Object *self, Object **argv, u32 argc) {
	return ObjectInt_from_cint(((Matrix*) self)->h);
}

Object *Matrix_mul(Object *self, Object **argv, u32 argc) {

	Matrix *m1 = (Matrix*) self;
	Matrix *m2;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != &TypeTable_Matrix)
		return NOJA_False;

	m2 = (Matrix*) argv[0];

	assert(m2->rw == m1->rh);

	//assert(build_transposed(m2) == 1);

	Matrix_inner *i1, *i2, *i3;

	i1 = m1->inner;
	i2 = m2->inner;
	i3 = malloc(sizeof(Matrix_inner) + m1->rw * m2->rh * sizeof(double));

	assert(i3 != NULL);

	i3->refcount = 0;

	for(u32 i = 0; i < m1->rh; i++) {

		for(u32 j = 0; j < m2->rw; j++) {
			
			i3->chunk[m2->rw * j + i] = 0;

			for(u32 k = 0; k < m1->rh; k++) {
				
				i3->chunk[m2->rw * j + i] += i1->chunk[m1->rw * i + k] * i2->chunk[m2->rw * k + j];

			}
		}
	}

	Matrix *m3 = (Matrix*) Object_create(&TypeTable_Matrix, 0, 0);

	m3->w = m2->w;
	m3->h = m1->h;
	m3->rw = m2->rw;
	m3->rh = m1->rh;
	m3->inner = i3;

	i3->refcount++;

	return (Object*) m3;
}


Object *Matrix_set(Object *self, Object **argv, u32 argc) {

	Matrix *m1 = (Matrix*) self;
	double value;

	if(m1->inner == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	value = ((ObjectFloat*) argv[0])->value;

	u32 i, j;

	i = 0;
	j = 0;

	while(1) {

		m1->inner->chunk[m1->rw*i + j] = value;

		j++;

		if(j == m1->w) {

			i++;

			j = 0;

			if(i == m1->h)

				break;
		}

	}

	return NOJA_True;
}


Object *Matrix_scale(Object *self, Object **argv, u32 argc) {

	Matrix *m1 = (Matrix*) self;
	double value;

	if(m1->inner == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != __ObjectFloat__) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	value = ((ObjectFloat*) argv[0])->value;

	u32 i, j;

	i = 0;
	j = 0;

	while(1) {

		m1->inner->chunk[m1->rw*i + j] *= value;

		j++;

		if(j == m1->w) {

			i++;

			j = 0;

			if(i == m1->h)

				break;
		}

	}

	return NOJA_True;
}

Object *Matrix_add(Object *self, Object **argv, u32 argc) {

	Matrix *m1 = (Matrix*) self;
	Matrix *m2;

	if(m1->inner == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != &TypeTable_Matrix) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	m2 = (Matrix*) argv[0];

	if(m1->w != m2->w || m1->h != m2->h)
		return NOJA_False;

	u32 i, j;

	i = 0;
	j = 0;

	while(1) {

		m1->inner->chunk[m1->rw * i + j] += m2->inner->chunk[m2->rw * i + j];

		j++;

		if(j == m1->w) {

			i++;

			j = 0;

			if(i == m1->h)

				break;
		}

	}

	return NOJA_True;
}

Object *Matrix_sub(Object *self, Object **argv, u32 argc) {

	Matrix *m1 = (Matrix*) self;
	Matrix *m2;

	if(m1->inner == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != &TypeTable_Matrix) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	m2 = (Matrix*) argv[0];

	if(m1->w != m2->w || m1->h != m2->h)
		return NOJA_False;

	u32 i, j;

	i = 0;
	j = 0;

	while(1) {

		m1->inner->chunk[m1->rw * i + j] -= m2->inner->chunk[m2->rw * i + j];

		j++;

		if(j == m1->w) {

			i++;

			j = 0;

			if(i == m1->h)

				break;
		}

	}

	return NOJA_True;
}

Object *Matrix_equals(Object *self, Object **argv, u32 argc) {

	Matrix *m1 = (Matrix*) self;
	Matrix *m2;

	if(m1->inner == NULL)
		return NOJA_False;

	if(argc == 0)
		return NOJA_False;

	if(argv[0]->type != &TypeTable_Matrix) {
		ctx_throw_exception(&context, Exception_TypeError);
		return NOJA_False;
	}

	m2 = (Matrix*) argv[0];

	if(m1->w != m2->w || m1->h != m2->h)
		return NOJA_False;

	u32 i, j;

	i = 0;
	j = 0;

	while(1) {

		if(m1->inner->chunk[m1->rw * i + j] != m2->inner->chunk[m2->rw * i + j])
			return NOJA_False;

		j++;

		if(j == m1->w) {

			i++;

			j = 0;

			if(i == m1->h)

				break;
		}

	}

	return NOJA_True;
}