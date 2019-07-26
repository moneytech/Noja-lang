
#include "header.h"

void Build_Exp_call(Segment *seg, AST_Node_Exp *exp) {

    AST_Node_ExpList *arg_list = (AST_Node_ExpList*) exp->r_exp;
    char opcode;

    AST_Node_Exp *l = (AST_Node_Exp*) exp->l_exp;

    Segment_insert_opcode(seg, OPCODE_AREC_CREATE);

    if(l->type == EXP_SELECT_ATTR) {

        Build_Exp(seg, l->l_exp);

        Segment_insert_opcode(seg, OPCODE_PUSH_SELF);

        AST_Node_Exp *r = (AST_Node_Exp*) l->r_exp;

        u32 n = Segment_insert(&builder.data, r->label, strlen(r->label)+1);

        Segment_insert_opcode(seg, OPCODE_PUSH_ATTR);
        Segment_insert(seg, &n, 4);

    } else {

        Build_Exp(seg, exp->l_exp);
    }

    if(arg_list) {

        AST_Node *arg = arg_list->head;

        while(arg) {
            Build_Exp(seg, arg);
            Segment_insert_opcode(seg, OPCODE_PUSH_ARG);
            Segment_insert_opcode(seg, OPCODE_POP);
            arg = arg->n_next;
        }

    }

    Segment_insert_opcode(seg, OPCODE_CALL);

}

void Build_ObjectArray(Segment *seg, AST_Node_Exp *exp) {

    if(!exp->value_array) {
        u32 n = 0;
        Segment_insert_opcode(seg, OPCODE_BUILD_ARRAY);

        Segment_insert(seg, &n, 4);
        return;
    }

    AST_Node *child = exp->value_array->head;

    while(child) {

        Build_Exp(seg, child);

        child = child->n_next;
    }

    Segment_insert_opcode(seg, OPCODE_BUILD_ARRAY);
    Segment_insert(seg, &exp->value_array->count, 4);

}

void Build_DictEntry(Segment *seg, AST_Node *node) {

    AST_Node_DictEntry *entry = (AST_Node_DictEntry*) node;

    Build_Exp(seg, entry->value);

    Segment_insert_opcode(seg, OPCODE_PUSH_STRING);

    u32 label_addr = Segment_insert(&builder.data, entry->label, strlen(entry->label)+1);
    Segment_insert(seg, &label_addr, 4);

    Segment_insert_opcode(seg, OPCODE_INSERT);

}

void Build_Dict(Segment *seg, AST_Node_Exp *exp) {

    AST_Node_Dict *dict = exp->value_dict;

    Segment_insert_opcode(seg, OPCODE_DICT_CREATE);

    AST_Node *entry = dict->head;

    while(entry) {

        Build_DictEntry(seg, entry);

        entry = entry->n_next;
    }
}

void build_function_head(Segment *seg, AST_Node_ObjectFunction *func) {

    // builds the segment of function that pushes the arguments onto the context frame

    u32 arg_name_data_addr;

    AST_Node_LabelList *args = (AST_Node_LabelList*) func->args;

    Segment_insert_opcode(seg, OPCODE_TRY_ASSIGN_SELF);

    if(args) {

        for(u32 i = 0, a; i < args->count; i++) {

            Segment_insert_opcode(seg, OPCODE_TRY_ASSIGN_ARG);

            arg_name_data_addr = Segment_insert(&builder.data, args->labels[i], strlen(args->labels[i])+1);

            Segment_insert(seg, &arg_name_data_addr, 4);
        }
    }

}

void Build_Method(Segment *seg, AST_Node *node) {

  AST_Node_ObjectFunction *func = (AST_Node_ObjectFunction*) node;

  u32 func_name_data_addr;
  u32 func_block_addr;
  int build_block_flags;

  Segment function_block_segment;

  function_block_segment.content = 0;
  function_block_segment.size = 0;
  function_block_segment.used = 0;

  /* Instruction to build the method object */

  // opcode

  Segment_insert_opcode(&builder.code, OPCODE_PUSH_METHOD);

  // insert method name into the data segment

  func_name_data_addr = Segment_insert(&builder.data, func->name, strlen(func->name)+1);

  // insert the addr of the name in the data segment onto the code segment
  // as operand 1 of OPCODE_PUSH_METHOD

  Segment_insert(&builder.code, &func_name_data_addr, 4);

  // start writing the method onto the function space

  // OPCODE_FUNC_BEG

  Segment_insert_opcode(&function_block_segment, OPCODE_FUNC_BEG);

  // instructions to load the arguments into the stack

  build_function_head(&function_block_segment, func);

  /* build the method block */

  build_block_flags = 0;

  // check if this method can return a value

  if(strcmp(func->name, "__print__") == 0 ||
     strcmp(func->name, "__init__") == 0) {

    build_block_flags = BLOCK_CANT_RETURN;
  }

  // build the block onto the function space

  Build_Block(&function_block_segment, func->block, build_block_flags);

  if(strcmp(func->name, "__print__") != 0 && strcmp(func->name, "__init__") != 0) {

    // if the method can return, return a true just in case the method didn't return

    Segment_insert_opcode(&function_block_segment, OPCODE_PUSH_TRUE);

  } else if(strcmp(func->name, "__init__") == 0) {

    // if its che constructor, return self

    Segment_insert_opcode(&function_block_segment, OPCODE_PUSH_NAMED);
    u32 n = Segment_insert(&builder.data, "self", sizeof("self"));
    Segment_insert(&function_block_segment, &n, 4);

  }

  // write OPCODE_FUNC_END

  Segment_insert_opcode(&function_block_segment, OPCODE_FUNC_END);

  // Built.

  // save the address of the actual function block on the function space segment

  func_block_addr = Segment_addr(&builder.function_space);

  // IMPORTANT NOTE: This must be done AFTER building the function block.
  // Lambdas could be built and pushed onto the function space
  // BEFORE this function was fully built, so the actual function block address
  // would be the size of the function_space segment after the block was built.

  // insert it onto the code segment as
  // operand 2 of OPCODE_PUSH_METHOD

  Segment_insert(&builder.code, &func_block_addr, 4);

  // copy the function segment onto the function space.

  Segment_merge(&builder.function_space, &function_block_segment);

  Segment_free(&function_block_segment);
}

void Build_ObjectFunction(Segment *seg, AST_Node *node) {

  AST_Node_ObjectFunction *func = (AST_Node_ObjectFunction*) node;

  emit_lineno_of(seg, node);

  u32 func_name_data_addr;
  u32 func_block_addr;
  Segment function_block_segment;
  function_block_segment.content = 0;
  function_block_segment.size = 0;
  function_block_segment.used = 0;

  Segment_insert_opcode(&builder.code, OPCODE_PUSH_FUNC);

  func_name_data_addr = Segment_insert(&builder.data, func->name, strlen(func->name)+1);

  Segment_insert(&builder.code, &func_name_data_addr, 4);

  Segment_insert_opcode(&function_block_segment, OPCODE_FUNC_BEG);

  
  build_function_head(&function_block_segment, func);

  Build_Block(&function_block_segment, func->block, 0);

  Segment_insert_opcode(&function_block_segment, OPCODE_PUSH_TRUE);
  Segment_insert_opcode(&function_block_segment, OPCODE_FUNC_END);

  func_block_addr = Segment_addr(&builder.function_space);

  Segment_insert(&builder.code, &func_block_addr, 4);

  Segment_merge(&builder.function_space, &function_block_segment);

  Segment_free(&function_block_segment);

}

void Build_Exp(Segment *seg, AST_Node *node) {

    AST_Node_Exp *exp = (AST_Node_Exp*) node;

    u32 offset;

    emit_lineno_of(seg, exp);

    switch(exp->type) {

        case EXP_TRUE:
        Segment_insert_opcode(seg, OPCODE_PUSH_TRUE);
        break;

        case EXP_FALSE:
        Segment_insert_opcode(seg, OPCODE_PUSH_FALSE);
        break;

        case EXP_DICT:
        Build_Dict(seg, exp);
        break;

        case EXP_ARRAY:
        Build_ObjectArray(seg, exp);
        break;

        case EXP_CALL:
        Build_Exp_call(seg, exp);
        break;

        case EXP_I64:
        Segment_insert_opcode(seg, OPCODE_PUSH_I64);
        Segment_insert(seg, &exp->value_i64, 8);
        break;

        case EXP_F64:
        Segment_insert_opcode(seg, OPCODE_PUSH_F64);
        Segment_insert(seg, &exp->value_f64, 8);
        break;

        case EXP_STRING:
        Segment_insert_opcode(seg, OPCODE_PUSH_STRING);
        offset = Segment_insert(&builder.data,
                                exp->value_string,
                                strlen(exp->value_string)+1); // BLEAHH @TODO
        Segment_insert(seg, &offset, 4);
        break;

        case EXP_LABEL:

        Segment_insert_opcode(seg, OPCODE_PUSH_NAMED);
        offset = Segment_insert(&builder.data, exp->label, strlen(exp->label)+1); // Bleahhhhhhhhhhh
        Segment_insert(seg, &offset, 4);

        break;

        case EXP_ADD:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_ADD);
        break;

        case EXP_SUB:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_SUB);
        break;

        case EXP_MUL:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_MUL);
        break;

        case EXP_DIV:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_DIV);
        break;

        case EXP_LSS:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_LSS);
        break;

        case EXP_GRT:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_GRT);
        break;

        case EXP_GEQ:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_GEQ);
        break;

        case EXP_LEQ:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_LEQ);
        break;

        case EXP_EQL:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_EQL);
        break;

        case EXP_NQL:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_NQL);
        break;

        case EXP_AND:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_AND);
        break;

        case EXP_OR:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_OR);
        break;

        case EXP_XOR:
        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_XOR);
        break;

        case EXP_SELECT:

        Build_Exp(seg, exp->l_exp);
        Build_Exp(seg, exp->r_exp);
        Segment_insert_opcode(seg, OPCODE_SELECT);

        break;

        case EXP_SELECT_ATTR:

        Build_Exp(seg, exp->l_exp);

        AST_Node_Exp *r = (AST_Node_Exp*) exp->r_exp;

        u32 n = Segment_insert(&builder.data, r->label, strlen(r->label)+1);

        Segment_insert_opcode(seg, OPCODE_PUSH_ATTR);
        Segment_insert(seg, &n, 4);

        break;

        case EXP_ASSIGN: {

            AST_Node_Exp *l, *r, *ll, *lr;
            u32 n;

            r  = (AST_Node_Exp*) exp->r_exp;
            l  = (AST_Node_Exp*) exp->l_exp;
            ll = (AST_Node_Exp*) l->l_exp;
            lr = (AST_Node_Exp*) l->r_exp;

            switch(l->type) {

                case EXP_LABEL:

                Build_Exp(seg, (AST_Node*) r);
                Segment_insert_opcode(seg, OPCODE_ASSIGN);
                n = Segment_insert(&builder.data, l->label, strlen(l->label)+1);
                Segment_insert(seg, &n, 4);

                break;

                case EXP_SELECT_ATTR:

                Build_Exp(seg, (AST_Node*) ll);
                Build_Exp(seg, (AST_Node*) r);
                Segment_insert_opcode(seg, OPCODE_SET_ATTR);
                n = Segment_insert(&builder.data, lr->label, strlen(lr->label)+1);
                Segment_insert(seg, &n, 4);

                break;

                case EXP_SELECT:

                Build_Exp(seg, (AST_Node*) ll);
                Build_Exp(seg, (AST_Node*) r);
                Build_Exp(seg, (AST_Node*) lr);
                Segment_insert_opcode(seg, OPCODE_INSERT);
                break;
            }
        }

        break;
    }

}

void Build_Print(Segment *seg, AST_Node *node) {

    emit_lineno_of(seg, node);

    AST_Node_Print *print = (AST_Node_Print*) node;

    AST_Node *arg = print->args;

    while(arg) {

        Build_Exp(seg, arg);
        Segment_insert_opcode(seg, OPCODE_PRINT);
        Segment_insert_opcode(seg, OPCODE_POP);

        arg = arg->n_next;
    }

    Segment_insert_opcode(seg, OPCODE_PRINTLN);

}

void Build_assign(Segment *seg, AST_Node *node) {

    AST_Node_Assign *a = (AST_Node_Assign*) node;
    AST_Node_Identifier *id = (AST_Node_Identifier*) a->identifier;

    if(!id->elem_count) {

        Build_Exp(seg, a->value);

        u32 label_addr = Segment_insert(&builder.data, id->base_label, strlen(id->base_label)+1);

        Segment_insert_opcode(seg, OPCODE_ASSIGN);
        Segment_insert(seg, &label_addr, 4);
        Segment_insert_opcode(seg, OPCODE_POP);
        return;
    }

    Segment_insert_opcode(seg, OPCODE_PUSH_NAMED);

    u32 label_addr = Segment_insert(&builder.data, id->base_label, strlen(id->base_label)+1);
    Segment_insert(seg, &label_addr, 4);

    for(u32 i = 0; i < id->elem_count; i++) {

        if(i == id->elem_count-1) {

            // last one

            if(id->elements[i].is_index) {

                // insert
                Build_Exp(seg, a->value);
                Build_Exp(seg, id->elements[i].index);

                Segment_insert_opcode(seg, OPCODE_INSERT);
                Segment_insert_opcode(seg, OPCODE_POP);
                //Segment_insert_opcode(seg, OPCODE_NOPE); // @TEMP

            } else {

                // set_attr

                Build_Exp(seg, a->value);

                Segment_insert_opcode(seg, OPCODE_SET_ATTR);
                label_addr = Segment_insert(&builder.data, id->elements[i].attr_name, strlen(id->elements[i].attr_name)+1);
                Segment_insert(seg, &label_addr, 4);

            }

        } else {

            if(id->elements[i].is_index) {

                // select
                Build_Exp(seg, id->elements[i].index);

                Segment_insert_opcode(seg, OPCODE_SELECT);

            } else {

                // push_attr
                Segment_insert_opcode(seg, OPCODE_PUSH_ATTR);
                label_addr = Segment_insert(&builder.data, id->elements[i].attr_name, strlen(id->elements[i].attr_name)+1);
                Segment_insert(seg, &label_addr, 4);

            }

        }

    }
}

void Build_Import(Segment *seg, AST_Node *node) {

  AST_Node_Import *import = (AST_Node_Import*) node;

  emit_lineno_of(seg, node);

  u32 as_addr, from_addr, name_addr;

  if(import->as)
    as_addr = Segment_insert(&builder.data, import->as, strlen(import->as)+1);

  name_addr = Segment_insert(&builder.data, import->name, strlen(import->name)+1);

  if(import->as) {

    Segment_insert_opcode(seg, OPCODE_IMPORT_AND_NAME);

    Segment_insert(seg, &name_addr, 4);
    Segment_insert(seg, &  as_addr, 4);

  } else {

    Segment_insert_opcode(seg, OPCODE_IMPORT);

    Segment_insert(seg, &name_addr, 4);

  }

}

void Build_Class(Segment *seg, AST_Node *node) {

  AST_Node_Class *class = (AST_Node_Class*) node;

  assert(class->members);

  Segment_insert_opcode(seg, OPCODE_BUILD_CLASS);

  AST_Node_Block *members = (AST_Node_Block*) class->members;

  AST_Node *member = members->head;

  while(member) {

    Build_Method(seg, member);

    member = member->n_next;
  }

  Segment_insert_opcode(seg, OPCODE_ASSIGN);

  u32 n = Segment_insert(&builder.data, class->name, strlen(class->name)+1);

  Segment_insert(seg, &n, 4);

  Segment_insert_opcode(seg, OPCODE_POP);

}

void Build_Block(Segment *seg, AST_Node *node, int flags) {

    AST_Node_Block *block = (AST_Node_Block*) node;

    AST_Node *_node = block->head;

    while(_node) {

        switch(_node->n_type) {

            case NODE_IMPORT:

            Build_Import(seg, _node);
            break;

            case NODE_FUNCTION:
            Build_ObjectFunction(seg, _node);
            break;

            case NODE_PRINT:
            Build_Print(seg, _node);
            break;

            case NODE_EXP:

            Build_Exp(seg, _node);
            Segment_insert_opcode(seg, OPCODE_POP);

            break;

            case NODE_IF: Build_If(seg, _node, flags); break;
            case NODE_WHILE: Build_While(seg, _node, flags); break;

            case NODE_BREAK:
            Segment_insert_opcode(seg, OPCODE_BREAK);
            break;

            case NODE_CONTINUE:
            Segment_insert_opcode(seg, OPCODE_CONTINUE);
            break;

            case NODE_BREAKPOINT:
            Segment_insert_opcode(seg, OPCODE_BREAKPOINT);
            break;

            case NODE_RETURN:

            if(flags & BLOCK_CANT_RETURN) {
              // this block can't return
              printf("ERROR :: Block can't return\n");
              assert(0);
            }

            Build_Exp(seg, ((AST_Node_Return*) _node)->value);
            Segment_insert_opcode(seg, OPCODE_FUNC_END);
            break;

            case NODE_CLASS:
            if(!(flags & BLOCK_IS_ROOT)) {
              // you can only declare a class at the root block
              printf("ERROR :: You can only declare a class in the root block\n");
              assert(0);
            }

            Build_Class(seg, _node);
            break;

        }

        _node = _node->n_next;
    }

}

void Build_While(Segment *seg, AST_Node *node, int flags) {

    AST_Node_While *_while = (AST_Node_While*) node;
    u32 a, b;

    /*
    OPCODE_WHILE_BEG,
    OPCODE_WHILE_END
    */

    emit_lineno_of(seg, node);

    Segment_insert_opcode(seg, OPCODE_WHILE_BEG);
    a = Segment_insert_padding(seg, 4);

    Build_Exp(seg, _while->condition);

    Segment_insert_opcode(seg, OPCODE_BIFFP);

    Build_Block(seg, _while->do_block, flags);

    b = Segment_addr(seg) - a;

    Segment_insert_at(seg, a, &b, 4);

    Segment_insert_opcode(seg, OPCODE_WHILE_END);
}

void Build_If(Segment *seg, AST_Node *node, int flags) {
    // OPCODE_JIFTP

    /*
        ..exp..
        JIFTP
        ..else..
        JUMP
        ..if...
        .......

        ...exp...
        JIFFP
        ...if...
        JUMP
        ...else...
    */

    u32 at, af, bt, bf;

    AST_Node_If *_if = (AST_Node_If*) node;

    Build_Exp(seg, _if->condition);
    Segment_insert_opcode(seg, OPCODE_JIFFP);
    at = Segment_insert_padding(seg, 4);

    Build_Block(seg, _if->if_block, flags);

    if(_if->else_block) {
        Segment_insert_opcode(seg, OPCODE_JUMPR);
        bt = Segment_insert_padding(seg, 4);
    }

    af = Segment_addr(seg) - at;
    Segment_insert_at(seg, at, &af, 4);

    if(_if->else_block) {

        Build_Block(seg, _if->else_block, flags);

        bf = Segment_addr(seg) - bt;
        Segment_insert_at(seg, bt, &bf, 4);
    }

}


char *Build(AST_Node *root, u32 *e_size) {

    memset(&builder, 0, sizeof(Builder));

    Build_Block(&builder.code, root, BLOCK_IS_ROOT);

    Segment_insert_opcode(&builder.code, OPCODE_END);

    /*
    printf("data....................%d / %d\n", builder.data.used, builder.data.size);
    printf("code_start..............%d / %d\n", builder.code_start.used, builder.code_start.size);
    printf("code....................%d / %d\n", builder.code.used, builder.code.size);
    printf("function_space..........%d / %d\n", builder.function_space.used, builder.function_space.size);
    */

    u32 size = builder.function_space.used + builder.data.used + builder.code.used + 12;

    char *content = malloc(size);

    *(u32*) (content + 0) = builder.data.used;
    *(u32*) (content + 4) = builder.code_start.used + builder.code.used;
    *(u32*) (content + 8) = builder.function_space.used;

    Segment *segs[4] = {
        &builder.data,
        &builder.code_start,
        &builder.code,
        &builder.function_space
    };

    for(u32 i = 0, j = 12; i < 4; i++) {

        memcpy(content + j, segs[i]->content, segs[i]->used);

        j += segs[i]->used;
    }

    *e_size = size;

    return content;
}

void Compile(char *path, AST_Node *root) {

    u32 size;
    char *content;

    content = Build(root, &size);

    FILE *fp = fopen(path, "wb");

    fwrite(content, 1, size, fp);

    free(content);
    free(builder.data.content);
    free(builder.code_start.content);
    free(builder.code.content);
    free(builder.function_space.content);

    fclose(fp);
}
