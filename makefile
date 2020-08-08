TARGET=game
SRC=$(wildcard src/*.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

CFLAGS=-std=c11 -lSDL2 -lSDL2main

$(TARGET): $(OBJ) main.c
	gcc -o $(TARGET) main.c $(OBJ) $(CFLAGS)
%.o: %.c
	gcc -c $< $(CFLAGS) -o $@
clean:
	rm $(OBJ) $(TARGET) 


web: $(SRC)
	emcc mainWASM.c $(SRC) -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2  --embed-file graphic -o index.html
	
