
## Who am I and why did I do this

I'm a CS student and this is my hobby project. I am no experienced programmer nor am a compiler/interpreter specialist (?). I just thought that it would be cool and interesting to build an interpreter, so I did it. I've documented the project extensively since I thought it's good practice and it may be helpful to others as a possible approach to doing this, and to me if anybody has some advice.

I heavily used CPython as reference.

---

## Objects

**Everything in Noja is an object!**

Every value that must be accessible from the VM must be wrapped into an Object structure. This allows the "native" polymorphism of the language and garbage collection.

The object structure for a value contains header members and members necessary to represent the value. Since the header section of each object overlaps, they can be masked with a generic structure that consists only of the header. This way, we can treat different objects the same way.

The object mask structure is defined as follows

```C
struct Object {
  ObjectType *type;
  Object *forwarding_refr;
  u8 flags;
};
```

The first member represents the type of the object. Keeping track of its type is necessary to cast the structure back to its original form [wtf?]. It's a pointer to a "Type object" which represents the type of the data and contains information on how to process it (it's pretty much the same as the C++'s vtable). The second member is necessary for garbage collection. The last member contains flags (duh).

As an example, the string object is defined as

```C
struct ObjectString {
  ObjectType *type;
  Object *forwarding_refr;
  u8 flags;
  char *value;
  u32 size, hash;
};
```

**NOTE:** This is pretty much how CPython does it too.

---

## The Type object

A type object is a type of object which contains references to the routines necessary to its "usage".

```C
struct ObjectType {

  ObjectType *type;
  Object *forwarding_refr;
  u8 flags;

  /* Info */

  char *name;
  u32   size;

  /* Methods */

  Object *methods;
  void    (*free)   (Object*);
  void    (*init)   (Object*, Object**, u32);
  char    (*insert) (Object*, Object*, Object*);
  Object *(*select) (Object*, Object*);
  void    (*setAttr)(Object*, char*, Object*);
  Object *(*getAttr)(Object*, char*);
  Object *(*call)   (Object*, Object*, Object**, u32);
  void    (*print)  (Object*);

  /* Casters */

  char (*to_cbool)(Object*);

  /* For operations */

  u32 expid;

  /* Garbage collector */

  void (*collectChildren)(Object*);
};
```

Built-in type objects are allocated statically and on initialization referenced by the context frame. [note out of place]

---

## Memory management and garbage collection

On initialization of the VM, a chunk of space is dynamically allocated. The majority of object are allocated onto this heap. If the heap is full while an object allocation occurs, another chunk is allocated (with double the size of the first one) and it is linked to the previous one.

At the end of each iteration of the main loop of execution, the state of the heap is checked: if there is a linked heap, then the garbage collection occurs.

The GC is an implementation of the stop-and-copy algorithm. Before dead object collection, a heap is created with size equal to the sum of all sizes of the linked heaps [But the heap always grows! Why do this?]. Then, the GC walks the objects tree (the roots are the context frames and the stack) copying each object onto the new heap, marking the original memory location as moved and storing at the old location the pointer to the new location. Then the GC tries to move the objects pointed by the just-moved object [also the type object]. If a child was already moved, the pointer of the parent is updated. In this way, at the end of the collection process, all live objects are copied onto the new stack and all pointers are updated. Ultimately, the heaps are substituted with the new one. The old heaps are iterated and the destructor routines of each object are called [what if the type object was moved?].

[Why not collect dead objects on a failed allocation?]

NOTE: Yes, dividing objects in generations would very likely decrease noticeably collection times, but the current implementation is much simpler [...].

---

## Execution context and main loop

    ..

---

## Math operations

Each built-in object type has an identifier (defined into its type object as expid) which identifies it while running math/logic operations. For each operation a matrix is statically allocated. While operating on two objects, their expids are used to select from the matrix relative to the operation a function address, which will get the objects references and return a newly allocated object. If the expid of an object is NULL, or there is no function address associated with their expids, then a BadOperation exception is thrown.

---

## Writing modules

    ..
