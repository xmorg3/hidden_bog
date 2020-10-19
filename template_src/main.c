
#include <SDL.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start_sdl(GameCore *gc);
//int stop_ttf(GameCore *gc);
int load_resources(GameCore *gc);
int update(GameCore *gc); //handle_keydown handle_mousebutton_down
void main_draw_loop(GameCore *gc);
void input(GameCore *gc);
#ifdef _SQLITE_
  int load_data_from_db(GameCore *gc);
#endif
void print_in_messagebox(GameCore *gc, char *text);

Actor * new_actor(char *name); //actors.c
PlayMap * new_map(char *name, int mapsize, char *filename); //scene.c

int main(int argc, char** argv){
  GameCore *gc;
  Actor *player;
  gc = (GameCore *) malloc(sizeof(GameCore));
  player = new_actor("player");//(Actor *) malloc(sizeof(Actor));
  gc->c_text_size = (SDL_Rect *) malloc(sizeof(SDL_Rect));
  gc->player = player;
  gc->mapsize = 20;
  gc->current_map = new_map("nomap", 20, "data/maps/v_hamsford.txt");
  gc->player->map_x = 4;
  gc->player->map_y = 4;

  //GCC hack, you must assign before running print_in_messagebox?
  strcpy(gc->messagelist[0],">"); //print_in_messagebox(gc, ">");
  strcpy(gc->messagelist[1],">"); //print_in_messagebox(gc, ">");
  strcpy(gc->messagelist[2],">"); //print_in_messagebox(gc, ">");
  strcpy(gc->messagelist[3],">"); //print_in_messagebox(gc, ">");
  strcpy(gc->messagelist[4],">"); //print_in_messagebox(gc, ">");
  strcpy(gc->messagelist[5],">"); //print_in_messagebox(gc, ">");
  strcpy(gc->messagelist[6],">");
  strcpy(gc->messagelist[7],">");
 

  start_sdl(gc); //gc->game_state = 1, resources.c
  load_resources(gc);
  #ifdef _SQLITE_
  load_data_from_db(gc);
  #endif
  gc->game_state = GAME_START_MENU;
  while(gc->game_state > 0) {
    input(gc);   //input.c
    update(gc);  //update.c
    main_draw_loop(gc);  //render.c
  }

  SDL_Delay(500);
  SDL_DestroyTexture(gc->t_buttons);
  SDL_DestroyTexture(gc->t_background);
  SDL_DestroyRenderer(gc->renderer);
  SDL_DestroyWindow(gc->win);
  //stop_ttf(gc);
  free(gc->c_text_size);
  free(gc);

	return 0;
}
