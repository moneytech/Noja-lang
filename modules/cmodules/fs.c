
#include "../../runtime/header.h"

typedef struct FileHandle FileHandle;

struct FileHandle {
    OBJECT_HEAD;
    char *path;
    char mode[3];
    FILE *fp;
};

void FileHandle_init(Object *self, Object **argv, u32 argc) {

    FileHandle *fh = (FileHandle*) self;

    if(!argc) return;



}

void FileHandle_destroy(Object *self) {

    FileHandle *fh = (FileHandle*) self;

    if(fh->path) free(fh->path);
    if(fh->fp) fclose(fh->fp);

}

Object *FileHandle_open(Object *parent, Object **argv, u32 argc) {

  if(!parent) {

    printf("ERROR :: Method used as stand-alone.\n");

    return 0;

  }

    FileHandle  *fh = (FileHandle*) parent;
    ObjectString      *obj_path = (ObjectString*) argv[0];
    ObjectString      *obj_mode = (ObjectString*) argv[1];

    FILE *fp = fopen(obj_path->value, obj_mode->value);

    if(!fp) return NOJA_False;

    fh->fp = fp;
    fh->path = malloc(obj_path->size+1);
    strcpy(fh->path, obj_path->value);
    strcpy(fh->mode, obj_mode->value);

    return NOJA_True;
}

Object *FileHandle_read(Object *parent, Object **argv, u32 argc) {

  if(!parent) {

    printf("ERROR :: Method used as stand-alone.\n");

    return 0;

  }

    FileHandle *fh = (FileHandle*) parent;

    int size;

    if(argc == 0) {

      int pos = ftell(fh->fp);

      fseek(fh->fp, 0, SEEK_END);
      size = ftell(fh->fp);
      fseek(fh->fp, pos, SEEK_SET);

    } else {

      size = ((ObjectInt*) argv[0])->value;

    }

    if(strcmp(fh->mode, "r") != 0 || !fh->fp)
        return NOJA_False;

    char *buffer = malloc(size+1);

    assert(buffer);

    fread(buffer, 1, size, fh->fp);

    return ObjectString_wrap_cstring(buffer, size);
}


Object *FileHandle_write(Object *parent, Object **argv, u32 argc) {

  if(!parent) {

    printf("ERROR :: Method used as stand-alone.\n");

    return 0;

  }

    FileHandle *fh = (FileHandle*) parent;
    ObjectString *obj_content = (ObjectString*) argv[0];

    if(strcmp(fh->mode, "w") != 0 || !fh->fp) {
        return NOJA_False;
    }

    fwrite(obj_content->value, 1, obj_content->size, fh->fp);

    return NOJA_True;
}

Object *FileHandle_seek(Object *parent, Object **argv, u32 argc) {

  if(!parent) {

    printf("ERROR :: Method used as stand-alone.\n");

    return 0;

  }

    FileHandle *fh = (FileHandle*) parent;
    ObjectInt *d = (ObjectInt*) argv[0];
    ObjectInt *q = (ObjectInt*) argv[1];

    if(!fh->fp)
        return NOJA_False;

    fseek(fh->fp, d->value, q->value);

    return NOJA_True;
}

Object *FileHandle_tell(Object *parent, Object **argv, u32 argc) {

  if(!parent) {

    printf("ERROR :: Method used as stand-alone.\n");

    return 0;

  }

    FileHandle *fh = (FileHandle*) parent;

    if(!fh->fp)
        return NOJA_False;

    return ObjectInt_from_cint((i64) ftell(fh->fp));
}

Object *FileHandle_close(Object *parent, Object **argv, u32 argc) {

  if(!parent) {

    printf("ERROR :: Method used as stand-alone.\n");

    return 0;

  }

    FileHandle *fh = (FileHandle*) parent;

    if(!fh->fp)
        return NOJA_False;

    fclose(fh->fp);
    free(fh->path);

    fh->path = 0;
    fh->fp   = 0;
    *fh->mode = 0;

    return NOJA_True;
}

ObjectType TypeTable_FileHandle = {
    .type = &TypeTable_ObjectType,
    .flags = 0,
    .methods = 0,
    .name  = "FileHandle",
    .size = sizeof(FileHandle),
    .free = &FileHandle_destroy,
    .select = 0,
    .insert = 0,
    .init   = &FileHandle_init,
    .call   = 0,
    .getAttr = 0,
    .setAttr = 0,
    .print  = 0,
    .expid  = 4,
    .to_cbool = &return_1,
    .collectChildren = 0
};

char Module_fs_init(Object *dest) {

    Object *methods = Object_create(__ObjectDict__, 0, 0);

    Dict_cinsert(methods, "seek", ObjectCFunction_create(&FileHandle_seek));
    Dict_cinsert(methods, "tell", ObjectCFunction_create(&FileHandle_tell));
    Dict_cinsert(methods, "open", ObjectCFunction_create(&FileHandle_open));
    Dict_cinsert(methods, "close", ObjectCFunction_create(&FileHandle_close));
    Dict_cinsert(methods, "read", ObjectCFunction_create(&FileHandle_read));
    Dict_cinsert(methods, "write", ObjectCFunction_create(&FileHandle_write));

    TypeTable_FileHandle.methods = methods;

    Dict_cinsert(dest, "SEEK_SET"     , ObjectInt_from_cint((i64) SEEK_SET));
    Dict_cinsert(dest, "SEEK_CUR"     , ObjectInt_from_cint((i64) SEEK_CUR));
    Dict_cinsert(dest, "SEEK_END"     , ObjectInt_from_cint((i64) SEEK_END));
    Dict_cinsert(dest, "stdin"        , ObjectInt_from_cint((i64) stdin));
    Dict_cinsert(dest, "stdout"       , ObjectInt_from_cint((i64) stdout));
    Dict_cinsert(dest, "stderr"       , ObjectInt_from_cint((i64) stderr));
    Dict_cinsert(dest, "FileHandle"   , (Object*) &TypeTable_FileHandle);

    return 1;
}
