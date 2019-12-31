#include <SDL_ttf.h>
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
//Note: "printf" function do NOT actually put text on the screen, they only
//create a texture that has to be "rendered" to the screen with SDL_RenderCopy
//See draw.c for examples.
//strlen! if you want to scale the text to a size based on how many characters, you need a number for x
//TODO: text rendering needs and SDL_Rect to scale the text.
//TODO: ^so we need to store the dest *SDL_Rect, per texture rendered.

typedef struct BMPFont{
  SDL_Surface *img; //font image
  int width, height; //width,height of each character(Fixed)  //x = atoi(char) * width
  //y = 0?
} bitmapfont;


bitmapfont *loadBMPfont(SDL_Surface *f, int width, int height);

void sdl_set_textpos(GameCore *gc, int x, int y);
//SDL_Texture* sdl_printf_fontTTF(GameCore *gc, TTF_Font *font, char *message);
//SDL_Texture* sdl_printf_font(GameCore *gc, SDL_Surface *font, char *message);
//SDL_Texture* sdl_printf(GameCore *gc, char *message);
SDL_Surface *sdlprint(bitmapfont *b, char *s);
void set_color(GameCore *gc, int r, int g, int b);
//void start_ttf(GameCore *gc);
//void stop_ttf(GameCore *gc);

SDL_Rect *getchar_rect(bitmapfont *b, SDL_Rect *cr, char c)
{// [THE FONT IMAGE######[char here]######]
  //SDL_Rect cr; //char rect
  int charcode;
  int x;
  //const char atc = ;
  charcode = atoi(c);
  cr->x = charcode * b->width;//position of char in font
  cr->y = 0; //no assumed rows in font
  cr->w = b->width;
  cr->h = b->height;
  return &cr;
}
SDL_Surface *sdlprint(bitmapfont *b, char *s)
{//getting a surface with the string printed onto it.
  int len;
  SDL_Rect string_rect;
  SDL_Rect charrect; //size of the whole string as a rectangle
  SDL_Surface *string_surf;
  len = strlen(s); //size of the string.
  //string_rect->w = len * b->w; //size of the string
  //string_rect->h = b->h;
  //string_rect->x = 0;
  //string_recy->y = 0;
  for(int i=0; i<len; i++) {
    //loop through i, and place characters in the right place.
    charrect.w = b->width;
    charrect.h = b->height;
    charrect.x = i*b->width;
    charrect.y = 0;
    SDL_BlitSurface(b->img, //blit the font
		    getchar_rect(b, &charrect, s[i]), //source rect of font
		    string_surf, //... to string_surf
		    &charrect);  //the dest rect on string_surf
  }
  return string_surf; //return string surface
}

void sdl_set_textpos(GameCore *gc, int x, int y)
{
  gc->c_text_size->x = x;
  gc->c_text_size->y = y;
}

//assume a bitmapfont texture is loaded

SDL_Texture* sdl_printf_fontTTF(GameCore *gc, TTF_Font *font, char *message)
{ //return a surface/texture that has teh text message
  //SDL_Surface *surf;
  //SDL_Texture *texture;
  //SDL_Rect ts;
  //TTF_SizeText(gc->font0, message, &gc->c_text_size->w, &gc->c_text_size->h);
  //surf = TTF_RenderText_Blended(font, message, gc->current_color);
  //texture = SDL_CreateTextureFromSurface(gc->renderer, surf);
  //return texture;
}
//SDL_Texture *sdl_printf_font(GameCore *gc, void *font, char *message)
//{ //wrap the sdl_printf_font fucntion, with either bitmap fonts, or ttf fonts.
//   SDL_Texture *t;
   //#ifdef SDLTTF
   //t = sdl_printf_fontTTF(gc, (TTF_Font)font, message);
   //#ifndef SDLTTF
   //do the bitmap font thing.
//  #endif
//   return t;
//}

//Same as above but use default font and color.
SDL_Texture* sdl_printf(GameCore *gc, char *message)
{ //Assumes you have already set a color!
  SDL_Surface *surf;
  SDL_Texture *texture;
  //SDL_Surface *sdlprint(bitmapfont b, char *s, int x, int y)
  surf = sdlprint(gc->current_font, message);
  //surf = TTF_RenderText_Blended(gc->current_font, message, gc->current_color);
  texture = SDL_CreateTextureFromSurface(gc->renderer, surf);
  return texture;
}

//void load_font(GameCore *gc, SDL_Surface)

void set_color(GameCore *gc, int r, int g, int b)
{
  gc->current_color.r = r;
  gc->current_color.g = g;
  gc->current_color.b = b;
}

//void start_ttf(GameCore *gc)
//{
//  if(!TTF_WasInit() && TTF_Init()==-1) {
//    printf("TTF_Init: %s\n", TTF_GetError());
//    exit(1);
//  }
  //TTF_Font *font0;
//  gc->font0 = TTF_OpenFont("data/font.ttf", 18);
//  if(!gc->font0) {
//    printf("TTF_OpenFont: %s\n", TTF_GetError()); // handle error
//  }
//}
//void stop_ttf(GameCore *gc)
//{
//  TTF_CloseFont(gc->font0);
//  gc->font0=NULL; // to be safe...
//  TTF_Quit();
//}
