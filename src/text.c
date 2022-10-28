//#include <SDL_ttf.h>
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

#define FWIDTH 16
#define FHEIGHT 24

SDL_Rect fast_rect(int x, int y, int w, int h);

/*replace with whatever Image loading function you have.
SDL_Texture* IMG_Load_w_error(GameCore *gc, char * imgfile);
*/

/*
  void load_font(GameCore *gc, char *bmpfile); //Load a bmp file into current_font
  load_font will load a bitmap file into a pointer to SDL_Texture
  For simplicity use a bitmap font that goes
  !"#$%&'()*,=./012345678... etc AND follows the AsCII numbering
  void load_font(SDL_Renderer * r, SDL_Texture *t, char *bmpfile);
*/


void sdl_set_textpos(SDL_Rect *text_rect, int x, int y); //text.c
//void rendertext(GameCore *gc, char *message);
SDL_Texture* sdl_printf_font(GameCore *gc, char * message); //calls txt currently
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;
void rendertext(SDL_Renderer *r, SDL_Texture *t, int x, int y, char *message);


void sdl_set_textpos(SDL_Rect *text_rect, int x, int y) { //text.c
	text_rect->x = x;
	text_rect->y = y;
	text_rect->w = 16;
	text_rect->h = 24;
}

//top = (ascii - 32) / 16 * 12;
//left = (ascii - 32) % 16 * 8;
void rendertext(SDL_Renderer *r, SDL_Texture *t, int x, int y, char *message){
  //printf("render text starting: %s\n", message);
  int l = strlen(message);
  SDL_Texture *wholetext;
  char c; //current letter in string
  for(int i=0; i < l; i++) {
    c = message[i]; //current letter in string
    int top = (c - 32) / 16 *12;  //gc->current_font->w / 96;
    int left = (c - 32) % 16 * 8; //12; //gc->current_font->h;
    SDL_Rect s = fast_rect(left,    //X
			   top,   //Y
			   8,     //W
			   12);   //H
    SDL_Rect d = fast_rect(x,y,8,12);
    SDL_RenderCopy(r,   //renderer
    		   t,   //text of font
    		   &s,  //letter of font to render
    		   &d   //where to render it.
		   );
  }
}


  void set_color(GameCore *gc, int r, int g, int b) { //set_font_color;
  gc->current_color.r = r;
  gc->current_color.b = b;
  gc->current_color.g = g;
  }
  

/*SDL_Rect fast_rect(int x, int y, int w, int h){
  SDL_Rect r;
  r.x = x; r.y = y; r.w=w; r.h=h;
  return r;
};*/
