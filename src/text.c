#include <SDL_ttf.h>
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

SDL_Rect fast_rect(int x, int y, int w, int h); //render.c
void load_font(GameCore *gc, char *bmpfile); //Load a bmp file into current_font
void sdl_set_textpos(GameCore *gc, int x, int y); //text.c
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;
SDL_Surface* text(GameCore *gc, char *message); //take message and return a surface
SDL_Texture* sdl_printf_font(GameCore *gc, char * message); //calls txt currently
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;

void load_font(GameCore *gc, char *bmpfile)
{
  SDL_Surface *s = SDL_LoadBMP(bmpfile); //load the surface
  gc->font0 = SDL_CreateTextureFromSurface(gc->renderer, s); //surf to tex
  gc->current_font = gc->font0; //pointer to pointer
}

void sdl_set_textpos(GameCore *gc, int x, int y) //text.c
{
  gc->c_text_size->x = x;
  gc->c_text_size->y = y;
}

SDL_Texture* rendertext(GameCore *gc, char *message)
{
  int l = strlen(message);
  SDL_Texture *wholetext;
  char c; //current letter in string
  //int  a; //c as int
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
  }
  //printf("\n");
  return wholetext;
}
SDL_Texture* sdl_printf_font(GameCore *gc, char * message)
{
  //SDL_Texture *t;
  //SDL_Surface *s = text(gc, message);
  //printf("got surface, creating texture\n");
  SDL_Texture *t = rendertext(gc, message);//SDL_CreateTextureFromSurface(gc->renderer, s);
  //printf("finished createtexturefromsurface\n");
  SDL_RenderCopy(gc->renderer, t, NULL, gc->c_text_size);
  return t;
}

void set_color(GameCore *gc, int r, int g, int b) //set_font_color;
{
  //SDL_Color current_color; //current color to draw in (like for text)
  gc->current_color.r = r;
  gc->current_color.b = b;
  gc->current_color.g = g;
}
