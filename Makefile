hello:
	clang -Wall -std=c99 hello.c -o hello -arch x86_64  -I/usr/local/Cellar/sdl2/2.26.1/include  -L/usr/local/Cellar/sdl2/2.26.1/lib -lSDL2

main:
	clang -Wall -std=c99 main.c -o main -arch x86_64  -I/usr/local/Cellar/sdl2/2.26.1/include  -L/usr/local/Cellar/sdl2/2.26.1/lib -lSDL2

clean:
	rm hello main