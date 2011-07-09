ALL_HEADERS = game.h input.h grid.h images.h draw.h net.h shape.h instance.h list.h
CC = gcc
CFLAGS = -Wall -Werror `sdl-config --cflags`
OBJECTS = game.o input.o list.o draw.o grid.o shape.o instance.o images.o net.o
SDL_LINKER = `sdl-config --libs` -lSDL_image -lSDL_net

CLIENT_OBJECTS = main.o $(OBJECTS)
CLIENT_OUTPUT = alfpogs
CLIENT_CFLAGS = $(CFLAGS)
CLIENT_SDL_LINKER = $(SDL_LINKER)

SERVER_OBJECTS = server_main.o $(OBJECTS)
SERVER_OUTPUT = $(CLIENT_OUTPUT)-server
SERVER_CFLAGS = $(CFLAGS) -pthread
SERVER_SDL_LINKER = $(SDL_LINKER)

all: $(CLIENT_OUTPUT) $(SERVER_OUTPUT)

main.o: $(ALL_HEADERS)
server_main.o: $(ALL_HEADERS)
draw.o: $(ALL_HEADERS)
input.o: $(ALL_HEADERS)
game.o: $(ALL_HEADERS)
grid.o: $(ALL_HEADERS)
images.o: $(ALL_HEADERS)
shape.o: $(ALL_HEADERS)
timer.o: $(ALL_HEADERS)
instance.o: $(ALL_HEADERS)
net.o: $(ALL_HEADERS)
list.o: $(ALL_HEADERS)

$(CLIENT_OUTPUT): $(CLIENT_OBJECTS) 
	$(CC) $(CLIENT_CFLAGS) -o $(CLIENT_OUTPUT) $(CLIENT_OBJECTS) $(CLIENT_SDL_LINKER)

$(SERVER_OUTPUT): $(SERVER_OBJECTS) 
	$(CC) $(SERVER_CFLAGS) -o $(SERVER_OUTPUT) $(SERVER_OBJECTS) $(SERVER_SDL_LINKER)

.PHONY: clean

clean:
	-rm $(CLIENT_OUTPUT) $(SERVER_OUTPUT) $(CLIENT_OBJECTS) $(SERVER_OBJECTS) *~