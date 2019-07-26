
#include "../../runtime/header.h"

typedef struct Pointer Pointer;

struct Pointer {
	OBJECT_HEAD;
	void *addr;
	u32 size;
};

void Pointer_init(Object *self, Object **argv, u32 argc) {

	Pointer *p = (Pointer*) self;
	ObjectInt *size_obj;
	void *addr;
	u32   size;

	if(argc == 0)
		return;

	if(argv[0]->type != __ObjectInt__)
		return;

	size_obj = (ObjectInt*) argv[0];
	size = size_obj->value;

	if(size == 0)
		return;

	addr = malloc(size);

	if(addr == NULL)
		return;

	p->addr = addr;
	p->size = size;

}

void Pointer_destroy(Object *self) {

	Pointer *p = (Pointer*) self;

	if(p->addr == NULL)
		return;

	free(p->addr);

	p->addr = 0;
}

Object *Pointer_free(Object *self, Object **argv, u32 argc) {

	Pointer *p = (Pointer*) self;

	if(p->addr == NULL)
		return NOJA_False;

	free(p->addr);

	p->addr = 0;

	return NOJA_True;
}

Object *Pointer_size(Object *self, Object **argv, u32 argc) {

	return ObjectInt_from_cint(self->context, (i64) ((Pointer*) self)->size);

}

Object *Pointer_write(Object *self, Object **argv, u32 argc) {

	Pointer *p = (Pointer*) self;
	u32 object_repr_size;
	u32 beg, end;

	if(argc == 0) // No arguments provided
		return NOJA_False;

	if(p->addr == NULL) // The pointer is null
		return NOJA_False;

	object_repr_size = Object_get_raw_repr_size(argv[0]);

	if(argc > 1) { // Starting index provided

		if(argv[1]->type != __ObjectInt__) { // The starting index is not an integer

			ctx_throw_exception(self->context, Exception_TypeError);

			return NOJA_False;

		}

		beg = ((ObjectInt*) argv[1])->value;

		if(beg < 0)
			return NOJA_False;

	} else { // By default write at index 0

		beg = 0;

	}

	if(argc > 2) { // End index provided

		if(argv[2]->type != __ObjectInt__) { // End index is not an integer
			ctx_throw_exception(self->context, Exception_TypeError);
			return NOJA_False;
		}

		end = ((ObjectInt*) argv[1])->value;

		if(end < 0 || end <= beg || end >= p->size) // invalid end index

			return NOJA_False;

	} else { // By default write till the end of the pointed chunk

		end = p->size - beg; // +-1?

	}

	if(object_repr_size == 0) // The object has no raw representation

		return NOJA_False;

	if(object_repr_size > end - beg) { // +-1?
		// object representation is bigger than the chunk
	}

	Object_get_raw_repr(argv[0], p->addr + beg, end - beg);

	return ObjectInt_from_cint(self->context, MIN(object_repr_size, end - beg));
}

char Pointer_to_cbool(Object *self) {

	return ((Pointer*) self)->addr != NULL;

}

void Pointer_iter(Object *self, Object *iter) {

	Pointer *p = (Pointer*) self;
	ObjectIterator *iterator = (ObjectIterator*) iter;

}

Object *Pointer_next(Object *self, Object *iter) {

	Pointer *p = (Pointer*) self;
	ObjectIterator *iterator = (ObjectIterator*) iter;

	if(p->addr == NULL)
		return NOJA_False;

	i64 index;

	if(iterator->ended)
		return NOJA_False;

	if(iterator->index->type == __ObjectInt__) {

		index = ((ObjectInt*) iterator->index)->value + 1;

	} else {

		index = 0;
	}

	char byte = ((char*) p->addr)[index];

	iterator->index = ObjectInt_from_cint(self->context, index);

	if(index+1 == p->size)
		iterator->ended = 1;

	return ObjectInt_from_cint(self->context, (i64) byte);

}

void Pointer_print(Object *self) {
	printf("%p", ((Pointer*) self)->addr);
}

ObjectType TypeTable_Pointer = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .methods = 0,
    .name  = "Pointer",
    .size = sizeof(Pointer),
    .free = &Pointer_destroy,
    .select = 0,
    .insert = 0,
    .init   = &Pointer_init,
    .call   = 0,
    .getAttr = 0,
    .setAttr = 0,
    .iter = &Pointer_iter,
    .next = &Pointer_next,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .print  = Pointer_print,
    .expid  = 0,
    .to_cbool = &Pointer_to_cbool,
    .collectChildren = 0
};


char Module_lowLevel_init(Object *dest) {

    Object *methods = Object_create(dest->context, __ObjectDict__, 0, 0);

    Dict_cinsert(methods, "size" , ObjectCFunction_create(dest->context, &Pointer_size));
    Dict_cinsert(methods, "free" , ObjectCFunction_create(dest->context, &Pointer_free));
    Dict_cinsert(methods, "write" , ObjectCFunction_create(dest->context, &Pointer_write));

    TypeTable_Pointer.methods = methods;

    Dict_cinsert(dest, "Pointer", (Object*) &TypeTable_Pointer);

    return 1;
}
