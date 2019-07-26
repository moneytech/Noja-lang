
#include "../../runtime/header.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct Socket Socket;

struct Socket {

  OBJECT_HEAD;

  int fd;
  int port;
  struct sockaddr_in addr;
};

typedef struct Connection {
  OBJECT_HEAD;
  int fd;
} Connection;

extern ObjectType ptable_Connection;
extern ObjectType ptable_Socket;

void Socket_init(Object *self, Object **argv, u32 argc) {

  /* Socket(AF_INET, SOCK_STREAM, 0) */

  int domain, type, protocol;

  switch(argc) {

    case 0:
    domain   = AF_INET;
    type     = SOCK_STREAM;
    protocol = 0;
    break;

    default:

    case 3:
    assert(argv[2]);
    assert(argv[2]->type == __ObjectInt__);
    protocol = (int) ((ObjectInt*) argv[2])->value;

    case 2:
    assert(argv[1]);
    assert(argv[1]->type == __ObjectInt__);
    type   = (int) ((ObjectInt*) argv[1])->value;

    case 1:
    assert(argv[0]);
    assert(argv[0]->type == __ObjectInt__);
    domain = (int) ((ObjectInt*) argv[0])->value;

    break;
  }

  Socket *sock = (Socket*) self;

  sock->fd = socket(domain, type, protocol);

  assert(sock->fd != -1);

}

void Socket_destroy(Object *self) {

  Socket *sock = (Socket*) self;

  close(sock->fd);
}

Object *Socket_listen(Object *self, Object **argv, u32 argc) {

  Socket *sock = (Socket*) self;

  int opt = 1;
  int port = 3000;
  int recieve_queue_size = 5;

  // set args

  switch(argc) {
    case 2:

    assert(argv[1]->type == __ObjectInt__);

    if(((ObjectInt*) argv[1])->value > 0)

      recieve_queue_size = (int) ((ObjectInt*) argv[1])->value;

    case 1:

    assert(argv[0]->type == __ObjectInt__);

    if(((ObjectInt*) argv[0])->value > 0)

      port = (int) ((ObjectInt*) argv[0])->value;
    break;
  }

  if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,  &opt, sizeof(opt))) {
    return NOJA_False;
  }

  sock->addr.sin_family = AF_INET;
  sock->addr.sin_addr.s_addr = INADDR_ANY;
  sock->addr.sin_port = htons(port);

  if(bind(sock->fd, (struct sockaddr*) &sock->addr, sizeof(sock->addr)) < 0) {
    // error. Couldn't bind
    return NOJA_False;
  }

  if(listen(sock->fd, recieve_queue_size) < 0) {

    return NOJA_False;
  }

  return NOJA_True;
}

Object *Socket_accept(Object *self, Object **argv, u32 argc) {

  Socket *sock = (Socket*) self;

  socklen_t addrlen = sizeof(struct sockaddr_in);

  int new_socket = accept(sock->fd, (struct sockaddr*) &sock->addr, &addrlen);

  if(new_socket < 0) {
    return NOJA_False;
  }

  Connection *conn = (Connection*) Object_create(self->context, &ptable_Connection, 0, 0);
  conn->fd = new_socket;

  return (Object*) conn;
}

char Socket_to_cbool(Object *self) {
  return ((Socket*) self)->fd == -1;
}

Object *Connection_close(Object *self, Object **argv, u32 argc) {

  Connection *conn = (Connection*) self;

  if(conn->fd < 0)
    return NOJA_False;

  close(conn->fd);

  conn->fd = -1;

  return NOJA_True;
}

void Connection_destroy(Object *self) {

  Connection *conn = (Connection*) self;

  if(conn->fd < 0)
    return;

  close(conn->fd);
}

Object *Connection_read(Object *self, Object **argv, u32 argc) {

  Connection *conn = (Connection*) self;

  if(conn->fd < 0)

    return NOJA_False;

  int buffer_size = 1024;

  if(argc > 0) {

    assert(argv[0]->type == __ObjectInt__);

    int temp = (int) ((ObjectInt*) argv[0])->value;

    if(temp > 0)
      buffer_size = temp;
  }

  char *buffer = malloc(buffer_size+1);

  int readbytes = read(conn->fd, buffer, buffer_size);

  buffer[readbytes] = 0;

  return ObjectString_wrap_cstring(self->context, buffer, buffer_size+1);
}

Object *Connection_write(Object *self, Object **argv, u32 argc) {

  Connection *conn = (Connection*) self;

  if(conn->fd < 0)
    return NOJA_False;

  if(argv == 0)
    return NOJA_False;

  assert(argv[0]->type == __ObjectString__);

  ObjectString *buffer = (ObjectString*) argv[0];

  write(conn->fd, buffer->value, buffer->size);

  return NOJA_True;
}

char Connection_to_cbool(Object *self) {

  Connection *conn = (Connection*) self;

  return conn->fd == -1;
}


ObjectType ptable_Connection = {
  .type = &ptable_ObjectType,
  .flags = 0,
  .methods = 0,
  .name  = "Connection",
  .size = sizeof(Connection),
  .free = &Connection_destroy,
  .select = 0,
  .insert = 0,
  .init   = 0,
  .call   = 0,
  .getAttr = 0,
  .setAttr = 0,
  .print  = 0,
  .operators = 0,
  .to_cbool = &Connection_to_cbool,
  .collectChildren = 0
};

ObjectType ptable_Socket = {
    .type = &ptable_ObjectType,
    .flags = 0,
    .methods = 0,
    .name  = "Socket",
    .size = sizeof(Socket),
    .free = &Socket_destroy,
    .select = 0,
    .insert = 0,
    .init   = &Socket_init,
    .call   = 0,
    .getAttr = 0,
    .setAttr = 0,
    .print  = 0,
    .operators = 0,
    .to_cbool = &Socket_to_cbool,
    .collectChildren = 0
};

char Module_socket_init(Object *dest) {

  /* Insert methods into the Socket class */ {

    Object *methods = Object_create(dest->context, __ObjectDict__, 0, 0);

    Dict_cinsert(methods, "listen", ObjectCFunction_create(dest->context, &Socket_listen));
    Dict_cinsert(methods, "accept", ObjectCFunction_create(dest->context, &Socket_accept));

    ptable_Socket.methods = methods;

  }

  /* Insert methods into the Connection class */ {

    Object *methods = Object_create(dest->context, __ObjectDict__, 0, 0);

    Dict_cinsert(methods, "close", ObjectCFunction_create(dest->context, &Connection_close));
    Dict_cinsert(methods, "read", ObjectCFunction_create(dest->context, &Connection_read));
    Dict_cinsert(methods, "write", ObjectCFunction_create(dest->context, &Connection_write));

    ptable_Connection.methods = methods;

  }

  Dict_cinsert(dest, "AF_INET"      , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_LOCAL"     , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_UNIX"      , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_AX25"      , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_IPX"       , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_APPLETALK" , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_X25"       , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_INET6"     , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_DECnet"    , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_KEY"       , ObjectInt_from_cint(dest->context, (i64) AF_INET));
  Dict_cinsert(dest, "AF_NETLINK"   , ObjectInt_from_cint(dest->context, (i64) AF_NETLINK));
  Dict_cinsert(dest, "AF_PACKET"    , ObjectInt_from_cint(dest->context, (i64) AF_PACKET));
  Dict_cinsert(dest, "AF_RDS"       , ObjectInt_from_cint(dest->context, (i64) AF_RDS));
  Dict_cinsert(dest, "AF_PPPOX"     , ObjectInt_from_cint(dest->context, (i64) AF_PPPOX));
  Dict_cinsert(dest, "AF_LLC"       , ObjectInt_from_cint(dest->context, (i64) AF_LLC));
  Dict_cinsert(dest, "AF_IB"        , ObjectInt_from_cint(dest->context, (i64) AF_IB));
  Dict_cinsert(dest, "AF_MPLS"      , ObjectInt_from_cint(dest->context, (i64) AF_MPLS));
  Dict_cinsert(dest, "AF_CAN"       , ObjectInt_from_cint(dest->context, (i64) AF_CAN));
  Dict_cinsert(dest, "AF_TIPC"      , ObjectInt_from_cint(dest->context, (i64) AF_TIPC));
  Dict_cinsert(dest, "AF_BLUETOOTH" , ObjectInt_from_cint(dest->context, (i64) AF_BLUETOOTH));
  Dict_cinsert(dest, "AF_ALG"       , ObjectInt_from_cint(dest->context, (i64) AF_ALG));
  Dict_cinsert(dest, "AF_VSOCK"     , ObjectInt_from_cint(dest->context, (i64) AF_VSOCK));
  Dict_cinsert(dest, "AF_KCM"       , ObjectInt_from_cint(dest->context, (i64) AF_KCM));
  Dict_cinsert(dest, "AF_XDP"       , ObjectInt_from_cint(dest->context, (i64) AF_XDP));
  Dict_cinsert(dest, "SOCK_SEQPACKET", ObjectInt_from_cint(dest->context, (i64) SOCK_SEQPACKET));
  Dict_cinsert(dest, "SOCK_RAW"     , ObjectInt_from_cint(dest->context, (i64) SOCK_RAW));
  Dict_cinsert(dest, "SOCK_RDM"     , ObjectInt_from_cint(dest->context, (i64) SOCK_RDM));
  Dict_cinsert(dest, "SOCK_PACKET"  , ObjectInt_from_cint(dest->context, (i64) SOCK_PACKET));
  Dict_cinsert(dest, "SOCK_NONBLOCK", ObjectInt_from_cint(dest->context, (i64) SOCK_NONBLOCK));
  Dict_cinsert(dest, "SOCK_CLOEXEC" , ObjectInt_from_cint(dest->context, (i64) SOCK_CLOEXEC));
  Dict_cinsert(dest, "SOCK_STREAM"  , ObjectInt_from_cint(dest->context, (i64) SOCK_STREAM));
  Dict_cinsert(dest, "SOCK_DGRAM"   , ObjectInt_from_cint(dest->context, (i64) SOCK_DGRAM));
  Dict_cinsert(dest, "Socket"       , (Object*) &ptable_Socket);
  Dict_cinsert(dest, "Connection"   , (Object*) &ptable_Connection);

  return 1;
}
