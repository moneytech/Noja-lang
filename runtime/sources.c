
#include "header.h"

void NOJA_SourceMap_free(SourceMap *map) {

  for(int i = 0; i < map->size; i++) {
    if(map->headers[i].path) {
      free(map->headers[i].path);
      free(map->headers[i].source->code);
      free(map->headers[i].source->data);
      free(map->headers[i].source);
    }
  }

  free(map->headers);
}

char NOJA_SourceMap_insert(SourceMap *map, char *path, Source *source) {

  if((map->size*2)/3 == map->used) {
    // resize
  }

  int h = Dict_chash(path);
  int p = h;

  int i = h & (map->size - 1);

  while(1) {

    if(map->headers[i].path) {
      if(strcmp(map->headers[i].path, path) == 0) {

        assert(0);

      }

    } else {

      map->headers[i].path = malloc(strlen(path)+1);
      strcpy(map->headers[i].path, path);

      map->headers[i].source = source;

    }

    p >>= 5;
    i = (h*5 + p + 1) & (map->size - 1);

  }

  assert(0); // unreachable
  return 0;

}

char NOJA_SourceMap_init(SourceMap *map) {
  map->headers = malloc(sizeof(SourceHeader) * 8);

  if(!map->headers)
    return 0;

  map->size = 8;
  map->used = 0;

  for(int i = 0; i < 8; i++) {
    map->headers[i].path = 0;
    map->headers[i].source = 0;
  }

  return 1;
}

Source *NOJA_SourceMap_seek(SourceMap *map, char *path) {

  int h = Dict_chash(path);
  int p = h;

  int i = h & (map->size - 1);

  while(1) {

    if(map->headers[i].path) {
      if(strcmp(map->headers[i].path, path) == 0)
        return map->headers[i].source;

    } else {

      return 0;

    }

    p >>= 5;
    i = (h*5 + p + 1) & (map->size - 1);

  }

  assert(0); // unreachable
  return 0;
}

void Sources_unload_all() {

  for(u32 i = 0; i < context.source_depth; i++) {
      free(context.source_stack[i]->data);
      free(context.source_stack[i]->code);
  }
}

char Sources_load(char *path) {

    FILE *fp = fopen(path, "rb");

    if(!fp)
        return 0;

    fseek(fp, 0, SEEK_END);
    sources[source_count].file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    fread(&sources[source_count].data_size, 4, 1, fp);
    fread(&sources[source_count].code_size, 4, 1, fp);
    fread(&sources[source_count].function_space_size, 4, 1, fp);

    sources[source_count].function_space_addr = sources[source_count].code_size;
    sources[source_count].code_size += sources[source_count].function_space_size;

    sources[source_count].data = (char*) malloc(sources[source_count].data_size);
    sources[source_count].code = (char*) malloc(sources[source_count].code_size);

    fread(sources[source_count].data, 1, sources[source_count].data_size, fp);
    fread(sources[source_count].code, 1, sources[source_count].code_size, fp);

    fclose(fp);

    source_count++;

    return 1;
}
