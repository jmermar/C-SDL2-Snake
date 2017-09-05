TARGET=game
SRC=$(wildcard src/*.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

CFLAGS=-std=c11 -lSDL2 -lSDLmain

$(TARGET): $(OBJ)
	gcc -o $(TARGET) $(CFLAGS) $(OBJ)
%.o: %.c
	gcc -c $< $(CFLAGS) -o $@
clean:
	rm $(OBJ) $(TARGET) 
