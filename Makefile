OBJECTS = main.o game.o input.o draw.o menu.o grid.o shape.o
OUTPUT = alfpogs
CFLAGS = -Wall -Werror `sdl-config --cflags`
SDL_LINKER = `sdl-config --libs` -lSDL_ttf -lSDL_image -lSDL_net
CC = gcc

all: $(OUTPUT)

main.o:
draw.o: 
input.o:
game.o:
menu.o:
grid.o:
shape.o:

$(OUTPUT): $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJECTS) $(SDL_LINKER)

.PHONY: clean

clean:
	-rm $(OUTPUT) $(OBJECTS)