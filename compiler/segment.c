
#include "header.h"

Builder builder;

char Segment_resize(Segment *seg) {

    u32 size = 16; // base

    if(seg->size)
        size = seg->size*2;

    char *content = malloc(size);

    if(!content)
        return 0;

    memset(content, 0, size); // @TEMP

    memcpy(content, seg->content, seg->size);

    free(seg->content);

    seg->content = content;
    seg->size = size;

    return 1;
}

u32 Segment_insert_at(Segment *seg, u32 addr, void *s, u32 length) {

    memcpy(seg->content+addr, s, length);

}

u32 Segment_insert(Segment *seg, void *s, u32 length) {

    while(seg->size - seg->used <= length) {

        // the data segment needs to be resized. The string doesn't fit!

        if(!Segment_resize(seg)) {
            // couldn't resize data segment!
            // handle error @TODO
            assert(0);
            break;
        }

    }

    // offset if the string about to be inserted in the data segment relative to its start
    u32 offset = seg->used;

    memcpy(seg->content + offset, s, length);

    seg->used += length;

    return offset;
}

u32 Segment_insert_opcode(Segment *seg, char opcode) {

    while(seg->size - seg->used <= 1) {

        // the data segment needs to be resized. The string doesn't fit!

        if(!Segment_resize(seg)) {
            // couldn't resize data segment!
            // handle error @TODO
            assert(0);
            break;
        }

    }

    // offset if the string about to be inserted in the data segment relative to its start
    u32 offset = seg->used;

    seg->content[offset] = opcode;

    seg->used++;

    return offset;
}

u32 Segment_insert_padding(Segment *seg, u32 size) {

    char zero = 0;

    u32 offset = seg->used;

    for(u32 i = 0; i < size; i++)
        Segment_insert(seg, &zero, 1);

    return offset;
}

u32 Segment_addr(Segment *seg) {
    return seg->used;
}

void emit_lineno_of(Segment *seg, void *addr) {

  if(!addr) return;

  AST_Node *node = addr;
  u32 lineno = node->lineno;

  if(lineno == builder.lineno) return;

  Segment_insert_opcode(seg, OPCODE_LINENO);
  Segment_insert(seg, &node->lineno, 4);

  builder.lineno = lineno;
}