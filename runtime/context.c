
#include "header.h"

u8 ctx_read_u8(Context *context) {
  u8 n = *(u8*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 1;
  return n;
}

u16 ctx_read_u16(Context *context) {
  u16 n = *(u16*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 2;
  return n;
}

u32 ctx_read_u32(Context *context) {
  u32 n = *(u32*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 4;
  return n;
}

u64 ctx_read_u64(Context *context) {
  u64 n = *(u64*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 8;
  return n;
}


i8 ctx_read_i8(Context *context) {
  i8 n = *(i8*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 1;
  return n;
}

i16 ctx_read_i16(Context *context) {
  i16 n = *(i16*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 2;
  return n;
}

i32 ctx_read_i32(Context *context) {
  i32 n = *(i32*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 4;
  return n;
}

i64 ctx_read_i64(Context *context) {
  i64 n = *(i64*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 8;
  return n;
}

f32 ctx_read_f32(Context *context) {
  f32 n = *(f32*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 4;
  return n;
}

f64 ctx_read_f64(Context *context) {
  f64 n = *(f64*) (context->source_stack[context->source_depth-1]->code + context->pc);
  context->pc += 8;
  return n;
}

char *ctx_read_string(Context *context) {

  u32 i = ctx_read_u32(context);

  return context->source_stack[context->source_depth-1]->data + i;
}

void ctx_create_activation_record(Context *context) {
  context->activation_records[context->activation_records_count].self = 0;
  context->activation_records[context->activation_records_count].bot = 0;
  context->activation_records[context->activation_records_count].top = 0;
  context->activation_records_count++;
}

void ctx_push_argument(Context *context, Object *object) {

  context->activation_records[context->activation_records_count-1].args[context->activation_records[context->activation_records_count-1].top++] = object;

}

void ctx_assign_argument(Context *context, char *name) {

  if(context->activation_records[context->activation_records_count-1].bot < context->activation_records[context->activation_records_count-1].top) {

      Dict_cinsert(
        context->frames[context->frame_depth-1],
        name,
        context->activation_records[context->activation_records_count-1].args[context->activation_records[context->activation_records_count-1].bot]);

      context->activation_records[context->activation_records_count-1].bot++;
  }
}

void ctx_push_self(Context *context, Object *object) {
  context->activation_records[context->activation_records_count-1].self = object;
}

Object *ctx_pop(Context *context) {
  return context->stack[--context->stack_size];
}

void ctx_pops(Context *context, int n) {
  context->stack_size -= n;
}

void ctx_push(Context *context, Object *object) {
  context->stack[context->stack_size++] = object;
}

Object *ctx_top(Context *context) {
  return context->stack[context->stack_size-1];
}

void ctx_call_pending(Context *context) {

  context->source_stack[context->source_depth]  = context->pending_call_offset.source;
  context->blocks[context->block_depth].beg     = context->pending_call_offset.addr;
  context->blocks[context->block_depth].type    = BLOCK_FUNC;
  context->blocks[context->block_depth].end     = context->pc;

  context->pc = context->blocks[context->block_depth].beg;

  context->block_depth++;
  context->source_depth++;

  context->pending_call_offset.source = 0;
  context->pending_call_offset.addr = 0;
}

void ctx_throw_exception(Context *context, int exception_code) {
  printf("Throwing exception\n");
  context->exception_code = exception_code;
}
