
#include "header.h"

Memory_Manager memory_man;

Heap *Mem_Heap_create(u32 size) {

    Heap *heap;

    heap = (Heap*) malloc(16 + size);

    if(!heap) return 0;

    heap->used = 0;
    heap->size = size;
    heap->next = 0;

    return heap;
}

void Mem_init(u32 size) {

    Heap *heap = Mem_Heap_create(size);

    if(!heap) {
      ctx_throw_exception(&context, Exception_OutOfMemory);
      return;
    }

    memory_man.current_head     = heap;
    memory_man.current_tail     = heap;
    memory_man.temp             = 0;
    memory_man.total_heaps_size = size;

}

void Mem_release() {

    Mem_HeapList_destroy(memory_man.current_head);

}

void Mem_HeapList_destroy(Heap *head) {

    u32 i;
    Object *object;
    Heap *next;

    Heap *heap  = head;

    while(heap) {

        i = 0;

        while(i < heap->used) {

            object = (Object*) (heap->chunk + i);

            if(object->flags & OBJ_IS_FORWARDING_REFR) {

                // Object was moved

            } else {

              if(object->type->flags & OBJ_IS_FORWARDING_REFR) {
                object->type = (ObjectType*) object->type->forwarding_refr;
              }

              Object_destroy(object);
            }

            i += Object_size(object);
        }

        heap = heap->next;
    }

    /*
      Heap chunks bust be freed
      at once since objects
      could refer to types
      in other chunks.

    */

    heap = head;

    while(heap) {

      next = heap->next;

      free(heap);

      heap = next;
    }
}

void Mem_collect(Object **object_refr) {

    Object *object = *object_refr;

    if(!object)
        return;

    if(!(object->flags & OBJ_IS_GC_COLLECTABLE)) {

        Object_collectChildren(object);

        return;
    }

    if(object->flags & OBJ_IS_FORWARDING_REFR) {

        *object_refr = object->forwarding_refr;

        return;
    }

    u32 obj_size = Object_size(object);

    memcpy(memory_man.temp->chunk + memory_man.temp->used, object, obj_size);

    Object *object_copy = (Object*) (memory_man.temp->chunk + memory_man.temp->used);

    memory_man.temp->used += obj_size;

    object->flags |= OBJ_IS_FORWARDING_REFR;
    object->forwarding_refr = object_copy;

    *object_refr = object_copy;

    Object_collectChildren(object_copy);
}

void Mem_cycle() {

    u32 new_size = memory_man.total_heaps_size;

    memory_man.temp = Mem_Heap_create(new_size);

    if(!memory_man.temp) {
      ctx_throw_exception(&context, Exception_IndexError);
      return;
    }

    memory_man.total_heaps_size = new_size;

    for(u32 i = 0; i < context.frame_depth; i++)
        Mem_collect(&context.frames[i]);

    for(u32 i = 0; i < context.stack_size; i++)
        Mem_collect(&context.stack[i]);

    for(u32 j = 0; j < context.activation_records_count; j++) {
        Mem_collect(&context.activation_records[j].self);
        for(u32 i = context.activation_records[j].bot; i < context.activation_records[j].top + 1; i++)
            Mem_collect(&context.activation_records[j].args[i]);
    }

    for(u32 j = 0; j < context.root_count; j++)
        Mem_collect(context.roots[j]);

    Mem_HeapList_destroy(memory_man.current_head);

    memory_man.current_head = memory_man.temp;
    memory_man.current_tail = memory_man.temp;
    memory_man.temp = 0;

}

void *Mem_allocate(u32 size) {

    Heap *heap = memory_man.current_tail;

    if(size >= (heap->size - heap->used)) {

        // chain a new heap

        u32 new_size = 4096;

        while(new_size < size)

              new_size <<= 1;

        memory_man.total_heaps_size += new_size;
        heap->next = Mem_Heap_create(new_size); // Out of memory?

        if(!heap->next) {
          ctx_throw_exception(&context, Exception_IndexError);
          return 0;
        }

        memory_man.current_tail = heap->next;

        heap = heap->next;

    }

    char *addr = heap->chunk + heap->used;

    heap->used += size;

    memset(addr, 0, size);

    return addr;
}
