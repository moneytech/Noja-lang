
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "../common/common.h"

char *getcwd(char *buf, size_t size);

extern int yylineno;

char* duplicate_segment(const char *token, int size) {

  /*
    Untility.
    Used just by the lexer.
    Should shove it in an utility functions file.
  */

  char *dup = (char*) malloc(size + 1);

  if (!dup) { 
    // handle memory allocation error 
  }

  memcpy(dup, token, size);
  
  dup[size] = 0;
  
  return dup;
}

#include "ast.c"

#include "lex.yy.c"

#include "builder.c"

int main(int argc, char **argv) {
    
    char src_path[128];
    char dst_path[128];

    getcwd(src_path, 128);
    getcwd(dst_path, 128);

    if(argc > 2) {
      strcat(src_path, "/");
      strcat(src_path, argv[1]);
      strcat(dst_path, "/");
      strcat(dst_path, argv[2]);
    } else {
      printf("Missing path arguments.\n");
      return 0;
    }

    AST_Node *root = AST_Build(src_path);

    if(!root) {
        printf("Couldn't build AST.\n");
        return 0;
    }

    Compile(dst_path, root);

    return 0;    
}