
all: fs socket sdl2 json fs2 mongoose libmicrohttpd lowLevel gsl math

math: cmodules/math/math.c cmodules/math/matrix.c cmodules/math/functions.c
	gcc -shared -fPIC cmodules/math/matrix.c cmodules/math/math.c cmodules/math/functions.c -o libmath.so -lc -g -lm

lowLevel: cmodules/lowLevel.c
	gcc -shared -fPIC cmodules/lowLevel.c -o liblowLevel.so -lc -g

gsl: cmodules/gsl/gsl.c cmodules/gsl/vector.c
	gcc -shared -fPIC cmodules/gsl/gsl.c cmodules/gsl/vector.c -o libgsl.so -lc -g -lgsl -lgslcblas

libmicrohttpd: cmodules/libmicrohttpd.c
	gcc -shared -fPIC cmodules/libmicrohttpd.c -o libmicrohttpd.so -lc -g

mongoose: cmodules/mongoose.c
	gcc -shared -fPIC cmodules/mongoose.c -o libmongoose.so -lc -g

fs: cmodules/fs.c
	gcc -shared -fPIC cmodules/fs.c -o libfs.so -lc -g

fs2: cmodules/fs2.c
	gcc -shared -fPIC cmodules/fs2.c -o libfs2.so -lc -g

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
