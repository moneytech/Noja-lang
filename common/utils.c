
#include "common.h"

void printb(char b) {

    char r;

    for(u32 i = 0, n = 1; i < 8; i++) {

        r = !!(n&b);

        if(r && 0) {
            printf("\x1B[36m" "%d" "\033[0m", r);
        } else {
            printf("%d", r);
        }

        n <<= 1;
    }
}
