
#include "header.h"


int NOJA_init(Context *context, char *path) {

  if(!Sources_load(path)) {
      printf("Couldn't open '%s'\n", path);
      return 0;
  }

  Mem_init(context, 4096);

  context->source_stack[0] = &sources[0];
  context->source_depth = 1;
  context->frame_depth = 1;
  context->block_depth = 0;
  context->stack_size  = 0;
  context->pc = 0;
  context->lineno = 1;
  context->pending_call_offset.addr = 0;
  context->pending_call_offset.source = 0;
  context->exception_code = 0;

  context->frames[0] = Object_create(context, __ObjectDict__, 0, 0);
  context->root_frame = context->frames[0];

  Dict_cinsert(context->frames[0], "self", context->frames[0]);

  /* Init ObjectArray object class */ {

  ptable_ObjectArray.methods = Object_create(context, __ObjectDict__, 0, 0);

    Dict_cinsert(ptable_ObjectArray.methods, "reverse", ObjectCFunction_create(context, &ObjectArray_reverse));
    Dict_cinsert(ptable_ObjectArray.methods, "append" , ObjectCFunction_create(context, &ObjectArray_append));
    Dict_cinsert(ptable_ObjectArray.methods, "pop"    , ObjectCFunction_create(context, &ObjectArray_pop));
    Dict_cinsert(ptable_ObjectArray.methods, "size"   , ObjectCFunction_create(context, &ObjectArray_size));

    Dict_cinsert(context->frames[0], "ObjectArray", (Object*) &ptable_ObjectArray);

  }

  /* Init ObjectString object class */ {

    ptable_ObjectString.methods = Object_create(context, __ObjectDict__, 0, 0);

    Dict_cinsert(ptable_ObjectString.methods, "format"       , ObjectCFunction_create(context, &ObjectString_format));
    Dict_cinsert(ptable_ObjectString.methods, "reverse"      , ObjectCFunction_create(context, &ObjectString_reverse));
    Dict_cinsert(ptable_ObjectString.methods, "sub"          , ObjectCFunction_create(context, &ObjectString_sub));
    Dict_cinsert(ptable_ObjectString.methods, "find"         , ObjectCFunction_create(context, &ObjectString_find));
    Dict_cinsert(ptable_ObjectString.methods, "length"       , ObjectCFunction_create(context, &ObjectString_length));
    Dict_cinsert(ptable_ObjectString.methods, "split"        , ObjectCFunction_create(context, &ObjectString_split));
    Dict_cinsert(ptable_ObjectString.methods, "replace"      , ObjectCFunction_create(context, &ObjectString_replace));

    Dict_cinsert(context->frames[0], "ObjectString", (Object*) &ptable_ObjectString);

  }

  /* Init Dict object class */ {

    ptable_ObjectDict.methods = Object_create(context, __ObjectDict__, 0, 0);


    /*
    Dict_cinsert(ptable_ObjectDict.methods, "format"       , ObjectCFunction_create(context, &ObjectString_format));
    Dict_cinsert(ptable_ObjectDict.methods, "reverse"      , ObjectCFunction_create(context, &ObjectString_reverse));
    Dict_cinsert(ptable_ObjectDict.methods, "sub"          , ObjectCFunction_create(context, &ObjectString_sub));
    Dict_cinsert(ptable_ObjectDict.methods, "find"         , ObjectCFunction_create(context, &ObjectString_find));
    Dict_cinsert(ptable_ObjectDict.methods, "length"       , ObjectCFunction_create(context, &ObjectString_length));
    Dict_cinsert(ptable_ObjectDict.methods, "split"        , ObjectCFunction_create(context, &ObjectString_split));
    Dict_cinsert(ptable_ObjectDict.methods, "replace"      , ObjectCFunction_create(context, &ObjectString_replace));
    */

    Dict_cinsert(context->frames[0], "Dict", (Object*) &ptable_ObjectDict);

  }

  /* Init ObjectInt object class */ {

    ptable_ObjectInt.methods = Object_create(context, __ObjectDict__, 0, 0);


    /*
    Dict_cinsert(ptable_ObjectDict.methods, "format"       , ObjectCFunction_create(context, &ObjectString_format));
    Dict_cinsert(ptable_ObjectDict.methods, "reverse"      , ObjectCFunction_create(context, &ObjectString_reverse));
    Dict_cinsert(ptable_ObjectDict.methods, "sub"          , ObjectCFunction_create(context, &ObjectString_sub));
    Dict_cinsert(ptable_ObjectDict.methods, "find"         , ObjectCFunction_create(context, &ObjectString_find));
    Dict_cinsert(ptable_ObjectDict.methods, "length"       , ObjectCFunction_create(context, &ObjectString_length));
    Dict_cinsert(ptable_ObjectDict.methods, "split"        , ObjectCFunction_create(context, &ObjectString_split));
    Dict_cinsert(ptable_ObjectDict.methods, "replace"      , ObjectCFunction_create(context, &ObjectString_replace));
    */

    Dict_cinsert(context->frames[0], "ObjectInt", (Object*) &ptable_ObjectInt);

  }

  /* Init ObjectFloat object class */ {

    ptable_ObjectFloat.methods = Object_create(context, __ObjectDict__, 0, 0);


    /*
    Dict_cinsert(ptable_ObjectFloat.methods, "format"       , ObjectCFunction_create(context, &ObjectString_format));
    Dict_cinsert(ptable_ObjectFloat.methods, "reverse"      , ObjectCFunction_create(context, &ObjectString_reverse));
    Dict_cinsert(ptable_ObjectFloat.methods, "sub"          , ObjectCFunction_create(context, &ObjectString_sub));
    Dict_cinsert(ptable_ObjectFloat.methods, "find"         , ObjectCFunction_create(context, &ObjectString_find));
    Dict_cinsert(ptable_ObjectFloat.methods, "length"       , ObjectCFunction_create(context, &ObjectString_length));
    Dict_cinsert(ptable_ObjectFloat.methods, "split"        , ObjectCFunction_create(context, &ObjectString_split));
    Dict_cinsert(ptable_ObjectFloat.methods, "replace"      , ObjectCFunction_create(context, &ObjectString_replace));
    */

    Dict_cinsert(context->frames[0], "ObjectFloat", (Object*) &ptable_ObjectFloat);

  }

  /* Init ObjectBool object class */ {

    ptable_ObjectBool.methods = Object_create(context, __ObjectDict__, 0, 0);


    /*
    Dict_cinsert(ptable_ObjectDict.methods, "format"       , ObjectCFunction_create(context, &ObjectString_format));
    Dict_cinsert(ptable_ObjectDict.methods, "reverse"      , ObjectCFunction_create(context, &ObjectString_reverse));
    Dict_cinsert(ptable_ObjectDict.methods, "sub"          , ObjectCFunction_create(context, &ObjectString_sub));
    Dict_cinsert(ptable_ObjectDict.methods, "find"         , ObjectCFunction_create(context, &ObjectString_find));
    Dict_cinsert(ptable_ObjectDict.methods, "length"       , ObjectCFunction_create(context, &ObjectString_length));
    Dict_cinsert(ptable_ObjectDict.methods, "split"        , ObjectCFunction_create(context, &ObjectString_split));
    Dict_cinsert(ptable_ObjectDict.methods, "replace"      , ObjectCFunction_create(context, &ObjectString_replace));
    */

    Dict_cinsert(context->frames[0], "ObjectBool", (Object*) &ptable_ObjectBool);

  }

  /* Init ObjectType object class */ {

    ptable_ObjectType.methods = Object_create(context, __ObjectDict__, 0, 0);


    /*
    Dict_cinsert(ptable_ObjectDict.methods, "format"       , ObjectCFunction_create(context, &ObjectString_format));
    Dict_cinsert(ptable_ObjectDict.methods, "reverse"      , ObjectCFunction_create(context, &ObjectString_reverse));
    Dict_cinsert(ptable_ObjectDict.methods, "sub"          , ObjectCFunction_create(context, &ObjectString_sub));
    Dict_cinsert(ptable_ObjectDict.methods, "find"         , ObjectCFunction_create(context, &ObjectString_find));
    Dict_cinsert(ptable_ObjectDict.methods, "length"       , ObjectCFunction_create(context, &ObjectString_length));
    Dict_cinsert(ptable_ObjectDict.methods, "split"        , ObjectCFunction_create(context, &ObjectString_split));
    Dict_cinsert(ptable_ObjectDict.methods, "replace"      , ObjectCFunction_create(context, &ObjectString_replace));
    */

    Dict_cinsert(context->frames[0], "ObjectType", (Object*) &ptable_ObjectType);

  }

  /* Init Module object class */ {

    ptable_ObjectModule.methods = Object_create(context, __ObjectDict__, 0, 0);


    /*
    Dict_cinsert(ptable_ObjectDict.methods, "format"       , ObjectCFunction_create(context, &ObjectString_format));
    Dict_cinsert(ptable_ObjectDict.methods, "reverse"      , ObjectCFunction_create(context, &ObjectString_reverse));
    Dict_cinsert(ptable_ObjectDict.methods, "sub"          , ObjectCFunction_create(context, &ObjectString_sub));
    Dict_cinsert(ptable_ObjectDict.methods, "find"         , ObjectCFunction_create(context, &ObjectString_find));
    Dict_cinsert(ptable_ObjectDict.methods, "length"       , ObjectCFunction_create(context, &ObjectString_length));
    Dict_cinsert(ptable_ObjectDict.methods, "split"        , ObjectCFunction_create(context, &ObjectString_split));
    Dict_cinsert(ptable_ObjectDict.methods, "replace"      , ObjectCFunction_create(context, &ObjectString_replace));
    */

    Dict_cinsert(context->frames[0], "Module", (Object*) &ptable_ObjectModule);

  }

  /* Init Iterator object class */ {

    ptable_ObjectIterator.methods = Object_create(context, __ObjectDict__, 0, 0);

    Dict_cinsert(ptable_ObjectIterator.methods, "iterated", ObjectCFunction_create(context, &ObjectIterator_iterated));
    Dict_cinsert(ptable_ObjectIterator.methods, "next", ObjectCFunction_create(context, &ObjectIterator_next));
    Dict_cinsert(ptable_ObjectIterator.methods, "ended", ObjectCFunction_create(context, &ObjectIterator_ended));
    Dict_cinsert(ptable_ObjectIterator.methods, "index", ObjectCFunction_create(context, &ObjectIterator_index));

    Dict_cinsert(context->frames[0], "Iterator", (Object*) &ptable_ObjectIterator);

  }

  Dict_cinsert(context->root_frame, "proto_attributes_of", ObjectCFunction_create(context, &proto_attributes_of));
  Dict_cinsert(context->root_frame, "typename_of", ObjectCFunction_create(context, &typename_of));
  Dict_cinsert(context->root_frame, "exit", ObjectCFunction_create(context, &bi_exit));
  Dict_cinsert(context->root_frame, "prototype", ObjectCFunction_create(context, &prototype));

    return 1;
}

int NOJA_exit(Context *context) {

    Mem_release();

    Sources_unload_all(context);

    return 1;
}


/*
  Each time a source is loaded, it's
  data is pushed onto this stack.
*/

Source sources[128];
u32 source_count = 0;

int main(int argc, char **argv) {

  if(argc == 1) {
      printf("No file specified!\n");
      return 0;
  }

  char path[128];

  getcwd(path, 128);
  strcat(path, "/");
  strcat(path, argv[1]);

  Context context;

  NOJA_init(&context, path);

  NOJA_run(&context);

  NOJA_exit(&context);

  return 1;
}
