

#include "../../runtime/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <error.h>

typedef struct FileHandle FileHandle;

struct FileHandle {
    OBJECT_HEAD;
    char *path;
    char mode[3];
    u32 size;
    FILE *fp;
};


Object *FS_readDir(Object *parent, Object **argv, u32 argc) {

    if(argv == 0)
      return NOJA_False;

    if(argv[0]->type != __ObjectString__) {
      ctx_throw_exception(parent->context, Exception_TypeError);
      return NOJA_False;
    }

    ObjectString *path_obj = (ObjectString*) argv[0];

    DIR *dir_ptr;

    struct dirent *files;

    if((dir_ptr = opendir(path_obj->value)) == NULL) {

      return NOJA_False;

    }

    Object *array = Object_create(parent->context, __ObjectArray__, 0, 0);
    Object *temp;

    while((files = readdir(dir_ptr)) != NULL) {

      if(!strcmp(files->d_name, ".") || !strcmp(files->d_name, ".."))
        continue;

      temp = Object_create(parent->context, __ObjectDict__, 0, 0);

      Dict_cinsert(temp, "name", ObjectString_from_cstring(parent->context, files->d_name));
      Dict_cinsert(temp, "type", ObjectInt_from_cint(parent->context, (i64) files->d_type));

      ObjectArray_append(array, (Object*[]) {temp}, 1);

    }

    closedir(dir_ptr);

    return array;
}

void FileHandle_init(Object *self, Object **argv, u32 argc) {

    FileHandle *fh = (FileHandle*) self;

    if(!argc) return;

}

void FileHandle_destroy(Object *self) {

    FileHandle *fh = (FileHandle*) self;

    if(fh->path) free(fh->path);
    if(fh->fp) fclose(fh->fp);

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

    return ObjectString_wrap_cstring(parent->context, buffer, size);
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

    return ObjectInt_from_cint(parent->context, (i64) ftell(fh->fp));
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

Object *FileHandle_size(Object *parent, Object **argv, u32 argc) {

  if(!parent) {

    printf("ERROR :: Method used as stand-alone.\n");

    return 0;

  }

  FileHandle *fh = (FileHandle*) parent;

    if(!fh->fp)
      return NOJA_False;

    return ObjectInt_from_cint(parent->context, (i64) fh->size);
}

ObjectType ptable_FileHandle = {
    .type = &ptable_ObjectType,
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
    .operators = 0,
    .to_cbool = &return_1,
    .collectChildren = 0
};


Object *FS_open(Object *parent, Object **argv, u32 argc) {

    char *mode = "r";
    char *path = 0;
    int   path_size = -1;

    FileHandle  *handle = (FileHandle*) Object_create(parent->context, &ptable_FileHandle, 0, 0);

    switch(argc) {

        default:

        case 2:

        if(argv[1]->type != __ObjectString__) {
            ctx_throw_exception(parent->context, Exception_TypeError);
            return NOJA_False;
        }

        mode = ((ObjectString*) argv[1])->value;

        case 1:

        if(argv[0]->type != __ObjectString__) {
            ctx_throw_exception(parent->context, Exception_TypeError);
            return NOJA_False;
        }

        path      = ((ObjectString*) argv[0])->value;
        path_size = ((ObjectString*) argv[0])->size;

        break;


        case 0:

        return NOJA_False;

    }


    FILE *fp = fopen(path, mode);

    if(!fp) return NOJA_False;

    fseek(fp, 0, SEEK_END);
    handle->size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    handle->fp = fp;
    handle->path = malloc(path_size + 1);
    strcpy(handle->path, path);
    strcpy(handle->mode, mode);

    return (Object*) handle;
}

char Module_fs2_init(Object *dest) {

    Object *methods = Object_create(dest->context, __ObjectDict__, 0, 0);

    Dict_cinsert(methods, "size" , ObjectCFunction_create(dest->context, &FileHandle_size));
    Dict_cinsert(methods, "seek" , ObjectCFunction_create(dest->context, &FileHandle_seek));
    Dict_cinsert(methods, "tell" , ObjectCFunction_create(dest->context, &FileHandle_tell));
    Dict_cinsert(methods, "close", ObjectCFunction_create(dest->context, &FileHandle_close));
    Dict_cinsert(methods, "read" , ObjectCFunction_create(dest->context, &FileHandle_read));
    Dict_cinsert(methods, "write", ObjectCFunction_create(dest->context, &FileHandle_write));

    ptable_FileHandle.methods = methods;

    Dict_cinsert(dest, "open"		      , ObjectCFunction_create(dest->context, &FS_open));
    Dict_cinsert(dest, "readDir"		  , ObjectCFunction_create(dest->context, &FS_readDir));
    Dict_cinsert(dest, "SEEK_SET"     , ObjectInt_from_cint(dest->context, (i64) SEEK_SET));
    Dict_cinsert(dest, "SEEK_CUR"     , ObjectInt_from_cint(dest->context, (i64) SEEK_CUR));
    Dict_cinsert(dest, "SEEK_END"     , ObjectInt_from_cint(dest->context, (i64) SEEK_END));
    Dict_cinsert(dest, "stdin"        , ObjectInt_from_cint(dest->context, (i64) stdin));
    Dict_cinsert(dest, "stdout"       , ObjectInt_from_cint(dest->context, (i64) stdout));
    Dict_cinsert(dest, "stderr"       , ObjectInt_from_cint(dest->context, (i64) stderr));

    return 1;
}
