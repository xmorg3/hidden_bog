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
SDL_Texture* rendertext(GameCore *gc, char *message); //put text out.
SDL_Texture* sdl_printf_font(GameCore *gc, char * message); //calls txt currently
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;

void load_font(GameCore *gc, char *bmpfile) {
  //SDL_Surface *s = SDL_LoadBMP(bmpfile); //load the surface
  //gc->font0 = SDL_CreateTextureFromSurface(gc->renderer, s); //surf to tex
  gc->font0 = IMG_Load_w_error(gc, bmpfile);
  gc->current_font = gc->font0; //pointer to pointer
}

void sdl_set_textpos(GameCore *gc, int x, int y) { //text.c
  gc->c_text_size->x = x;
  gc->c_text_size->y = y;
}

SDL_Texture* rendertext(GameCore *gc, char *message) {
  int l = strlen(message);
  SDL_Texture *wholetext;
  char c; //current letter in string
  for(int i=0; i < l; i++) {
    c = message[i]; //current letter in string
    int cfwidth = 8; //gc->current_font->w / 96;
    int cfheight = 12; //gc->current_font->h;
    SDL_Rect s = fast_rect(c*cfwidth,    //X
			   0,            //Y
			   cfwidth,      //W
			   cfheight);    //H
    SDL_Rect d = fast_rect(i*cfwidth, 0, cfwidth, cfheight);
    //printf("blitting surface for char %c %d", c, i);
    SDL_RenderCopy(gc->renderer, //renderer
		   gc->current_font, //text of font
		   &s,  //place in font to blit
		   &d);
  }   //printf("\n");
  return wholetext;
}
SDL_Texture* sdl_printf_font(GameCore *gc, char * message) {
  //SDL_RenderCopy(gc->renderer, gc->wall_right_fov0_blank, NULL, &gc->player_viewport);
  SDL_Texture *t = rendertext(gc, message);//SDL_CreateTextureFromSurface(gc->renderer, s);
  SDL_RenderCopy(gc->renderer, t, NULL, gc->c_text_size);  //output to the screen.
  return t;
}

void set_color(GameCore *gc, int r, int g, int b) { //set_font_color;
  gc->current_color.r = r;
  gc->current_color.b = b;
  gc->current_color.g = g;
}
