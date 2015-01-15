
#include <SDL2/SDL.h>
#include "game.h"

int start_sdl(GameCore *gc);
int stop_ttf(GameCore *gc);
int load_resources(GameCore *gc);
int update(GameCore *gc); //handle_keydown handle_mousebutton_down
void draw(GameCore *gc);
void input(GameCore *gc);

void print_in_messagebox(GameCore *gc, char *text);


Actor * new_actor(char *name); //actors.c

Scene * new_map(char *name, int mapsize, char *filename); //scene.c

int main(int argc, char** argv){
  GameCore *gc;
  Actor *player;
  gc = (GameCore *) malloc(sizeof(GameCore));
  player = new_actor("player");//(Actor *) malloc(sizeof(Actor));
  gc->c_text_size = (SDL_Rect *) malloc(sizeof(SDL_Rect));
  gc->player = player;
  gc->mapsize = 20;
  gc->current_map = new_map("nomap", gc->mapsize, NULL);
  
  gc->player->map_x = 4; 
  gc->player->map_y = 4;

  print_in_messagebox(gc, ">");
  print_in_messagebox(gc, ">");
  print_in_messagebox(gc, ">");
  print_in_messagebox(gc, ">");
  print_in_messagebox(gc, ">");
  print_in_messagebox(gc, ">");


  start_sdl(gc); //gc->game_state = 1, resources.c
  load_resources(gc);
  gc->game_state = GAME_START_MENU;
  while(gc->game_state > 0) {
    input(gc);
    update(gc);
    draw(gc);
  }

  SDL_Delay(1000);
  SDL_DestroyTexture(gc->t_buttons);
  SDL_DestroyTexture(gc->t_background);
  SDL_DestroyRenderer(gc->renderer);
  SDL_DestroyWindow(gc->win);
  stop_ttf(gc);
  free(gc->c_text_size);
  free(gc);
}
