#include <SDL.h>
#include <stdio.h>
#include "game.h"

void draw_chargen_menu(GameCore *gc);
void draw_character_attributes(GameCore *gc, int x, int y, int moddable);
void draw_character_1attribute(GameCore *gc, int x, int y, int stat, char *str); //macro to draw each
void draw_minusplus_buttons(GameCore *gc, int x, int y);
void draw_character_attributes(GameCore *gc, int x, int y, int moddable);//draw attribs in box
void draw_add_skills_dialogue(GameCore *gc); //puts a dialogue that lists the skills.

void handle_mousebutton_down_chargen_menu(GameCore *gc);

void fast_button(GameCore *gc, int x, int y, char *text);//render.c
SDL_Rect fast_rect(int x, int y, int w, int h);//render.c
void set_rect(SDL_Rect *r, int x, int y, int w, int h);

void rendertext(GameCore *gc, char *message);
void sdl_set_textpos(GameCore *gc, int x, int y); //text.c
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;
void fast_radio(GameCore *gc, int x, int y, char *text, int selected); //does not uncheck? //render.c
void draw_char_menu_frame(GameCore *gc); //backdrop frame


void draw_add_skills_dialogue(GameCore *gc)
{ //create a popup window which lists skills and how much to put into them by adding plus/minus buttons to the 
//left of each skill.
//frame and frame shadow are the border of the window. inside the window is the skillpane, a black box where the skills
//will be printed.  Bubblelist_frame is the border of bubblelist. Bubblelist is a box off to the right of the skill
//defines the skill, and is activated when clicking on a skill. below, near the bottom of the window is the "accept" button.
  SDL_Rect frame, frame_shadow, skillpane; //, bubblelist_frame, bubblelist;
  frame = fast_rect(50,50, gc->screen_size_x -50, gc->screen_size_y-50); //make a square
  frame_shadow = fast_rect(50 +3,50 +3, gc->screen_size_x -50 -3, gc->screen_size_x -50 -3); //make it looks nice?
  skillpane = fast_rect( 0 +3+10,50 +3+10, gc->screen_size_x -50 -3-10, gc->screen_size_y-50 -3 -10 );
  //print skills here
  fast_button(gc, gc->screen_size_x - 300, gc->screen_size_y -50 -3 -50, "Accept"); //accept button
}
void draw_char_menu_frame(GameCore *gc)
{
  //SDL_Rect dst, src, r;
  SDL_RenderCopy(gc->renderer, gc->w_background, NULL, NULL); //put background
  //put name on the top
  fast_button(gc, 10,10, gc->player->name); //- player name
  //put character here?
  //src = fast_rect(0,0,280,800); //set_rect(&gc->character_doll_rect, 0,0,280,800); //female rect x = 454, w = 220
  //dst = fast_rect(8,65,180,450);
  if( gc->game_state == GAME_PLAYER_STATUS) {
    fast_button(gc, 10,gc->screen_size_y - 58, "Close");
  }
  else {
    fast_button(gc, 10,gc->screen_size_y - 58, "Back");
    fast_button(gc, 300,gc->screen_size_y - 58, "Next");
  }
}
void draw_chargen_menu(GameCore *gc)
{//int screen_size_x, screen_size_y;
  SDL_Rect dst, src, r;
  src = fast_rect(0,0,280,800); //set_rect(&gc->character_doll_rect, 0,0,280,800); //female rect x = 454, w = 220
  dst = fast_rect(8,65,180,450);
  draw_char_menu_frame(gc); //draw background (with buttons)
  SDL_RenderCopy(gc->renderer, gc->character_doll, &gc->character_doll_rect, &dst); //put background
  sdl_set_textpos(gc, 210, 80); set_color(gc, 255, 255, 255);
  //SDL_RenderCopy(gc->renderer, sdl_printf_font(gc, "Gender"), NULL, gc->c_text_size);
  rendertext(gc, "Gender");
  if(gc->player->sex == 0) { //1 male, 0 female
    fast_radio(gc, 200, 100, "Male", 0 );
    fast_radio(gc, 200, 130, "Female", 1 );
  }
  else { //male 1
    fast_radio(gc, 200, 100, "Male", 1);
    fast_radio(gc, 200,130, "Female", 0);
  }
  sdl_set_textpos(gc, 210, 180); //set_color(gc, 255, 255, 255);
  //SDL_RenderCopy(gc->renderer, sdl_printf_font(gc, "Race"), NULL, gc->c_text_size);
  rendertext(gc, "Race"); 
  
  if(gc->player->race == 0) {  fast_radio(gc, 200, 200, "Human",1); }//0
  else { fast_radio(gc, 200, 200, "Human",0); }
  
  if(gc->player->race == 1) {  fast_radio(gc, 200, 230, "Elf",1); } //1
  else { fast_radio(gc, 200, 230, "Elf",0); }
  
  if(gc->player->race == 2) {  fast_radio(gc, 200, 260, "Dwarf",1); } //2
  else {fast_radio(gc, 200, 260, "Dwarf",0);}
  
  if(gc->player->race == 3) { fast_radio(gc, 200, 290, "Dark Elf",1); }//3
  else{fast_radio(gc, 200, 290, "Dark Elf",0);}//3
  
  if(gc->player->race == 4) { fast_radio(gc, 200, 320, "Goblin",1);}
  else{fast_radio(gc, 200, 320, "Goblin",0); }//4
  
  if(gc->player->race == 5) { fast_radio(gc, 200, 350, "Half-Ork",1); }
  else{fast_radio(gc, 200, 350, "Half-Ork",0);} //5

  r = fast_rect(gc->player->portrait*128,0,128,128);
  gc->char_frame_rect = fast_rect(323, 40, 128, 128 );
 
 if(gc->player->sex == 0) {  //check sex for portraits
  SDL_RenderCopy(gc->renderer, gc->portraits_human_male,&r, &gc->char_frame_rect); //TODO: get female portraits
  //check race, there are a total of 10 png's 
 }
 else { //1
  SDL_RenderCopy(gc->renderer, gc->portraits_human_male,&r, &gc->char_frame_rect); //male portraits
  //check race, there are a total of 10 png's 
 }
  SDL_RenderCopy(gc->renderer, gc->char_frame, NULL, &gc->char_frame_rect);  
  draw_minusplus_buttons(gc, 443, 145);
  draw_character_attributes(gc, gc->stat_panel_x, gc->stat_panel_y, 1);
}

#include <string.h>
void draw_character_1attribute(GameCore *gc, int x, int y, int stat, char *str)
{
  char stat_text[4];
  sdl_set_textpos(gc, x, y);
  //SDL_RenderCopy(gc->renderer, sdl_printf_font(gc, str), NULL, gc->c_text_size);
  rendertext(gc, str);
  sdl_set_textpos(gc,x+130,y);
  sprintf(stat_text, "%2d", stat);
  //SDL_RenderCopy(gc->renderer, sdl_printf_font(gc, stat_text), NULL, gc->c_text_size);
  rendertext(gc, stat_text);
}
void draw_minusplus_buttons(GameCore *gc, int x, int y)
{
  SDL_Rect dst, dst2;
  dst = fast_rect(x-32+20, y, 20, 20);
  dst2 = fast_rect(x-32, y, 20, 20);

  SDL_RenderCopy(gc->renderer, gc->t_buttons, &gc->button_minus_raised, &dst);
  SDL_RenderCopy(gc->renderer, gc->t_buttons, &gc->button_plus_raised, &dst2);
}
void draw_character_attributes(GameCore *gc, int x, int y, int moddable)
{
  //char stat_text[4];
  SDL_Rect stat_bg_frame, stat_fg_frame;
  stat_bg_frame.w = 200;  stat_bg_frame.h = 170; stat_bg_frame.x = x-35;
  stat_bg_frame.y = y-5;
  stat_fg_frame.w = 196;  stat_fg_frame.h = 166; stat_fg_frame.x = x-33;
  stat_fg_frame.y = y-3;

  //if moddable, display the -+ buttons
  SDL_SetRenderDrawColor(gc->renderer, 150,150,150,255);
  SDL_RenderFillRect(gc->renderer, &stat_bg_frame);
  SDL_SetRenderDrawColor(gc->renderer, 0,0,0,255);
  SDL_RenderFillRect(gc->renderer, &stat_fg_frame);
  //show buttongs here if moddable == 1
  if( moddable == 1) {
    draw_minusplus_buttons(gc, x, y);
    draw_minusplus_buttons(gc, x, y+20);
    draw_minusplus_buttons(gc, x, y+40);
    draw_minusplus_buttons(gc, x, y+60);
    draw_minusplus_buttons(gc, x, y+80);
    draw_minusplus_buttons(gc, x, y+100);
    draw_minusplus_buttons(gc, x, y+120);
    draw_minusplus_buttons(gc, x, y+140);
  }
  draw_character_1attribute(gc, x+10, y, gc->player->strength, "Strength");
  draw_character_1attribute(gc, x+10, y+20, gc->player->intelligence, "Intelligence");
  draw_character_1attribute(gc, x+10, y+40, gc->player->agility, "Agility");
  draw_character_1attribute(gc, x+10, y+60, gc->player->wisdom, "Wisdom");
  draw_character_1attribute(gc, x+10, y+80, gc->player->stamina, "Stamina");
  draw_character_1attribute(gc, x+10, y+100, gc->player->charisma, "Charisma");
  draw_character_1attribute(gc, x+10, y+120, gc->player->luck, "Luck");
  draw_character_1attribute(gc, x+10, y+140, gc->player->bonus_attr, "Bonus");
}

int check_clickedin(SDL_Rect *r, int mouse_x, int mouse_y)
{
  if(mouse_x >= r->x && mouse_x <= r->x+r->w && mouse_y >= r->y && mouse_y <= r->y+r->h){
    return 1;
  }
  else {
    return 0;
  }
}

void handle_mousebutton_down_chargen_menu(GameCore *gc)
{
  int i;
  SDL_Rect b1, b2;

  SDL_Rect mstrength, pstrength, mintell, pintell, magi, pagi; //plus and minus buttons
  SDL_Rect mwisdom, pwisdom, mstamina, pstamina, mcharisma, pcharisma, mluck, pluck;
  SDL_Rect mportrait, pportrait;
  SDL_Rect rmale, rfemale; //radio buttons for male/female
  SDL_Rect race_rect;
  //fast_radio(gc, 200, 100, "Male");
  //fast_radio(gc, 200, 130, "Female");

  rmale = fast_rect(200, 100, 28,28);
  rfemale = fast_rect(200,130,28,28);

  b1 = fast_rect(10, gc->screen_size_y - 58, 283 , 58);
  b2 = fast_rect(300, gc->screen_size_y - 58, 283 , 58);
  pstrength = fast_rect(gc->dst_stat_minus.x, gc->dst_stat_minus.y, gc->dst_stat_minus.w, gc->dst_stat_minus.h);
  mstrength = fast_rect(gc->dst_stat_plus.x, gc->dst_stat_plus.y, gc->dst_stat_plus.w, gc->dst_stat_plus.h);

  pintell = fast_rect(gc->dst_stat_minus.x, gc->dst_stat_minus.y+20, gc->dst_stat_minus.w, gc->dst_stat_minus.h);
  mintell = fast_rect(gc->dst_stat_plus.x, gc->dst_stat_plus.y  +20, gc->dst_stat_plus.w, gc->dst_stat_plus.h);

  pagi  = fast_rect(gc->dst_stat_minus.x, gc->dst_stat_plus.y  +20*2, gc->dst_stat_plus.w, gc->dst_stat_plus.h);
  magi  = fast_rect(gc->dst_stat_plus.x, gc->dst_stat_plus.y  +20*2, gc->dst_stat_plus.w, gc->dst_stat_plus.h);


  pwisdom  = fast_rect(gc->dst_stat_minus.x, gc->dst_stat_plus.y  +20*3, gc->dst_stat_plus.w, gc->dst_stat_plus.h);
  mwisdom  = fast_rect(gc->dst_stat_plus.x, gc->dst_stat_plus.y  +20*3, gc->dst_stat_plus.w, gc->dst_stat_plus.h);

  pstamina  = fast_rect(gc->dst_stat_minus.x, gc->dst_stat_plus.y  +20*4, gc->dst_stat_plus.w, gc->dst_stat_plus.h);
  mstamina  = fast_rect(gc->dst_stat_plus.x, gc->dst_stat_plus.y  +20*4, gc->dst_stat_plus.w, gc->dst_stat_plus.h);

  pcharisma  = fast_rect(gc->dst_stat_minus.x, gc->dst_stat_plus.y  +20*5, gc->dst_stat_plus.w, gc->dst_stat_plus.h);
  mcharisma  = fast_rect(gc->dst_stat_plus.x, gc->dst_stat_plus.y  +20*5, gc->dst_stat_plus.w, gc->dst_stat_plus.h);


  pluck  = fast_rect(gc->dst_stat_minus.x, gc->dst_stat_plus.y  +20*6, gc->dst_stat_plus.w, gc->dst_stat_plus.h);
  mluck  = fast_rect(gc->dst_stat_plus.x, gc->dst_stat_plus.y  +20*6, gc->dst_stat_plus.w, gc->dst_stat_plus.h);

  mportrait = fast_rect(413,145, 20,20);
  pportrait = fast_rect(413+20, 145, 20,20);
  //draw_minusplus_buttons(gc, 443, 145);
  
  if( check_clickedin(&b1, gc->mouse_x, gc->mouse_y ) == 1 ) {
    printf("Go Back.\n");
    gc->game_state = GAME_START_MENU;
  }
  else if ( check_clickedin(&mportrait, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->portrait > 0 ) {gc->player->portrait--;}
  }
  else if ( check_clickedin(&pportrait, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->portrait < 2 ) {gc->player->portrait++;}
  }
  else if ( check_clickedin(&b2, gc->mouse_x, gc->mouse_y ) == 1 ) {
    //gc->game_state = GAME_PLAY_INTRO_STORY;
    gc->game_state = GAME_PLAY_IDLE;
    printf("(still in chargen).\n");
  }
  else if ( check_clickedin(&mstrength, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->strength > 1) {
      gc->player->strength--;
    }
  }
  else if ( check_clickedin(&pstrength, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->bonus_attr > 0 ) {
      gc->player->strength++;
      gc->player->bonus_attr--;
    }
  }
  else if ( check_clickedin(&pintell, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->bonus_attr > 0 ) {
      gc->player->intelligence++;
      gc->player->bonus_attr--;
    }
  }
  else if ( check_clickedin(&mintell, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->intelligence > 1) {
      gc->player->intelligence--;
    }
  }
  else if ( check_clickedin(&magi, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->agility > 1) {
      gc->player->agility--;
    }
  }
  else if ( check_clickedin(&pagi, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->bonus_attr > 0 ) {
      gc->player->agility++;
      gc->player->bonus_attr--;
    }
  }
  else if ( check_clickedin(&mwisdom, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->wisdom > 1) {
      gc->player->wisdom--;
    }
  }
  else if ( check_clickedin(&pwisdom, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->bonus_attr > 0 ) {
      gc->player->wisdom++;
      gc->player->bonus_attr--;
    }
  }
  else if ( check_clickedin(&mstamina, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->stamina > 1) {
      gc->player->stamina--;
    }
  }
  else if ( check_clickedin(&pstamina, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->bonus_attr > 0 ) {
      gc->player->stamina++;
      gc->player->bonus_attr--;
    }
  }
  else if ( check_clickedin(&mcharisma, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->charisma > 1) {
      gc->player->charisma--;
    }
  }
  else if ( check_clickedin(&pcharisma, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->bonus_attr > 0 ) {
      gc->player->charisma++;
      gc->player->bonus_attr--;
    }
  }
  else if ( check_clickedin(&mluck, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->luck > 1) {
      gc->player->luck--;
    }
  }
  else if ( check_clickedin(&pluck, gc->mouse_x, gc->mouse_y ) == 1 ) {
    if(gc->player->bonus_attr > 0 ) {
      gc->player->luck++;
      gc->player->bonus_attr--;
    }
  }
  //rmale = fast_rect(200, 100, 28,28);
  //rfemale = fast_rect(300,130,28,28);
  //src = fast_rect(0,0,280,800); //set_rect(&gc->character_doll_rect, 0,0,280,800); //female rect x = 454, w = 220
  else if ( check_clickedin(&rmale, gc->mouse_x, gc->mouse_y ) == 1 ) {
    gc->player->sex = 1;
    printf("selected male\n");
    set_rect(&gc->character_doll_rect, 0,0,280,800);
  }
  else if ( check_clickedin(&rfemale, gc->mouse_x, gc->mouse_y ) == 1 ) {
    gc->player->sex = 0;
    printf("selected female\n");
    set_rect(&gc->character_doll_rect, 454,0,220,800);
  }
  
  for(i=0;i<6;i++) {
    race_rect = fast_rect(200,200+i*30,28,28);
    if(check_clickedin(&race_rect, gc->mouse_x, gc->mouse_y ) == 1) {
      gc->player->race = i;
      break;
    }
  }
  

  //loop through these and see if one was clicked?
  //race  a->race = 0;
  /*  fast_radio(gc, 200, 200, "Human",0); //0
  fast_radio(gc, 200, 230, "Elf",0); //1
  fast_radio(gc, 200, 260, "Dwarf",0); //2
  fast_radio(gc, 200, 290, "Dark Elf",0);//3
  fast_radio(gc, 200, 320, "Goblin",0); //4
  fast_radio(gc, 200, 350, "Half-Ork",0); //4*/
  //else if ( check_clickedin(&rradio_race_human, gc->mouse_x, gc->mouse_y ) == 1 ) {
  //  a->race=human;
  //}
  //gc->dst_stat_minus = fast_rect(gc->stat_panel_x-32+20, gc->stat_panel_y, 20, 20); //first buttons for plus/minus on
  //gc->dst_stat_plus = fast_rect( gc->stat_panel_x-32, gc->stat_panel_y, 20, 20); //stat sheets
}
