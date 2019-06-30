
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>

char *getcwd(char *buf, size_t size);

#include "../common/common.h"

enum {
    VIEW_BITS = 1,
    VIEW_DATA = 2
};

u8 flags;

#include "print_code.c"

int main(int argc, char **argv) {

    if(argc == 1) {
        printf("No target.\n");
        return 0;
    }

    printf("About to disassemble '%s'.\n", argv[1]);

    char path[128];

    getcwd(path, 128);
    strcat(path, "/");
    strcat(path, argv[1]);

    flags = 0;

    for(u32 i = 2; i < argc; i++) {
        if(!strcmp("-b", argv[i])) {
            flags |= VIEW_BITS;
        } else if(!strcmp("-d", argv[i])) {
            flags |= VIEW_DATA;
        }
    }

    u32 size = 0;
    FILE *fp = fopen(path, "rb");

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *content = malloc(size);

    fread(content, 1, size, fp);

    fclose(fp);

    printf("file size is %d.\n", size);

    printf("\n");

    u32 code_size, data_size, function_space_size;

    data_size           = *(u32*) content;
    code_size           = *(u32*) (content + 4);
    function_space_size = *(u32*) (content + 8);

    if(flags & VIEW_BITS) {

        printf(" %-4d", 0); printb(content[0]); printf("  Data size (%d)\n", data_size);
        printf(" %-4d", 1); printb(content[1]); printf("\n");
        printf(" %-4d", 2); printb(content[2]); printf("\n");
        printf(" %-4d", 3); printb(content[3]); printf("\n");

        printf(" %-4d", 4); printb(content[4]); printf("  Code size (%d)\n", code_size);
        printf(" %-4d", 5); printb(content[5]); printf("\n");
        printf(" %-4d", 6); printb(content[6]); printf("\n");
        printf(" %-4d", 7); printb(content[7]); printf("\n");

        printf(" %-4d", 8); printb(content[4]); printf("  ObjectFunction space size (%d)\n", function_space_size);
        printf(" %-4d", 9); printb(content[5]); printf("\n");
        printf(" %-4d", 10); printb(content[6]); printf("\n");
        printf(" %-4d", 11); printb(content[7]); printf("\n");

    } else {

        printf(" %-4d", 0); printf("  Data size (%d)\n", data_size);
        printf(" %-4d", 4); printf("  Code size (%d)\n", code_size);
        printf(" %-4d", 8); printf("  Code size (%d)\n", function_space_size);

    }

    if(flags & VIEW_DATA) {

        printf("\n       DATA\n\n");

        u32 i = 0;
        char c;
        char *data = content + 12;
        char prev_was_zero = 1;

        while(i < data_size) {

            c = data[i++];

            if(prev_was_zero || (flags & VIEW_BITS))
                printf(" %-4d", i-1);

            if(flags & VIEW_BITS) {

                printb(c);

                printf("  ");
            }

            if(!c) {

                if(!(flags & VIEW_BITS)) {
                    printf("]\n");
                }

                prev_was_zero = 1;

            } else {

                if(!(flags & VIEW_BITS)) {

                    if(prev_was_zero)
                        printf(" [");

                    printf("%c", c);
                } else {
                    printf("[%c]", c);
                }

                prev_was_zero = 0;
            }

            if(flags & VIEW_BITS)
                printf("\n");
        }

    }

    print_code(content+12+data_size, content+12, code_size+function_space_size);    

    printf("\n");

    free(content);

    return 0;
}
