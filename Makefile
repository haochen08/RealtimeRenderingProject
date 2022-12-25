main:
	clang -Wall -std=c99 main.c -o main -I/opt/homebrew/Cellar/sdl2/2.26.1/include  -L/opt/homebrew/Cellar/sdl2/2.26.1/lib -lSDL2

test:
	clang -Wall -std=c99 test.c -o test -I/opt/homebrew/Cellar/sdl2/2.26.1/include  -L/opt/homebrew/Cellar/sdl2/2.26.1/lib -lSDL2

clean:
	rm main