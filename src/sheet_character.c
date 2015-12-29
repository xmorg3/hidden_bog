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
  
}
