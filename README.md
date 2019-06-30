

## Just show me the code!

```javascript

import 'sdl2' from 'C' as sdl;

sdl.init();

ctx = sdl.Context();

ctx.createWindow('Holaa come va amigoss', 300, 300);

ctx.clear();

ctx.fillRect(20, 20, 10, 10, 255, 0, 0, 0);

ctx.update();

running = true;

while running {

  event = ctx.catchEvent();

  if event['name'] == 'quit' {

    running = false;

  } else {

    if event['name'] == 'keydown' {

      print(event['code']);

    }
  }

}


sdl.quit();

```

This program imports an SDL2 wrapper module, opens a window, draws a red rectangle and waits to be closed.

---
