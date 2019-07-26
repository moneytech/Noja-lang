

#include "header.h"

#define STACK_TOP context->stack[context->stack_size-1]
#define SOURCE_TOP context->source_stack[context->source_depth-1]

void NOJA_run(Context *context) {

    char opcode;
    char done = 0;

    /* Main loop */

    Register reg0, reg1, reg2, reg3;

    InstrInfo *instr_info;

    while(1) {

        if(context->pc >= context->source_stack[context->source_depth-1]->code_size) {
          ctx_throw_exception(context, InternalException_11);
          break;
        }

        opcode = context->source_stack[context->source_depth - 1]->code[context->pc++];

        /*
        instr_info = get_instrinfo_by_repr(opcode);

        printf("line %-3d :: %-4d: %-30s (stack size: %d", context->lineno, context->pc, instr_info->name, context->stack_size);

        if(context->activation_records_count > 0) {
          printf(", self = %p", context->activation_records[context->activation_records_count-1].self);
        }

        printf(")\n");
        */

        switch(opcode) {

            case OPCODE_LINENO:

            context->lineno = ctx_read_u32(context);

            //printf("line %d\n", context->lineno);

            break;

            case OPCODE_NOPE:

            break;

            case OPCODE_BUILD_CLASS:

            reg0._obj = Object_create(context, __ObjectType__, 0, 0);

            ((ObjectType*) reg0._obj)->name = "Class";
            ((ObjectType*) reg0._obj)->size = sizeof(ObjectIstance);
            //((ObjectType*) reg0._obj)->flags = 0;
            ((ObjectType*) reg0._obj)->methods = Object_create(context, __ObjectDict__, 0, 0);
            ((ObjectType*) reg0._obj)->free = Class_delete;
            ((ObjectType*) reg0._obj)->select = Class_select;
            ((ObjectType*) reg0._obj)->insert = Class_insert;
            ((ObjectType*) reg0._obj)->getAttr = Class_getAttr;
            ((ObjectType*) reg0._obj)->setAttr = Class_setAttr;
            ((ObjectType*) reg0._obj)->init = Class_init;
            ((ObjectType*) reg0._obj)->call = Class_call;
            ((ObjectType*) reg0._obj)->print = Class_print;
            ((ObjectType*) reg0._obj)->iter = 0;
            ((ObjectType*) reg0._obj)->next = 0;
            ((ObjectType*) reg0._obj)->operators = 0;
            ((ObjectType*) reg0._obj)->to_cbool = return_1;
            ((ObjectType*) reg0._obj)->collectChildren = Class_collectChildren;

            Dict_cinsert(((ObjectType*) reg0._obj)->methods, "__prototype__", reg0._obj);

            context->stack[context->stack_size++] = reg0._obj;

            // does ASSIGN pop?

            break;

            case OPCODE_PUSH_METHOD:

            reg0._str  = ctx_read_string(context); // name
            reg1._u32  = ctx_read_u32(context) + context->source_stack[context->source_depth-1]->function_space_addr; // addr

            reg2._obj = context->stack[context->stack_size-1];

            Dict_cinsert(
              ((ObjectType*) reg2._obj)->methods,
              reg0._str,
              ObjectFunction_create(context, reg1._u32, context->source_stack[context->source_depth-1]) // -1?
            );

            break;


            case OPCODE_IMPORT: {

              reg0._str = ctx_read_string(context); // path

              import_shared_library(reg0._str, context->frames[context->frame_depth-1]);

              // TODO


            } break;


            case OPCODE_IMPORT_AND_NAME: {

              reg0._str = ctx_read_string(context); // path
              reg1._str = ctx_read_string(context); // name

              reg2._obj = Object_create(context, __ObjectModule__, 0, 0);

              if(!import_shared_library(reg0._str, (reg2._module)->members)) {

                  ctx_throw_exception(context, Exception_ImportFailed);

                  break;
              }

              Dict_cinsert(context->frames[context->frame_depth-1], reg1._str, reg2._obj);

              // TODO

            } break;

            case OPCODE_PUSH_TRUE:  ctx_push(context, NOJA_True);    break;
            case OPCODE_PUSH_FALSE: ctx_push(context, NOJA_False);   break;

            case OPCODE_AREC_CREATE:

            ctx_create_activation_record(context);

            break;

            case OPCODE_PUSH_SELF:

            ctx_push_self(context, ctx_top(context));

            break;

            case OPCODE_TRY_ASSIGN_SELF:

            if(context->activation_records[context->activation_records_count-1].self != NULL) {

              Dict_cinsert(
                context->frames[context->frame_depth-1],
                "self",
                context->activation_records[context->activation_records_count-1].self
              );

            }

            break;

            case OPCODE_SET_ATTR:

            reg0._str = ctx_read_string(context); // name
            reg1._obj = ctx_pop(context); // value
            reg2._obj = ctx_pop(context); // self

            Object_setAttr(reg2._obj, reg0._str, reg1._obj);

            ctx_push(context, reg1._obj);

            break;

            case OPCODE_PUSH_ATTR:

            reg0._str = ctx_read_string(context);
            reg1._obj = ctx_pop(context);

            reg2._obj = Object_getAttr(reg1._obj, reg0._str);

            if(!reg2._obj) {
              ctx_throw_exception(context, Exception_AttributeError);
              break;
            }

            context->stack[context->stack_size] = reg2._obj;
            context->stack_size++;

            break;

            case OPCODE_SELECT:

            reg1._obj = ctx_pop(context); // key
            reg0._obj = ctx_pop(context); // src

            reg2._obj = Object_select(reg0._obj, reg1._obj);

            if(context->exception_code) break;

            if(context->pending_call_offset.source != 0) {

              ctx_call_pending(context);
              //ctx_pop(context); //?

            } else {

              ctx_push(context, reg2._obj);
            }

            break;

            case OPCODE_TRY_ASSIGN_ARG:

            reg1._str = ctx_read_string(context);

            ctx_assign_argument(context, reg1._str);

            /*

            if(context->activation_records[context->activation_records_count-1].bot < context->activation_records[context->activation_records_count-1].top) {

                Dict_cinsert(
                  context->frames[context->frame_depth-1],
                  reg1._str,
                  context->activation_records[context->activation_records_count-1].args[context->activation_records[context->activation_records_count-1].bot]);

                context->activation_records[context->activation_records_count-1].bot++;
            }
            */

            break;

            case OPCODE_PUSH_FUNC: {

                char *name;
                u32   addr;

                name = ctx_read_string(context);
                addr = ctx_read_u32(context);

                // get also the addr of its code block

                Object *function_object = ObjectFunction_create(
                  context,
                  context->source_stack[context->source_depth-1]->function_space_addr + addr,
                  context->source_stack[context->source_depth-1]
                );

                Dict_cinsert(context->frames[context->frame_depth-1], name, function_object);

                // build

            } break;

            case OPCODE_FUNC_BEG:

            context->frames[context->frame_depth++] = Object_create(context, __ObjectDict__, 0, 0);

            break;

            case OPCODE_FUNC_END:

            if(context->blocks[context->block_depth-1].type != BLOCK_FUNC) {

                ctx_throw_exception(context, InternalException_0);
                break;
            }

            context->pc = context->blocks[context->block_depth-1].end;

            context->activation_records_count--;
            context->frame_depth--;
            context->block_depth--;
            context->source_depth--;

            break;

            case OPCODE_PUSH_ARG:

            if(!context->stack_size) {
              ctx_throw_exception(context, InternalException_1);
                break;
            }

            ctx_push_argument(context, ctx_top(context));

            break;

            case OPCODE_CALL:

            if(context->activation_records[context->activation_records_count-1].self == NULL) {
                context->activation_records[context->activation_records_count-1].self = (Object*) context->module;
            }

            reg0._obj = Object_call(
              ctx_top(context),
              context->activation_records[context->activation_records_count-1].self,
              context->activation_records[context->activation_records_count-1].args  + context->activation_records[context->activation_records_count-1].bot,
              context->activation_records[context->activation_records_count-1].top   - context->activation_records[context->activation_records_count-1].bot
            );

            if(context->exception_code) break;

            ctx_pop(context);

            if(context->pending_call_offset.source != 0) {

              ctx_call_pending(context);

            } else {

              ctx_push(context, reg0._obj);
              context->activation_records_count--;
            }

            break;

            case OPCODE_DICT_CREATE:
            ctx_push(context, Object_create(context, __ObjectDict__, 0, 0));
            break;

            case OPCODE_INSERT:

            if(context->stack_size < 3) {
              ctx_throw_exception(context, InternalException_2);
              break;
            }

            reg0._obj = ctx_pop(context); // key
            reg1._obj = ctx_pop(context); // value
            reg2._obj = ctx_top(context); // src

            reg3._u8 = Object_insert(reg2._obj, reg0._obj, reg1._obj);

            if(context->exception_code) break;

            if(context->pending_call_offset.source != 0) {

              ctx_call_pending(context);
              ctx_pop(context); //?

            }

            break;

            case OPCODE_BUILD_ARRAY: {

                u32 n = ctx_read_u32(context);

                if(context->stack_size < n) {
                  ctx_throw_exception(context, InternalException_3);
                  break;
                }

                reg0._obj = Object_create(context, __ObjectArray__, 0, 0);

                for(u32 k = context->stack_size - n; k < context->stack_size; k++) {
                    ObjectArray_append(reg0._obj, context->stack + k, 1);
                }

                ctx_pops(context, n);
                ctx_push(context, reg0._obj);

            } break;

            case OPCODE_PUSH_I64:
            reg0._i64 = ctx_read_i64(context);
            ctx_push(context, ObjectInt_from_cint(context, reg0._i64));
            break;

            case OPCODE_PUSH_F64:
            reg0._f64 = ctx_read_f64(context);
            ctx_push(context, ObjectFloat_from_cdouble(context, reg0._f64));
            break;

            case OPCODE_PUSH_STRING:
            reg0._str = ctx_read_string(context);
            ctx_push(context, ObjectString_from_cstring(context, reg0._str));
            break;

            case OPCODE_PUSH_NAMED:

            reg1._str = ctx_read_string(context);

            reg0._obj = Dict_cselect(context->frames[context->frame_depth-1], reg1._str);

            if(!reg0._obj) {

              if(context->frames[context->frame_depth-1] != context->root_frame) {

                reg0._obj = Dict_cselect(
                  context->root_frame,
                  reg1._str
                );

              }

              if(!reg0._obj) {
                ctx_throw_exception(context, Exception_NameError);
                break;

              }

            }

            ctx_push(context, reg0._obj);

            break;

            case OPCODE_ASSIGN:

            reg0._str = ctx_read_string(context);

            Dict_cinsert(context->frames[context->frame_depth-1], reg0._str, ctx_top(context));

            break;

            case OPCODE_WHILE_BEG:

            /*

            context->blocks[context->block_depth].type = BLOCK_WHILE;
            context->blocks[context->block_depth].beg  = i-1+4;
            context->blocks[context->block_depth].end  = *(u32*) (context->source_stack[context->source_depth-1]->code+context->pc)+1;
            context->blocks[context->block_depth].end += i;

            context->block_depth++;

            i += 4;
            */

            reg0._u32 = ctx_read_u32(context);

            context->blocks[context->block_depth].type = BLOCK_WHILE;
            context->blocks[context->block_depth].end  = reg0._u32 + 1;
            context->blocks[context->block_depth].beg  = context->pc - 1;
            context->blocks[context->block_depth].end += context->pc - 4; // 4 is the size of the u32 just read

            context->block_depth++;

            break;

            case OPCODE_WHILE_END:

            context->pc = context->blocks[context->block_depth-1].beg;

            break;

            case OPCODE_BIFFP:

            if(!Object_to_cbool(context->stack[context->stack_size - 1])) {

                // am i sure i'm in a while block?

                context->pc = context->blocks[context->block_depth-1].end;
                context->block_depth--;
            }

            context->stack_size--;

            break;

            case OPCODE_BREAK:

            // find first while loop

            context->pc = context->blocks[context->block_depth-1].end;

            context->block_depth--;

            break;

            case OPCODE_CONTINUE:

            context->pc = context->blocks[context->block_depth-1].beg;

            break;

            case OPCODE_JUMP:

            context->pc = ctx_read_u32(context);

            break;

            case OPCODE_JUMPR: // OK

            reg0._u32 = ctx_read_u32(context);

            context->pc += reg0._u32 - 5 + 1;

            break;

            case OPCODE_JIFTP:

            if(context->stack_size == 0) {
              ctx_throw_exception(context, InternalException_4);
              break;
            }

            reg0._i32 = ctx_read_i32(context);

            if(Object_to_cbool(context->stack[context->stack_size-1]))

                context->pc += reg0._i32;

            context->stack_size--;

            break;

            case OPCODE_JIFFP:

            if(context->stack_size == 0) {
              ctx_throw_exception(context, InternalException_5);
              break;
            }

            reg0._i32 = ctx_read_i32(context);

            if(!Object_to_cbool(context->stack[context->stack_size-1]))

                context->pc += reg0._i32 - 4;

            context->stack_size--;

            break;

            case OPCODE_PRINT:

            if(context->stack_size == 0) {
              ctx_throw_exception(context, InternalException_6);
              break;
            }

            Object_print(context->stack[context->stack_size - 1]);


            if(context->pending_call_offset.source != 0)

              ctx_call_pending(context);


            break;

            case OPCODE_PRINTLN:

            printf("\n");

            break;

            case OPCODE_TYPE:

            if(context->stack_size == 0) {
              ctx_throw_exception(context, InternalException_7);
              break;
            }

            context->stack[context->stack_size-1] = (Object*) context->stack[context->stack_size-1]->type;

            break;

            case OPCODE_TYPE_NAME:

            if(context->stack_size == 0) {
              ctx_throw_exception(context, InternalException_8);
              break;
            }

            context->stack[context->stack_size-1] = ObjectString_from_cstring(context, context->stack[context->stack_size-1]->type->name);

            break;

            case OPCODE_POP:

            context->stack_size--;

            break;

            case OPCODE_ADD:
            case OPCODE_SUB:
            case OPCODE_MUL:
            case OPCODE_DIV:
            case OPCODE_GRT:
            case OPCODE_LSS:
            case OPCODE_GEQ:
            case OPCODE_LEQ:
            case OPCODE_EQL:
            case OPCODE_NQL:

            if(context->stack_size < 2) {
              ctx_throw_exception(context, InternalException_6);
              break;
            }

            reg1._obj = ctx_pop(context);
            reg0._obj = ctx_pop(context);

            switch (opcode) {
              case OPCODE_ADD: reg2._obj = Object_add(reg0._obj, reg1._obj); break;
              case OPCODE_SUB: reg2._obj = Object_sub(reg0._obj, reg1._obj); break;
              case OPCODE_MUL: reg2._obj = Object_mul(reg0._obj, reg1._obj); break;
              case OPCODE_DIV: reg2._obj = Object_div(reg0._obj, reg1._obj); break;
              case OPCODE_GRT: reg2._obj = Object_grt(reg0._obj, reg1._obj); break;
              case OPCODE_LSS: reg2._obj = Object_lss(reg0._obj, reg1._obj); break;
              case OPCODE_GEQ: reg2._obj = Object_geq(reg0._obj, reg1._obj); break;
              case OPCODE_LEQ: reg2._obj = Object_leq(reg0._obj, reg1._obj); break;
              case OPCODE_EQL: reg2._obj = Object_eql(reg0._obj, reg1._obj); break;
              case OPCODE_NQL: reg2._obj = (Object_eql(reg0._obj, reg1._obj) == NOJA_True) ? NOJA_False : NOJA_True; break;
            }

            if(!reg2._obj) {
              ctx_throw_exception(context, Exception_badOperation);
              break;
            }

            ctx_push(context, reg2._obj);

            break;

            case OPCODE_END:

            done = 1;

            break;

            case OPCODE_BREAKPOINT: {
              printf("============== Breakpoint ===============\n");
              printf("stack size: %d\n", context->stack_size);
              printf("=========================================\n");
            } break;

            default:

            ctx_throw_exception(context, InternalException_10);
            break;
        }

        if(context->exception_code || done) break;

        if(context->memory_man.current_head != context->memory_man.current_tail) {

            Mem_cycle(context);
        }
    }

    if(context->exception_code) {

      printf("Aborted at line %d (address %d): ", context->lineno, context->pc);

      switch (context->exception_code) {
        case Exception_ImportFailed: printf("Import failed"); break;
        case Exception_AttributeError: printf("object doesnt have this attribute"); break;
        case Exception_SetAttributeError: printf("can't set attribute of object"); break;
        case Exception_IndexError: printf("Bad index"); break;
        case Exception_ValueError: printf("bad value type"); break;
        case Exception_TypeError: printf("bad type"); break;
        case Exception_OutOfMemory: printf("out of memory"); break;
        case Exception_UncallableCalled: printf("uncallable object was called"); break;
        case Exception_NameError: printf("undeclared variable"); break;
        case Exception_InsertError: printf("bad insertion"); break;
        case Exception_SelectError: printf("bad selection"); break;
        case Exception_badOperation: printf("bad operation"); break;
        case Exception_UniterableIterated: printf("Uniterable iterated"); break;
        case Exception_ExplicitAbort: printf("exit() was called"); break;
        case InternalException_0: printf("instruction FUNC_END not in a function"); break;
        case InternalException_1: printf("instruction PUSH_ARG on empty stack"); break;
        case InternalException_2: printf("instruction INSERT on stack with size < 3"); break;
        case InternalException_3: printf("building array of size greather of the stack size"); break;
        case InternalException_4: printf("JIFTP on empty stack"); break;
        case InternalException_5: printf("JIFFP on empty stack"); break;
        case InternalException_6: printf("PRINT on empty stack"); break;
        case InternalException_7: printf("TYPE on empty stack"); break;
        case InternalException_8: printf("TYPE_NAME on empty stack"); break;
        case InternalException_9: printf("operation on stack with size < 2"); break;
        case InternalException_10: printf("unknown opcode"); break;
        case InternalException_11: printf("invalid address");


      }

      printf(".\n");

    } else {

      //printf("All good.\n");

    }

    return;
}
