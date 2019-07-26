
#include "../header.h"

ObjectType ptable_ObjectDict = {
    .type = &ptable_ObjectType,
    .flags = 0,
    .name  = "Dict",
    .size = sizeof(ObjectDict),
    .methods = 0,
    .free = &Dict_destroy,
    .init   = &Dict_init,
    .call   = 0,
    .insert = &Dict_insert,
    .select = &Dict_select,
    .print  = &Dict_print,
    .iter = 0,
    .next = 0,
    .get_raw_repr = 0,
    .get_raw_repr_size = 0,
    .operators = 0,
    .to_cbool = &Dict_to_cbool,
    .collectChildren = &Dict_collectChildren
};

/* === Operators === */

Object *Dict_eql(Object *a, Object *b) {
    return NOJA_False;
}

/* === C Handlers === */

Object *Dict_cselect(Object *object, char *name) {

    ObjectDict *dict = (ObjectDict*) object;

    u32 x = Dict_chash(name);
    u32 p = x;
    u32 i = x & (dict->size - 1);

    while(1) {

        if(dict->buckets[i].state == BUCKET_UNUSED) {

            // empty

            return 0;

        } else {

            // used

            if(strcmp(dict->buckets[i].name, name) == 0) {

                // Found it!

                return dict->buckets[i].ref;

            }

        }

        p >>= 1;
        i = (i*5 + p + 1) & (dict->size - 1);
    }

    assert(0);
    /* Unreachable */
}

void Dict_cremove(Object *object, char *name) {

    ObjectDict *dict = (ObjectDict*) object;

    u32 x = Dict_chash(name);
    u32 p = x;
    u32 i = x & (dict->size - 1);

    while(1) {

        if(dict->buckets[i].state == BUCKET_UNUSED) {

            // empty
            return;

        } else {

            // used

            if(strcmp(dict->buckets[i].name, name) == 0) {

                // Found it!
                dict->buckets[i].name[0]  = 0;
                dict->buckets[i].state = BUCKET_CLEARED;
                dict->buckets[i].ref = 0;

                return;
            }
        }

        p >>= 1;
        i = (i*5 + p + 1) & (dict->size - 1);
    }

    assert(0);
    /* Unreachable */

}


/* === Handlers === */


void Dict_destroy(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    free(dict->buckets);
}

void Dict_print(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    printf("{");
    for(u32 i = 0, j = 0; i < dict->size; i++) {

        if(i == 0) printf("\n");

        if(dict->buckets[i].state == BUCKET_USED) {
            printf("%-20s: %s", dict->buckets[i].name, dict->buckets[i].ref->type->name);
            //Object_print(dict->buckets[i].ref);
            if(j < dict->used-1) {
                printf(", ");
            }
            printf("\n");
            j++;
        }
    }
    printf("}");
}

void Dict_collectChildren(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    for(u32 i = 0; i < dict->size; i++) {
        if(dict->buckets[i].state == BUCKET_USED) {
            Mem_collect(&dict->buckets[i].ref);
        }
    }
}

char Dict_to_cbool(Object *self) {
    return ((ObjectDict*) self)->used != 0;
}

void Dict_init(Object *self, Object **argv, u32 argc) {

    ObjectDict *dict = (ObjectDict*) self;

    dict->buckets = malloc(sizeof(ObjectBucket)*8);
    dict->size = 8;

    memset(dict->buckets, 0, sizeof(ObjectBucket)*8);

}

u32 Dict_chash(char *string) {

    char c;
    u32 i = 0, x = 0;

    while((c = string[i++]))
        x += c*c*i;

    return x;
}

char Dict_insert(Object *self, Object *key, Object *value) {

    Dict_cinsert(self, ((ObjectString*) key)->value, value);
    return 1;
}

void Dict_resize(Object *self) {

    ObjectDict *dict = (ObjectDict*) self;

    ObjectBucket *old_buckets  = dict->buckets;
    u32           old_size     = dict->size;

    dict->buckets = calloc(dict->size*2, sizeof(ObjectBucket));
    dict->size *= 2;

    for(u32 i = 0; i < old_size; i++)
        if(old_buckets[i].state == BUCKET_USED)
            Dict_cinsert(self, old_buckets[i].name, old_buckets[i].ref);

    free(old_buckets);

}

void Dict_cinsert(Object *object, char *name, Object *child) {

    ObjectDict *dict = (ObjectDict*) object;

    if(dict->used == dict->size - 1)
        Dict_resize(object);

    char bucket_already_there = 0;

    u32 x = Dict_chash(name);
    u32 p = x;
    u32 i = x & (dict->size - 1);

    while(1) {

        if(dict->buckets[i].state == BUCKET_UNUSED) {

            // empty

            break;

        } else if(dict->buckets[i].state == BUCKET_CLEARED) {

            break;

        } else {

            // used

            if(strcmp(dict->buckets[i].name, name) == 0) {

                bucket_already_there = 1;
                // already here! Overwrite!
                // insert
                break;
            }
        }

        p >>= 1;
        i = (i*5 + p + 1) & (dict->size - 1);
    }

    dict->buckets[i].state = BUCKET_USED;
    strcpy(dict->buckets[i].name, name);
    dict->buckets[i].ref   = child;

    if(!bucket_already_there)
        dict->used++;

}

Object *Dict_select(Object *self, Object *key) {

    return Dict_cselect(self, ((ObjectString*) key)->value);
}

/* === Methods === */