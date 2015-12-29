#include <SDL.h>
#include "game.h"

void draw_character_attributes(GameCore *gc, int x, int y, int moddable); //chargen.c
void draw_char_menu_frame(GameCore *gc); //backdrop frame
void input_char_menu_frame(GameCore *gc); //mouse functions
void draw_sheet_character(GameCore *gc);

void draw_sheet_character(GameCore *gc)
{
  draw_char_menu_frame(gc);
  //draw a portrait
  draw_character_attributes(gc, gc->stat_panel_x, gc->stat_panel_y, 1);
}

void input_char_menu_frame(GameCore *gc) //get mouse functions?
{
  int i;
  SDL_Rect b1, b2;
  b1 = fast_rect(10, gc->screen_size_y - 58, 283 , 58);
  b2 = fast_rect(300, gc->screen_size_y - 58, 283 , 58);
  if( check_clickedin(&b1, gc->mouse_x, gc->mouse_y ) == 1 ) {
    gc->game_state = GAME_PLAY_IDLE;
  }
}
