
void print_next_u32(char *content, u32 i) {

    u32 n = *(u32*) (content + i);

    if(!(flags & VIEW_BITS)) {
        printf("  %d", n);
        return;
    }

    printf("\n");

    printf(" %-4d", i+0); printb(content[i+0]);  printf("  %d\n", n);
    printf(" %-4d", i+1); printb(content[i+1]);  printf("\n");
    printf(" %-4d", i+2); printb(content[i+2]);  printf("\n");
    printf(" %-4d", i+3); printb(content[i+3]);
}

void print_next_i32(char *content, u32 i) {

    i32 n = *(i32*) (content + i);

    if(!(flags & VIEW_BITS)) {
        printf("  %d", n);
        return;
    }

    printf("\n");

    printf(" %-4d", i+0); printb(content[i+0]);  printf("  %d\n", n);
    printf(" %-4d", i+1); printb(content[i+1]);  printf("\n");
    printf(" %-4d", i+2); printb(content[i+2]);  printf("\n");
    printf(" %-4d", i+3); printb(content[i+3]);
}

void print_next_i64(char *content, u32 i) {

    i64 n = *(i64*) (content + i);

    if(!(flags & VIEW_BITS)) {
        printf("  %ld", n);
        return;
    }

    printf("\n");

    printf(" %-4d", i+0); printb(content[i+0]);  printf("  %ld\n", n);
    printf(" %-4d", i+1); printb(content[i+1]);  printf("\n");
    printf(" %-4d", i+2); printb(content[i+2]);  printf("\n");
    printf(" %-4d", i+3); printb(content[i+3]);  printf("\n");
    printf(" %-4d", i+4); printb(content[i+4]);  printf("\n");
    printf(" %-4d", i+5); printb(content[i+5]);  printf("\n");
    printf(" %-4d", i+6); printb(content[i+6]);  printf("\n");
    printf(" %-4d", i+7); printb(content[i+8]);

}

void print_next_f64(char *content, u32 i) {

    f64 n = *(f64*) (content + i);

    if(!(flags & VIEW_BITS)) {
        printf("  %lf", n);
        return;
    }

    printf("\n");

    printf(" %-4d", i+0); printb(content[i+0]);  printf("  %lf\n", n);
    printf(" %-4d", i+1); printb(content[i+1]);  printf("\n");
    printf(" %-4d", i+2); printb(content[i+2]);  printf("\n");
    printf(" %-4d", i+3); printb(content[i+3]);  printf("\n");
    printf(" %-4d", i+4); printb(content[i+4]);  printf("\n");
    printf(" %-4d", i+5); printb(content[i+5]);  printf("\n");
    printf(" %-4d", i+6); printb(content[i+6]);  printf("\n");
    printf(" %-4d", i+7); printb(content[i+8]);

}

void print_code(char *code, char *data, u32 size) {

    printf("\n       CODE\n\n");

    u8 byte;
    u32 i = 0;

    InstrInfo *instr_info;

    while(i < size) {

        byte = code[i++];

        instr_info = get_instrinfo_by_repr(byte);

        if(!instr_info) {
          printf("failed on %d\n", byte);
          return 0;
        }

        printf(" %-4d", i-1);

        if(flags & VIEW_BITS) {
            printb(byte);
        }

        printf("  %-10s", instr_info->name);

        for(int k = 0, j; k < instr_info->arg_count; k++) {
          switch(instr_info->arg_types[k]) {
            //case OPT_U8:  print_next_u8(code, i); i += 1;break;
            //case OPT_U16: print_next_u16(code, i); i += 2; break;
            case OPT_U32: print_next_u32(code, i); i += 4; break;
            //case OPT_U64: print_next_u64(code, i); i += 8; break;

            //case OPT_I8:  print_next_i8(code, i); i += 1; break;
            //case OPT_I16: print_next_i16(code, i); i += 2; break;
            case OPT_I32: print_next_i32(code, i); i += 4; break;
            case OPT_I64: print_next_i64(code, i); i += 8; break;

            //case OPT_F32: print_next_f32(code, i); i += 4; break;
            case OPT_F64: print_next_f64(code, i); i += 8; break;

            case OPT_STRING:
              j = *(u32*)(code + i);
              printf(" \"%s\"", data + j);
              i += 4;
            break;
          }
        }

        printf("\n");

    }
}
