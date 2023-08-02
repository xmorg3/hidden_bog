#Makefile for mySDL

#CC=musl-clang #produces all kinds of linker errors.  make SDL with MUSL?
#CC = clang -g 
#CC = tcc
#CC = scc
CC = gcc -ggdb

#LIBS = #-lSDL2 -lSDL2_image #-lSDL2_ttf -lm #-lsqlite3 #-lGL
LIBS = -lm `sdl2-config --libs` -lSDL2_image

FLAGS = `sdl2-config --cflags --libs` -I/usr/local/include -L/usr/local/lib

FILES = src/main.c \
	src/update.c \
	src/resources.c \
	src/render.c \
	src/text.c \
	src/input.c \
	src/actors.c \
	src/crafting.c \
	src/gameoptions.c \
	src/chargen.c \
	src/scene.c \
	src/maps.c \
	src/sheet_character.c \
	src/sheet_dialogue.c \
	src/sheet_inventory.c \
	src/renderports.c \
#	src/data.c

#src/glfunctions.c
#game.exe: src/SDL_collide.c src/actors.c src/datafunctions.c src/gameui.c
# src/groups.c src/menus.c src/resources.c src/fonts.c src/maps.c 
#src/movables.c src/render.c src/input.c src/world.c src/Main.c
#	gcc -o mySDL.exe -L /usr/local/lib -I /usr/local/include/SDL -lm -lSDL -lSDL_image *.c
#	gcc -o game.exe src/*.c `sdl-config --cflags --libs` -lSDL_image -lm

all:
	$(CC) -o game $(FILES) $(FLAGS) $(LIBS)

clean:
	@echo Cleaning up...
	@echo Erasing exec
	@rm game
	@echo Erasing emacs backups
	@rm src/*.*~
	@rm src/*.o
	@rm *.core
	@echo Done.
