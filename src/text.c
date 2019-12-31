#include <SDL_ttf.h>
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

SDL_Rect fast_rect(int x, int y, int w, int h);
void load_font(GameCore *gc, char *bmpfile); //Load a bmp file into current_font
void sdl_set_textpos(GameCore *gc, int x, int y); //text.c
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;
SDL_Surface* text(GameCore *gc, char *message);
sdl_printf_font(GameCore *gc, SDL_Surface *f, char * message);

void load_font(GameCore *gc, char *bmpfile)
{
  gc->font0 = SDL_LoadBMP(const char* file);
  //gc->current_font = gc->font0;
}

void sdl_set_textpos(GameCore *gc, int x, int y) //text.c
{
  gc->c_text_size = x;
  gc->c_text_size = y;
}
SDL_Surface* text(GameCore *gc, char *message)
{
  l = strlen(message);
  SDL_Surface *wholetext;
  char c; //current letter in string
  int  a; //c as int
  for(int i=0; i < l; i++) {
    c = message[i]; //current letter in string
    a = atoi(c);
    cfwidth = gc->current_font->w / 96;
    cfheight = gc->current_font->h;
    SDL_Rect s = fast_rect(a*cfwidth,    //X
			   0,            //Y
			   cfwidth,      //W
			   cfheight);    //H
    //update a font size here?
    SDL_Rect d = fast_rect(i*cfwidth, 0, cfwidth, cfheight);
    SDL_BitSurface(gc->current_font, //surface of font
		   &s,  //place in font to blit
		   wholetext,//output string surface
		   &d);		   
    //text output as a surface
    //it should now be ready to convert/copy to a texture
  }
  return wholetext;
}
SDL_Texture* sdl_printf_font(GameCore *gc, SDL_Surface *f, char * message)
{
  SDL_Texture t;
  SDL_Surface *s = text(gc, message);
  t = SDL_CreateTextureFromSurface(gc->renderer, s);
  return t;
}
