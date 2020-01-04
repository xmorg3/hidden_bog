#include <SDL_ttf.h>
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

SDL_Rect fast_rect(int x, int y, int w, int h); //render.c
SDL_Texture* IMG_Load_w_error(GameCore *gc, char * imgfile); //resources.c
void load_font(GameCore *gc, char *bmpfile); //Load a bmp file into current_font
void sdl_set_textpos(GameCore *gc, int x, int y); //text.c
void rendertext(GameCore *gc, char *message);
SDL_Texture* sdl_printf_font(GameCore *gc, char * message); //calls txt currently
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;

void load_font(GameCore *gc, char *bmpfile) {
  gc->font0 = IMG_Load_w_error(gc, bmpfile);
  gc->current_font = gc->font0; //pointer to pointer
}

void sdl_set_textpos(GameCore *gc, int x, int y) { //text.c
  gc->c_text_size->x = x;
  gc->c_text_size->y = y;
  gc->c_text_size->w = 16;
  gc->c_text_size->h = 24;
}

//top = (ascii - 32) / 16 * 12;
//left = (ascii - 32) % 16 * 8;
void rendertext(GameCore *gc, char *message){
  int l = strlen(message);
  SDL_Texture *wholetext;
  char c; //current letter in string
  for(int i=0; i < l; i++) {
    c = message[i]; //current letter in string
    int top = (c - 32) / 16 *12;  //gc->current_font->w / 96;
    int left = (c - 32) % 16 * 8; //12; //gc->current_font->h;
    SDL_Rect s = fast_rect(left,    //X
			   top,   //Y
			   8,      //W
			   12);    //H
    SDL_Rect d = fast_rect(gc->c_text_size->x + (i*gc->c_text_size->w),
			   gc->c_text_size->y + 0,
			   gc->c_text_size->w,
			   gc->c_text_size->h);
    SDL_RenderCopy(gc->renderer, //renderer
    		   gc->current_font, //text of font
    		   &s,  //place in font to blit
    		   &d );
  }  //putchar('\n');
}

void set_color(GameCore *gc, int r, int g, int b) { //set_font_color;
  gc->current_color.r = r;
  gc->current_color.b = b;
  gc->current_color.g = g;
}
