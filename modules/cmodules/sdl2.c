
#include <SDL2/SDL.h>
#include "../../runtime/header.h"

typedef struct SDL2Context {
  OBJECT_HEAD;
  SDL_Window *window;
  SDL_Renderer *renderer;
} SDL2Context;

void SDL2Context_destroy(Object *self) {

  SDL2Context *ctx = (SDL2Context*) self;

  if(ctx->renderer) {
    SDL_DestroyRenderer(ctx->renderer);
  }

  if(ctx->window) {
    SDL_DestroyWindow(ctx->window);
  }

}

void SDL2Context_init(Object *self, Object **argv, u32 argc) {

}

Object *SDL2Context_catchEvent(Object *self, Object **argv, u32 argc) {

  SDL_Event event;

  SDL_PollEvent(&event);

  Object *result = Object_create(self->context, __ObjectDict__, 0, 0);

  Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "?"));

  switch(event.type) {

    case SDL_WINDOWEVENT:

    switch(event.window.event) {

      case SDL_WINDOWEVENT_SHOWN:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-shown"));
      break;

      case SDL_WINDOWEVENT_HIDDEN:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-hidden"));
      break;

      case SDL_WINDOWEVENT_EXPOSED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-exposed"));
      break;

      case SDL_WINDOWEVENT_MOVED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-moved"));
      break;

      case SDL_WINDOWEVENT_RESIZED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-resized"));
      break;

      case SDL_WINDOWEVENT_SIZE_CHANGED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-size-changed"));
      break;

      case SDL_WINDOWEVENT_MINIMIZED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-minimized"));
      break;

      case SDL_WINDOWEVENT_MAXIMIZED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-maximized"));
      break;

      case SDL_WINDOWEVENT_RESTORED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-restored"));
      break;

      case SDL_WINDOWEVENT_ENTER:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-enter"));
      break;

      case SDL_WINDOWEVENT_LEAVE:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-leave"));
      break;

      case SDL_WINDOWEVENT_FOCUS_GAINED:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-focus-gained"));
      break;

      case SDL_WINDOWEVENT_FOCUS_LOST:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-focus-lost"));
      break;

      case SDL_WINDOWEVENT_CLOSE:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-close"));
      break;

      case SDL_WINDOWEVENT_TAKE_FOCUS:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-take-focus"));
      break;

      case SDL_WINDOWEVENT_HIT_TEST:
      Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "window-hit-test"));
      break;
    }
    break;

    case SDL_QUIT:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "quit"));
    break;

    case SDL_APP_TERMINATING:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "app-terminating"));
    break;

    case SDL_APP_LOWMEMORY:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "app-lowmemory"));
    break;

    case SDL_APP_WILLENTERBACKGROUND:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "app-willenterbackground"));
    break;

    case SDL_APP_DIDENTERBACKGROUND:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "app-didenterbackground"));
    break;

    case SDL_APP_WILLENTERFOREGROUND:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "app-willenterforeground"));
    break;

    case SDL_APP_DIDENTERFOREGROUND:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "app-didenterforeground"));
    break;

    case SDL_KEYDOWN://
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "keydown"));
    Dict_cinsert(result, "code", ObjectInt_from_cint(self->context, (i64) event.key.keysym.sym));
    break;

    case SDL_KEYUP://
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "keyup"));
    Dict_cinsert(result, "code", ObjectInt_from_cint(self->context, (i64) event.key.keysym.sym));
    break;

    case SDL_TEXTEDITING://
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "textediting"));
    break;

    case SDL_TEXTINPUT: //
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "textinput"));
    break;

    case SDL_KEYMAPCHANGED:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "keymapchanged"));
    break;

    case SDL_MOUSEMOTION:
    Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousemotion"));
    break;

    case SDL_MOUSEBUTTONDOWN:

    switch(event.button.button) {
      case SDL_BUTTON_LEFT:   Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttondown-left")); break;
      case SDL_BUTTON_RIGHT:  Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttondown-right")); break;
      case SDL_BUTTON_MIDDLE: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttondown-middle")); break;
      case SDL_BUTTON_X1:     Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttondown-x1")); break;
      case SDL_BUTTON_X2:     Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttondown-x2")); break;
    }

    break;

    case SDL_MOUSEBUTTONUP:

    switch(event.button.button) {
      case SDL_BUTTON_LEFT:   Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttonup-left")); break;
      case SDL_BUTTON_RIGHT:  Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttonup-right")); break;
      case SDL_BUTTON_MIDDLE: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttonup-middle")); break;
      case SDL_BUTTON_X1:     Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttonup-x1")); break;
      case SDL_BUTTON_X2:     Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousebuttonup-x2")); break;
    }

    break;

    case SDL_MOUSEWHEEL: {

      char  x = 0, // 0 none, 1 left, 2 right
            y = 0; // 0 none, 10 up, 20 down

      if(event.wheel.y > 0) {

        y = 1;

      } else if(event.wheel.y < 0) {

        y = 2;

      }

      if(event.wheel.x > 0) {

        x = 10;

      } else if(event.wheel.x < 0) {

        x = 20;

      }

      switch(x + y) {
        case 1: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-up")); break;
        case 2: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-down")); break;
        case 11: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-up-left")); break;
        case 21: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-up-right")); break;
        case 12: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-down-left")); break;
        case 22: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-down-right")); break;
        case 10: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-left")); break;
        case 20: Dict_cinsert(result, "name", ObjectString_from_cstring(self->context, "mousewheel-right")); break;
      }

    }

    break;

    case SDL_JOYAXISMOTION:break;
    case SDL_JOYBALLMOTION:break;
    case SDL_JOYHATMOTION:break;
    case SDL_JOYBUTTONDOWN:break;
    case SDL_JOYBUTTONUP:break;
    case SDL_JOYDEVICEADDED:break;
    case SDL_JOYDEVICEREMOVED:break;

    case SDL_CONTROLLERAXISMOTION:break;
    case SDL_CONTROLLERBUTTONDOWN:break;
    case SDL_CONTROLLERBUTTONUP:break;
    case SDL_CONTROLLERDEVICEADDED:break;
    case SDL_CONTROLLERDEVICEREMOVED:break;
    case SDL_CONTROLLERDEVICEREMAPPED:break;

    case SDL_FINGERDOWN:break;
    case SDL_FINGERUP:break;
    case SDL_FINGERMOTION:break;

    case SDL_DOLLARGESTURE:break;
    case SDL_DOLLARRECORD:break;
    case SDL_MULTIGESTURE:break;

    case SDL_CLIPBOARDUPDATE:break;
    case SDL_DROPFILE:break;
    case SDL_DROPTEXT:break;
    case SDL_DROPBEGIN:break;
    case SDL_DROPCOMPLETE:break;

    case SDL_AUDIODEVICEADDED:break;
    case SDL_AUDIODEVICEREMOVED:break;

    case SDL_RENDER_TARGETS_RESET:break;
    case SDL_RENDER_DEVICE_RESET:break;

    case SDL_USEREVENT:break;
    case SDL_LASTEVENT:break;

  }

  return result;
}

Object *SDL2Context_createWindow(Object *self, Object **argv, u32 argc) {

  SDL2Context *ctx = (SDL2Context*) self;

  char *title = "Untitled window";
  int w = 100,
      h = 100,
      x = SDL_WINDOWPOS_UNDEFINED,
      y = SDL_WINDOWPOS_UNDEFINED,
      flags = 0;

  switch(argc) {

    default:
    case 5: y = ((ObjectInt*) argv[4])->value;
    case 4: x = ((ObjectInt*) argv[3])->value;
    case 3: h = ((ObjectInt*) argv[2])->value;
    case 2: w = ((ObjectInt*) argv[1])->value;
    case 1: title = ((ObjectString*) argv[0])->value;
    case 0:
    break;
  }

  ctx->window = SDL_CreateWindow(title, x, y, w, h, flags);

  if(!ctx->window) {
    return NOJA_False;
  }

  ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);

  if(!ctx->renderer) {
    SDL_DestroyWindow(ctx->window);
    ctx->window = 0;
    return NOJA_False;
  }

  return NOJA_True;
}

Object *SDL2Context_drawRect(Object *self, Object **argv, u32 argc) {

  SDL2Context *ctx = (SDL2Context*) self;

  if(!ctx->window || !ctx->renderer)
    return NOJA_False;

  u8  r = 255,
      g = 255,
      b = 255,
      a = 255;

  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = 0;
  rect.h = 0;

  switch(argc) {
    default:
    case 8:      a = (int) ((ObjectInt*) argv[7])->value;
    case 7:      b = (int) ((ObjectInt*) argv[6])->value;
    case 6:      g = (int) ((ObjectInt*) argv[5])->value;
    case 5:      r = (int) ((ObjectInt*) argv[4])->value;
    case 4: rect.y = (int) ((ObjectInt*) argv[3])->value;
    case 3: rect.x = (int) ((ObjectInt*) argv[2])->value;
    case 2: rect.h = (int) ((ObjectInt*) argv[1])->value;
    case 1: rect.w = (int) ((ObjectInt*) argv[0])->value;
    case 0:
    break;
  }

  SDL_SetRenderDrawColor(ctx->renderer, r, g, b, a);

  SDL_RenderDrawRect(ctx->renderer, &rect);

  return NOJA_True;
}

Object *SDL2Context_fillRect(Object *self, Object **argv, u32 argc) {

  SDL2Context *ctx = (SDL2Context*) self;

  if(!ctx->window || !ctx->renderer)
    return NOJA_False;

  u8  r = 255,
      g = 255,
      b = 255,
      a = 255;

  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = 0;
  rect.h = 0;

  switch(argc) {
    default:
    case 8:      a = (int) ((ObjectInt*) argv[7])->value;
    case 7:      b = (int) ((ObjectInt*) argv[6])->value;
    case 6:      g = (int) ((ObjectInt*) argv[5])->value;
    case 5:      r = (int) ((ObjectInt*) argv[4])->value;
    case 4: rect.y = (int) ((ObjectInt*) argv[3])->value;
    case 3: rect.x = (int) ((ObjectInt*) argv[2])->value;
    case 2: rect.h = (int) ((ObjectInt*) argv[1])->value;
    case 1: rect.w = (int) ((ObjectInt*) argv[0])->value;
    case 0:
    break;
  }

  SDL_SetRenderDrawColor(ctx->renderer, r, g, b, a);

  SDL_RenderFillRect(ctx->renderer, &rect);

  return NOJA_True;

}

Object *SDL2Context_drawLine(Object *self, Object **argv, u32 argc) {

  SDL2Context *ctx = (SDL2Context*) self;

  if(!ctx->window || !ctx->renderer)
    return NOJA_False;

  u8  r = 255,
      g = 255,
      b = 255,
      a = 255;

  int x1 = 0,
      y1 = 0,
      x2 = 0,
      y2 = 0;

  switch(argc) {
    default:
    case 8:  a = (int) ((ObjectInt*) argv[7])->value;
    case 7:  b = (int) ((ObjectInt*) argv[6])->value;
    case 6:  g = (int) ((ObjectInt*) argv[5])->value;
    case 5:  r = (int) ((ObjectInt*) argv[4])->value;
    case 4: y2 = (int) ((ObjectInt*) argv[3])->value;
    case 3: x2 = (int) ((ObjectInt*) argv[2])->value;
    case 2: y1 = (int) ((ObjectInt*) argv[1])->value;
    case 1: x1 = (int) ((ObjectInt*) argv[0])->value;
    case 0:
    break;
  }

  SDL_SetRenderDrawColor(ctx->renderer, r, g, b, a);

  SDL_RenderDrawLine(ctx->renderer, x1, y1, x2, y2);

  return NOJA_True;
}

Object *SDL2Context_clear(Object *self, Object **argv, u32 argc) {

  SDL2Context *ctx = (SDL2Context*) self;

  if(!ctx->window || !ctx->renderer)
    return NOJA_False;

  u8  r = 255,
      g = 255,
      b = 255,
      a = 255;

  switch(argc) {
    default:
    case 4:  a = (int) ((ObjectInt*) argv[3])->value;
    case 3:  b = (int) ((ObjectInt*) argv[2])->value;
    case 2:  g = (int) ((ObjectInt*) argv[1])->value;
    case 1:  r = (int) ((ObjectInt*) argv[0])->value;
    case 0:
    break;
  }

  SDL_SetRenderDrawColor(ctx->renderer, r, g, b, a);

  SDL_RenderClear(ctx->renderer);

  return NOJA_True;
}

Object *SDL2Context_update(Object *self, Object **argv, u32 argc) {

  SDL2Context *ctx = (SDL2Context*) self;

  if(!ctx->window || !ctx->renderer)
    return NOJA_False;

  SDL_RenderPresent(ctx->renderer);

  return NOJA_True;
}

ObjectType ptable_SDL2Context = {
  .type = &ptable_ObjectType,
  .flags = 0,
  .methods = 0,
  .name = "SDL2Context",
  .size = sizeof(SDL2Context),
  .free = SDL2Context_destroy,
  .select = 0,
  .insert = 0,
  .init = SDL2Context_init,
  .call = 0,
  .getAttr = 0,
  .setAttr = 0,
  .print = 0,
  .operators = 0,
  .to_cbool = 0,
  .collectChildren = 0,
};

Object *start(Object *self, Object **argv, u32 argc) {
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    return NOJA_False;
  }
  return NOJA_True;
}

Object *quit(Object *self, Object **argv, u32 argc) {
  SDL_Quit();
  return NOJA_True;
}

char Module_sdl2_init(Object *dest) {

    Object *methods = Object_create(dest->context, __ObjectDict__, 0, 0);

    Dict_cinsert(methods, "drawLine", ObjectCFunction_create(dest->context, &SDL2Context_drawLine));
    Dict_cinsert(methods, "drawRect", ObjectCFunction_create(dest->context, &SDL2Context_drawRect));
    Dict_cinsert(methods, "fillRect", ObjectCFunction_create(dest->context, &SDL2Context_fillRect));
    Dict_cinsert(methods, "clear",    ObjectCFunction_create(dest->context, &SDL2Context_clear));
    Dict_cinsert(methods, "update",   ObjectCFunction_create(dest->context, &SDL2Context_update));
    Dict_cinsert(methods, "createWindow", ObjectCFunction_create(dest->context, &SDL2Context_createWindow));
    Dict_cinsert(methods, "catchEvent", ObjectCFunction_create(dest->context, &SDL2Context_catchEvent));

    ptable_SDL2Context.methods = methods;

    Dict_cinsert(dest, "init", ObjectCFunction_create(dest->context, &start));
    Dict_cinsert(dest, "quit", ObjectCFunction_create(dest->context, &quit));
    Dict_cinsert(dest, "Context", (Object*) &ptable_SDL2Context);

    return 1;
}
