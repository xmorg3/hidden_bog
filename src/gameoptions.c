#include <SDL.h>
#include "game.h"

void handle_mousebutton_down_options_menu(GameCore *gc);
void draw_options_menu(GameCore *gc);

void fast_button(GameCore *gc, int x, int y, char *text);//render.c
SDL_Rect fast_rect(int x, int y, int w, int h);//render.c

SDL_Texture* sdl_printf_font(GameCore *gc, TTF_Font *font, char *message); //text.c
void sdl_set_textpos(GameCore *gc, int x, int y);//text.c
void set_color(GameCore *gc, int r, int g, int b); //set_font_color; //text.c

void draw_options_menu(GameCore *gc)
{//int screen_size_x, screen_size_y;
  SDL_Rect dst, src;
  SDL_RenderCopy(gc->renderer, gc->w_background, NULL, NULL); //put background
  //put name on the top
  fast_button(gc, 10,10, "Player"); //- player name
  fast_button(gc, 10,gc->screen_size_y - 58, "Back");
  fast_button(gc, 300,gc->screen_size_y - 58, "Next");
}
void handle_mousebutton_down_options_menu(GameCore *gc)
{
  //fast_button(gc, 10,gc->screen_size_y - 58, "Back");
  //fast_button(gc, 300,gc->screen_size_y - 58, "Next");
  if(gc->mouse_x >= 10 && gc->mouse_x <= 10+283 &&
     gc->mouse_y >= gc->screen_size_y - 58 && gc->mouse_y <= gc->screen_size_y) {
    printf("Go Back.\n");
    gc->game_state = GAME_START_MENU;
  }
  else if (gc->mouse_x >= 300 && gc->mouse_x <= 300+283 &&
	   gc->mouse_y >= gc->screen_size_y-58 && gc->mouse_y <= gc->screen_size_y) {
    gc->game_state = GAME_OPTIONS_MENU;
    printf("(still in options).\n");
  }
}
