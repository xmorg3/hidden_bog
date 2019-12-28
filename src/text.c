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
//int TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h);
//int TTF_FontHeight(const TTF_Font *font)
//SDL_Surface *TTF_RenderText_Solid(TTF_Font *font, const char *text, SDL_Color fg)
// SDL_Color color={0,0,0};
//  SDL_Surface *text_surface;
//   if(!(text_surface=TTF_RenderText_Solid(font,"Hello World!",color))) {
//handle error here, perhaps print TTF_GetError at least
//   } else {
//   SDL_BlitSurface(text_surface,NULL,screen,NULL);
//   //perhaps we can reuse it, but I assume not for simplicity.
//   SDL_FreeSurface(text_surface);
//   }
// */

void sdl_set_textpos(GameCore *gc, int x, int y);

SDL_Texture* sdl_printf_fontTTF(GameCore *gc, TTF_Font *font, char *message);
SDL_Texture* sdl_printf_font(GameCore *gc, SDL_Surface *font, char *message);


SDL_Texture* sdl_printf(GameCore *gc, char *message);
void set_color(GameCore *gc, int r, int g, int b);
void start_ttf(GameCore *gc);
void stop_ttf(GameCore *gc);


void sdl_set_textpos(GameCore *gc, int x, int y)
{
  gc->c_text_size->x = x;
  gc->c_text_size->y = y;
}

SDL_Texture* sdl_printf_fontTTF(GameCore *gc, TTF_Font *font, char *message)
{ //return a surface/texture that has teh text message
  SDL_Surface *surf;
  SDL_Texture *texture;
  //SDL_Rect ts;
  TTF_SizeText(gc->font0, message, &gc->c_text_size->w, &gc->c_text_size->h);
  surf = TTF_RenderText_Blended(font, message, gc->current_color);
  texture = SDL_CreateTextureFromSurface(gc->renderer, surf);
  return texture;
}
SDL_Texture *sdl_printf_font(GameCore *gc, void *font, char *message)
{ //wrap the sdl_printf_font fucntion, with either bitmap fonts, or ttf fonts.
   SDL_Texture *t;
  #ifdef SDLTTF
   t = sdl_printf_fontTTF(gc, (TTF_Font)font, message);
  #ifndef SDLTTF
   //do the bitmap font thing.
  #endif
   return t;
}

//Same as above but use default font and color.
SDL_Texture* sdl_printf(GameCore *gc, char *message)
{ //Assumes you have already set a color!
  SDL_Surface *surf;
  SDL_Texture *texture;
  surf = TTF_RenderText_Blended(gc->current_font, message, gc->current_color);
  texture = SDL_CreateTextureFromSurface(gc->renderer, surf);
  return texture;
}

void set_color(GameCore *gc, int r, int g, int b)
{
  gc->current_color.r = r;
  gc->current_color.g = g;
  gc->current_color.b = b;
}

void start_ttf(GameCore *gc)
{
  if(!TTF_WasInit() && TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(1);
  }
  //TTF_Font *font0;
  gc->font0 = TTF_OpenFont("data/font.ttf", 18);
  if(!gc->font0) {
    printf("TTF_OpenFont: %s\n", TTF_GetError()); // handle error
  }
}
void stop_ttf(GameCore *gc)
{
  TTF_CloseFont(gc->font0);
  gc->font0=NULL; // to be safe...
  TTF_Quit();
}
