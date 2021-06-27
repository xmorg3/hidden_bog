
#include <SDL.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void handle_keydown(GameCore *gc);
void handle_mousebutton_down(GameCore *gc);
void handle_mousebutton_down_start_menu(GameCore *gc);
void handle_mousebutton_down_chargen_menu(GameCore *gc); //chargen.c
void handle_mousebutton_down_options_menu(GameCore *gc); //gameoptions.c
void handle_mousebutton_down_gameplayidle(GameCore *gc);

void resize_screen(GameCore *gc, int size_x, int size_y);//render.c
void set_player_direction(GameCore *gc, int mod); //update.c
void set_player_move_foreward(GameCore *gc); //update.c
void set_player_move_backward(GameCore *gc); //update.c?

void draw_sheet_character(GameCore *gc);
void input_char_menu_frame(GameCore *gc);

int get_object_in_0front_location(GameCore *gc);

void input(GameCore *gc)
{
  while (SDL_PollEvent(&gc->sdl_event ) ){
    if (gc->sdl_event.type == SDL_QUIT) {//If user closes the window
      gc->game_state = GAME_QUIT;
    }
    else if (gc->sdl_event.type == SDL_KEYDOWN)//If user presses any key
      handle_keydown(gc);
    else if (gc->sdl_event.type == SDL_MOUSEBUTTONDOWN)//If user clicks the mouse
      handle_mousebutton_down(gc);
  }
}

void handle_keydown(GameCore *gc)
{
  int k;
  //gc->game_state = 0;
  k = gc->sdl_event.key.keysym.sym;
  if(k == SDLK_F1) {
    resize_screen(gc, 1024, 600); //resize teh window
  }
  if(k == SDLK_ESCAPE ) {   //---------------------------------ESCAPE
    gc->game_state = GAME_START_MENU;
  }
  if(k == SDLK_LEFT && gc->game_state == GAME_PLAY_IDLE) { //--LEFT
    set_player_direction(gc, -1);

  }
  else if(k == SDLK_RIGHT && gc->game_state == GAME_PLAY_IDLE ) {//RIGHT
    set_player_direction(gc, 1);
  }
  else if(k == SDLK_UP && gc->game_state == GAME_PLAY_IDLE ) {//UP
    //move forward.
    set_player_move_foreward(gc); //update.c
  }
  else if(k == SDLK_DOWN && gc->game_state == GAME_PLAY_IDLE ) {//DOWN
    set_player_move_backward(gc); //??
  }
  else if(k == SDLK_c ) { //draw sheet
  	if (gc->game_state == GAME_PLAYER_STATUS) {
  		gc->game_state = GAME_PLAY_IDLE;
  	}
  	else { gc->game_state = GAME_PLAYER_STATUS;	}
  }
   else if(k == SDLK_i ) { //draw sheet
  	if (gc->game_state == GAME_PLAYER_INVENTORY) {
  		gc->game_state = GAME_PLAY_IDLE;
  	}
  	else { gc->game_state = GAME_PLAYER_INVENTORY;	}
  }
   else if(k == SDLK_n ) {
     if ( gc->game_state == GAME_START_MENU ) {
       gc->game_state = GAME_CHARGEN_MENU;
     }
   }
}
void handle_mousebutton_down(GameCore *gc)
{
  if( gc->game_state == GAME_START_MENU) {
    handle_mousebutton_down_start_menu(gc);
  }
  else if (gc->game_state == GAME_CHARGEN_MENU) {
    handle_mousebutton_down_chargen_menu(gc); //chargen.c ?
  }
  else if (gc->game_state == GAME_PLAYER_STATUS) {
    input_char_menu_frame(gc); //character_sheet.c
  }
  else if (gc->game_state == GAME_OPTIONS_MENU) {
    handle_mousebutton_down_options_menu(gc);
  }
  else if (gc->game_state == GAME_PLAY_IDLE) { //what are we clicking on?
  //you clicked on the character portrait //open status sheet.
  //you clicked on a "backpack" icon?
  //you clicked an object /chest/monster/npc/door ?what location?
    handle_mousebutton_down_gameplayidle(gc);
  }
}
void handle_mousebutton_down_start_menu(GameCore *gc)
{//find the clickys!
  int button_row, button_col; //, button_col1_to;
  button_row = 150;//+55
  button_col = 15;//
  SDL_GetMouseState(&gc->mouse_x, &gc->mouse_y);
  if(gc->mouse_x >= button_col && gc->mouse_x <= button_col+283 &&
     gc->mouse_y >= button_row+55*4 &&
     gc->mouse_y <= (button_row+55*4)+55) {
    printf("Game Quit.\n");
    gc->game_state = GAME_QUIT;
  }
  else if (gc->mouse_x >= button_col && gc->mouse_x <= button_col+283 &&
	   gc->mouse_y >= button_row &&
	   gc->mouse_y <= (button_row)+55) {
    gc->game_state = GAME_CHARGEN_MENU;
    printf("New Game.\n");
  }
  else if (gc->mouse_x >= button_col && gc->mouse_x <= button_col+283 &&
	   gc->mouse_y >= button_row+55*1 &&
	   gc->mouse_y <= (button_row+55*1)+55) {
    printf("Load Game.\n");
  }
  else if (gc->mouse_x >= button_col && gc->mouse_x <= button_col+283 &&
	   gc->mouse_y >= button_row+55*2 &&
	   gc->mouse_y <= (button_row+55*2)+55) {
    printf("Save Game.\n");
  }
  else if (gc->mouse_x >= button_col && gc->mouse_x <= button_col+283 &&
	   gc->mouse_y >= button_row+55*3 &&
	   gc->mouse_y <= (button_row+55*3)+55) {
    gc->game_state = GAME_OPTIONS_MENU;
    printf("Options.\n");
  }
}
int get_object_in_0front_location(GameCore *gc)
{
	//what direction am i facing
	//what is the *int* of object_layer directly in front of me 0=nothing
	//return that int.
	return 0; //default
}
void handle_mousebutton_down_gameplayidle(GameCore *gc) //you clicked on a mouse button during idle
{
	//doors - if you are standing in front of a door (direction/and item in front of you)
	//^^ --return something if you are standing in front of a door.
	
}
