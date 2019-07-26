
#include "header.h"

/* === Object === */

char return_1(Object *o) {
    return 1;
}

u32 Object_get_raw_repr_size(Object *self) {

  if(self->type->get_raw_repr_size == NULL)

    return 0;

  return self->type->get_raw_repr_size(self);
}

void Object_get_raw_repr(Object *self, void *addr, u32 max_size) {

  if(self->type->get_raw_repr == NULL)
    return;

  self->type->get_raw_repr(self, addr, max_size);

}

void Object_destroy(Object *self) {

    if(self->type->free) {
        self->type->free(self);
    }
}

Object *Object_create(Context *context, ObjectType *type, Object **argv, u32 argc) {

    if(type == __ObjectBool__)
      return NOJA_True;

    Object *object = (Object*) Mem_allocate(context, type->size);

    if(!object)
      return 0;

    object->flags |= OBJ_IS_GC_COLLECTABLE;
    object->type = type;
    object->context = context;

    if(type->init)

        type->init(object, argv, argc);

    return object;
}

Object *Object_call(Object *self, Object *parent, Object **argv, u32 argc) {

  if(!self->type->call) {
    ctx_throw_exception(self->context, Exception_UncallableCalled);
    return 0;
  }

    return self->type->call(self, parent, argv, argc);
}

u32 Object_size(Object *self) {
    return self->type->size;
}

void Object_setAttr(Object *self, char *name, Object *value) {

    if(!self->type->setAttr) {


      ctx_throw_exception(self->context, Exception_SetAttributeError);

      return;
    }

    self->type->setAttr(self, name, value);
}

Object *Object_getAttr(Object *self, char *name) {

    if(!self->type->getAttr) {

        if(!self->type->methods) {

          ctx_throw_exception(self->context, Exception_AttributeError);

          return 0;

        }

        Object *value = Dict_cselect(self->type->methods, name);

        if(!value) {

          ctx_throw_exception(self->context, Exception_AttributeError);

          return 0;

        }

        return value;
    }

    return self->type->getAttr(self, name);
}

char Object_insert(Object *self, Object *key, Object *value) {

    if(!self->type->insert) {

      ctx_throw_exception(self->context, Exception_InsertError);

      return 0;
    }

    return self->type->insert(self, key, value);
}

Object *Object_select(Object *self, Object *key) {

    if(!self->type->select) {

      ctx_throw_exception(self->context, Exception_SelectError);

      return 0;
    }

    return self->type->select(self, key);
}


void Object_collectChildren(Object *self) {

  if(self->type->flags & OBJ_IS_GC_COLLECTABLE)
    Mem_collect((Object**) &self->type);

  if(self->type->collectChildren) {
    self->type->collectChildren(self);
  }

}

char Object_to_cbool(Object *self) {

    if(!self->type->to_cbool) {

      ctx_throw_exception(self->context, Exception_TypeError);

      return 0;
    }

    return self->type->to_cbool(self);
}

Object *Object_lss(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->lss == NULL)
      return 0;

    return a->type->operators->lss(a, b);
}

Object *Object_grt(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->grt == NULL)
      return 0;

    return a->type->operators->grt(a, b);
}

Object *Object_eql(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->eql == NULL)
      return 0;

    return a->type->operators->eql(a, b);
}

Object *Object_leq(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->grt == NULL)
      return 0;

    return a->type->operators->grt(a, b) == NOJA_True ? NOJA_False : NOJA_True;

}

Object *Object_geq(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->lss == NULL)
      return 0;

    return a->type->operators->lss(a, b) == NOJA_True ? NOJA_False : NOJA_True;

}

Object *Object_add(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->add == NULL)
      return 0;

    return a->type->operators->add(a, b);

}

Object *Object_sub(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->add == NULL)
      return 0;

    return a->type->operators->sub(a, b);
}

Object *Object_mul(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->mul == NULL)
      return 0;

    return a->type->operators->mul(a, b);
}

Object *Object_div(Object *a, Object *b) {

    if(a->type->operators == NULL)
      return 0;

    if(a->type->operators->div == NULL)
      return 0;

    return a->type->operators->div(a, b);
}

void Object_print(Object *a) {

    if(!a->type->print) {
        printf("<type %s is unprintable>", a->type->name);
        return;
    }

    a->type->print(a);
}

/* === Class === */

void Class_delete(Object *self) {

}

Object *Class_select(Object *self, Object *key) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__select__");

  if(!method) {
    ctx_throw_exception(self->context, Exception_AttributeError);
    return 0;
  }

  if(method->type != __ObjectFunction__) {
    ctx_throw_exception(self->context, Exception_TypeError);
    return 0;
  }

  ctx_create_activation_record(self->context);
  ctx_push_self(self->context, self);
  ctx_push_argument(self->context, key);

  self->context->pending_call_offset = ((ObjectFunction*) method)->offset;

  return 0;
}

char Class_insert(Object *self, Object *key, Object *value) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__insert__");

  if(!method) {
    ctx_throw_exception(self->context, Exception_AttributeError);
    return 0;
  }

  if(method->type != __ObjectFunction__) {
    ctx_throw_exception(self->context, Exception_TypeError);
    return 0;
  }

  ctx_create_activation_record(self->context);
  ctx_push_self(self->context, self);
  ctx_push_argument(self->context, key);
  ctx_push_argument(self->context, value);

  self->context->pending_call_offset = ((ObjectFunction*) method)->offset;

  return 1;
}

Object *Class_getAttr(Object *self, char *key) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *result = Dict_cselect(istance->members, key);

  if(!result)
    result = Dict_cselect(istance->type->methods, key);

  return result;
}

void Class_setAttr(Object *self, char *key, Object *value) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Dict_cinsert(istance->members, key, value);
}

void Class_init(Object *self, Object **argv, u32 argc) {

  ObjectIstance *istance = (ObjectIstance*) self;

  istance->members = Object_create(self->context, __ObjectDict__, 0, 0);

  Object *method = Dict_cselect(istance->type->methods, "__init__");

  if(!method) {
    ctx_throw_exception(self->context, Exception_AttributeError);
    return;
  }

  if(method->type != __ObjectFunction__) {
    ctx_throw_exception(self->context, Exception_TypeError);
    return;
  }

  ctx_push_self(self->context, self);

  self->context->pending_call_offset = ((ObjectFunction*) method)->offset;

}

Object *Class_call(Object *self, Object **argv, u32 argc) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__call__");

  if(!method) {
    ctx_throw_exception(self->context, Exception_AttributeError);
    return 0;
  }

  if(method->type != __ObjectFunction__) {
    ctx_throw_exception(self->context, Exception_TypeError);
    return 0;
  }

  ctx_push_self(self->context, self);

  self->context->pending_call_offset = ((ObjectFunction*) method)->offset;

  return 0;
}

void Class_print(Object *self) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Object *method = Dict_cselect(istance->type->methods, "__print__");

  if(!method) {
    ctx_throw_exception(self->context, Exception_AttributeError);
    return;
  }

  if(method->type != __ObjectFunction__) {
    ctx_throw_exception(self->context, Exception_TypeError);
    return;
  }

  ctx_create_activation_record(self->context);
  ctx_push_self(self->context, self);

  self->context->pending_call_offset = ((ObjectFunction*) method)->offset;

}

void Class_collectChildren(Object *self) {

  ObjectIstance *istance = (ObjectIstance*) self;

  Mem_collect(&istance->members);

}
