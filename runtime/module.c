
#include "header.h"
#include <dlfcn.h>

char import_shared_library(char *name, Object *dest) {

    char buffer[1024];
    char path[32];

    sprintf(buffer, "Module_%s_init", name);
    sprintf(path, "modules/lib%s.so", name);

    void *handle;
    char *error;

    handle = dlopen(path, RTLD_NOW | RTLD_NODELETE);

    if (!handle) {
        fputs (dlerror(), stderr);
        return 0;
    }

    char (*initializer)(Object *dest);

    initializer = (char (*)(Object*)) dlsym(handle, buffer);

    if ((error = dlerror()) != NULL)  {
        printf("\n");
        fputs(error, stderr);
        printf("\n");
        dlclose(handle);
        return 0;
    }

    char r = initializer(dest);

    dlclose(handle);

    return r;
}
