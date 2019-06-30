
all: fs socket sdl2 json

fs: cmodules/fs.c
	gcc -shared -fPIC cmodules/fs.c -o libfs.so -lc -g

socket: cmodules/socket.c
	gcc -shared -fPIC cmodules/socket.c -o libsocket.so -lc -g

sdl2: cmodules/sdl2.c
	gcc -shared -fPIC cmodules/sdl2.c -o libsdl2.so -lc -g -lSDL2

json: cmodules/json.c
	gcc -shared -fPIC cmodules/json.c -o libjson.so -lc -g

install: fs socket
	mkdir /usr/lib/Noja && \
	mkdir /usr/lib/Noja/std_modules && \
	mv    libfs.so /usr/lib/Noja/std_modules/libfs.so
