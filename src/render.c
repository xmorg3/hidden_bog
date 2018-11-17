#include <SDL.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void draw(GameCore *gc); // main drawing
void draw_playframe(GameCore *gc);
void draw_playport(GameCore *gc);

void draw_playport_north(GameCore *gc);
void draw_playport_east(GameCore *gc);
void draw_playport_south(GameCore *gc);
void draw_playport_west(GameCore *gc);

void draw_oov0(GameCore *gc, int left, int middle, int right);

void draw_game_menu(GameCore *gc);
void draw_chargen_menu(GameCore *gc); //chargen.c
void draw_options_menu(GameCore *gc); //gameoptions.c
void draw_mapport(GameCore *gc);
void draw_character_portraits(GameCore *gc);
void set_map_tile_color(GameCore *gc, int location_x, int location_y, int x, int y);
void fast_button(GameCore *gc, int x, int y, char *text);
SDL_Rect fast_rect(int x, int y, int w, int h);
void fast_radio(GameCore *gc, int x, int y, char *text, int selected); //does not uncheck?
//void display_render(GameCore *gc);
void draw_sheet_character(GameCore *gc);

//text.c
SDL_Texture* sdl_printf_font(GameCore *gc, TTF_Font *font, char *message);
void sdl_set_textpos(GameCore *gc, int x, int y);
void set_color(GameCore *gc, int r, int g, int b); //set_font_color;

void draw_message_frame(GameCore *gc);
void resize_screen(GameCore *gc, int size_x, int size_y);

//void gl_draw_game_menu(GameCore *gc); //glfunctions.c

//void draw_background_texture(GameCore *gc, SDL_Texture *t);

void draw(GameCore *gc)
{
  SDL_RenderClear(gc->renderer); //clear screen?  
  if(gc->game_state == GAME_START_MENU) {
    draw_game_menu(gc);
  }
  else if (gc->game_state == GAME_CHARGEN_MENU) {
    draw_chargen_menu(gc);
  }
  else if (gc->game_state == GAME_OPTIONS_MENU) {
    draw_options_menu(gc);
  }
  else if (gc->game_state == GAME_PLAY_INTRO_STORY) {
  }
  else if (gc->game_state == GAME_PLAY_IDLE) {
    
    draw_playport(gc);
    draw_playframe(gc);
  }
  else if (gc->game_state == GAME_PLAYER_MOVE) {
  }
  else if (gc->game_state == GAME_PLAYER_COMBAT){
  }
  else if (gc->game_state == GAME_PLAYER_STATUS){
  	draw_sheet_character(gc);
  }
  else if (gc->game_state == GAME_PLAYER_INVENTORY){
  }
  else if (gc->game_state == GAME_PLAYER_CONVERSATION){
  }
  else if (gc->game_state == GAME_PLAYER_CRAFTING) {
  }
  else{
    //draw_playframe(gc);
  }
  //end drawing code
  SDL_RenderPresent(gc->renderer);
}
void draw_playframe(GameCore *gc)
{ //draw frame with other items inside.
  //SDL_RenderCopy(gc->renderer, gc->t_background, NULL, NULL); //put background
  //SDL_GetRenderDrawColor(gc->renderer, 0,0,0,0); 
  //SDL_SetRenderDrawColor(gc->renderer, 0,0,0,0);
  //SDL_RenderFillRect(gc->renderer, &gc->player_viewport);  // message_log, tabbed_pane;
  //SDL_RenderFillRect(gc->renderer, &gc->message_log);
  //SDL_RenderFillRect(gc->renderer, &gc->tabbed_pane);
  //draw_message_frame(gc);
  draw_character_portraits(gc);
  draw_mapport(gc);
}

void draw_playport(GameCore *gc) //draw the play viewport
{
  //sky and floor
  SDL_RenderCopy(gc->renderer, gc->sky_top_fobx_blank, NULL, &gc->player_viewport);
  SDL_RenderCopy(gc->renderer, gc->floor_bottom_fobx_blank, NULL, &gc->player_viewport);
  if(gc->player->direction == NORTH) {
    draw_playport_north(gc);
  }
  if(gc->player->direction == EAST) {
    draw_playport_east(gc);
  }
  if(gc->player->direction == SOUTH) {
    draw_playport_south(gc);
  }
  if(gc->player->direction == WEST) {
    draw_playport_west(gc);
  }
  SDL_RenderCopy(gc->renderer, gc->play_port_frame, NULL, &gc->player_viewport_frame);
}


/* New wall dimensions for wall_all
picture 598x273
leftwall( at right, x618 w118)
rightwall(at left x0 w118)
middle wall x115 w505 (at 619)
*/

//left(2-3,4), right, middle
void draw_fov2(GameCore *gc, int left, int middle, int right)
{//gc->wall_all
  SDL_Rect left_wall, right_wall, middle_wall;
  left_wall = fast_rect(618, 0, 118, 273);
  right_wall = fast_rect(0, 0, 118, 273);
  middle_wall = fast_rect(115, 0, 505,273);
  if( left == 2) {
    SDL_RenderCopy(gc->renderer, gc->wall_left_fov2_blank, NULL, &gc->player_viewport);
  }
  if ( left == 3 ) {
    SDL_RenderCopy(gc->renderer, gc->tall_wall_left_fov2, NULL, &gc->player_viewport);
  }
  if( left == 4) {
    SDL_RenderCopy(gc->renderer, gc->wall_left_fov2_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_left_fov2_blank, NULL, &gc->player_viewport);
  }
  if( right ==2)  {SDL_RenderCopy(gc->renderer, gc->wall_right_fov2_blank, NULL, &gc->player_viewport);}
  if( right == 3)  {SDL_RenderCopy(gc->renderer, gc->tall_wall_right_fov2, NULL, &gc->player_viewport);}
  if( right == 4) {
    SDL_RenderCopy(gc->renderer, gc->wall_right_fov2_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_right_fov2_blank, NULL, &gc->player_viewport);
  }
  
  if( middle==2)  {SDL_RenderCopy(gc->renderer, gc->wall_front_fov1_blank, NULL, &gc->player_viewport);}
  if( middle ==3)  {SDL_RenderCopy(gc->renderer, gc->tall_wall_front_fov1, NULL, &gc->player_viewport);}
  if( middle==4)  {
    SDL_RenderCopy(gc->renderer, gc->wall_front_fov1_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_front_fov1_blank, NULL, &gc->player_viewport);
  }
}
void draw_fov1(GameCore *gc, int left, int middle, int right)
{
  SDL_Rect left_wall, right_wall, middle_wall;
  left_wall = fast_rect(618, 0, 118, 273);
  right_wall = fast_rect(0, 0, 118, 273);
  middle_wall = fast_rect(115, 0, 505,273);
  if( left==2 )  {
    SDL_RenderCopy(gc->renderer, gc->wall_left_fov1_blank, NULL, &gc->player_viewport);
  }
  if( left ==3)  {
    SDL_RenderCopy(gc->renderer, gc->tall_wall_left_fov1, NULL, &gc->player_viewport);
  }
  if( left == 4)  {
    SDL_RenderCopy(gc->renderer, gc->wall_left_fov1_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_left_fov1_blank, NULL, &gc->player_viewport);
  }
  if( right ==2) {SDL_RenderCopy(gc->renderer, gc->wall_right_fov1_blank, NULL, &gc->player_viewport);}
  if( right ==3) {SDL_RenderCopy(gc->renderer, gc->tall_wall_right_fov1, NULL, &gc->player_viewport);}
  if( right == 4)  {
    SDL_RenderCopy(gc->renderer, gc->wall_right_fov1_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_right_fov1_blank, NULL, &gc->player_viewport);
  }
  if( middle==2)  {SDL_RenderCopy(gc->renderer, gc->wall_front_fov0_blank, NULL, &gc->player_viewport);}
  if( middle ==3)  {SDL_RenderCopy(gc->renderer, gc->tall_wall_front_fov0, NULL, &gc->player_viewport);}
  if( middle == 4)  {
    SDL_RenderCopy(gc->renderer, gc->wall_front_fov0_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_front_fov0_blank, NULL, &gc->player_viewport);
  }
}
void draw_fov0(GameCore *gc, int left, int middle, int right)
{
  SDL_Rect left_wall, right_wall, middle_wall;
  //SDL_Rect drect;
  left_wall = fast_rect(618, 0, 118, 273);
  right_wall = fast_rect(0, 0, 118, 273);
  middle_wall = fast_rect(115, 0, 505,273);

  // ------------------------------------->walls
  if( left==2)  {
    SDL_RenderCopy(gc->renderer, gc->wall_left_fov0_blank, NULL, &gc->player_viewport);}
  if( left ==3)  {
    SDL_RenderCopy(gc->renderer, gc->tall_wall_left_fov0, NULL, &gc->player_viewport);}
  if( left == 4)  {
    SDL_RenderCopy(gc->renderer, gc->wall_left_fov0_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_left_fov0_blank, NULL, &gc->player_viewport);
  }
  
  if( right==2  ) {
    SDL_RenderCopy(gc->renderer, gc->wall_right_fov0_blank, NULL, &gc->player_viewport);
  }
  if( right ==3 ) {
    SDL_RenderCopy(gc->renderer, gc->tall_wall_right_fov0, NULL, &gc->player_viewport);
  }
  if( right == 4)  {
    SDL_RenderCopy(gc->renderer, gc->wall_right_fov0_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_right_fov0_blank, NULL, &gc->player_viewport);
  }
   
  if( middle==2)  { //middle wall
    SDL_RenderCopy(gc->renderer, gc->wall_front_fov0_blank, NULL, &gc->player_viewport);
  }
  if( middle ==3)  { //middle wall
    SDL_RenderCopy(gc->renderer, gc->tall_wall_front_fov0, NULL, &gc->player_viewport);
  } 
  if( middle == 4)  {
    SDL_RenderCopy(gc->renderer, gc->wall_front_fov0_blank, NULL, &gc->player_viewport);
    SDL_RenderCopy(gc->renderer, gc->door_front_fov0_blank, NULL, &gc->player_viewport);
  }
}

SDL_Texture * get_texture_by_objectid(GameCore *gc, int textureid)
{
  int i;
  for(i=0; i<25; i++){
    if(gc->npc_list[i].npc_map_id == textureid) {
      return gc->npc_list[i].sprite;
    }
  }
  return NULL;
}
void draw_oov0(GameCore *gc, int left, int middle, int right) //drop objects in view
{
  if( left >=1000 ) {
  	SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,left), NULL, &gc->vp0_object_left);//, &gc->player_viewport);
  }
  if( right >=1000 ) {
  	SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,right), NULL,&gc->vp0_object_right);//, &gc->player_viewport);
  }
  if(middle >= 1000) { //its an object
    SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,middle), NULL, &gc->player_viewport); //NOTE! make them as big as the viewport!
  }
  
}

void draw_oov1(GameCore *gc, int left, int middle, int right) //drop objects in view
{
  if( left >=1000 ) {
  	SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,left), NULL, &gc->vp1_object_left);//, &gc->player_viewport);
  }
  if( right >=1000 ) {
  	SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,right), NULL,&gc->vp1_object_right);//, &gc->player_viewport);
  }
  if(middle >= 1000) { //its an object
    SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,middle), NULL, &gc->vp1_object_middle); //NOTE! make them as big as the viewport!
  } //vp0_object_left, vp0_object_right, 
  
}

void draw_playport_north(GameCore *gc)
{
  //int current_tile; //set value to whatever tile we are rendering.
  draw_fov2(gc, gc->current_map->background_layer[gc->player->map_y-2][gc->player->map_x-1],
	    gc->current_map->background_layer[    gc->player->map_y-2][gc->player->map_x],
	    gc->current_map->background_layer[    gc->player->map_y-2][gc->player->map_x+1]);
  
  draw_fov1(gc,
	    gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x-1],
	    gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x  ],
	    gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x+1]);
  draw_oov1(gc,
	    gc->current_map->object_layer[gc->player->map_y-1][gc->player->map_x-1],
	    gc->current_map->object_layer[gc->player->map_y-1][gc->player->map_x  ],
	    gc->current_map->object_layer[gc->player->map_y-1][gc->player->map_x+1]);
  draw_fov0(gc, gc->current_map->background_layer[gc->player->map_y][gc->player->map_x-1],
	    gc->current_map->background_layer[    gc->player->map_y][gc->player->map_x],
	    gc->current_map->background_layer[    gc->player->map_y][gc->player->map_x+1]);
  	   
  draw_oov0(gc, 
	    gc->current_map->object_layer[ gc->player->map_y][gc->player->map_x-1],
	    gc->current_map->object_layer[ gc->player->map_y][gc->player->map_x],
	    gc->current_map->object_layer[ gc->player->map_y][gc->player->map_x+1]);
}

void draw_playport_east(GameCore *gc)
{
  //int current_tile; //set value to whatever tile we are rendering.
  draw_fov2(gc, gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x+2],
	    gc->current_map->background_layer[    gc->player->map_y  ][gc->player->map_x+2],
	    gc->current_map->background_layer[    gc->player->map_y+1][gc->player->map_x+2]);
  
  draw_fov1(gc, gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x+1],
	    gc->current_map->background_layer[gc->player->map_y][gc->player->map_x+1],
	    gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x+1]);
  draw_oov1(gc,gc->current_map->object_layer[gc->player->map_y-1][gc->player->map_x+1],
	    gc->current_map->object_layer[gc->player->map_y][gc->player->map_x+1],
	    gc->current_map->object_layer[gc->player->map_y+1][gc->player->map_x+1]);
  draw_fov0(gc, gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x],
	    gc->current_map->background_layer[gc->player->map_y][gc->player->map_x],
	    gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x]);
  draw_oov0(gc, gc->current_map->object_layer[gc->player->map_y-1][gc->player->map_x],
	    gc->current_map->object_layer[gc->player->map_y][gc->player->map_x],
	    gc->current_map->object_layer[gc->player->map_y+1][gc->player->map_x]);
}
void draw_playport_south(GameCore *gc)
{
  //int current_tile; //set value to whatever tile we are rendering.
  //current_tile = gc->current_map->tiles[gc->player->map_y-1][gc->player->map_x+2];
  draw_fov2(gc, gc->current_map->background_layer[gc->player->map_y+2][gc->player->map_x+1],
	    gc->current_map->background_layer[gc->player->map_y+2][gc->player->map_x],
	    gc->current_map->background_layer[gc->player->map_y+2][gc->player->map_x-1]);
  
  draw_fov1(gc, gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x+1],
	    gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x],
	    gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x-1]);
  draw_oov1(gc,gc->current_map->object_layer[gc->player->map_y+1][gc->player->map_x+1],
	    gc->current_map->object_layer[gc->player->map_y+1][gc->player->map_x],
	    gc->current_map->object_layer[gc->player->map_y+1][gc->player->map_x-1]);


  draw_fov0(gc, gc->current_map->background_layer[gc->player->map_y][gc->player->map_x+1],    
	    gc->current_map->background_layer[gc->player->map_y][gc->player->map_x],
	    gc->current_map->background_layer[gc->player->map_y][gc->player->map_x-1]);
  draw_oov0(gc, gc->current_map->object_layer[gc->player->map_y][gc->player->map_x+1],    
	    gc->current_map->object_layer[gc->player->map_y][gc->player->map_x],
	    gc->current_map->object_layer[gc->player->map_y][gc->player->map_x-1]);
}
void draw_playport_west(GameCore *gc)
{
  draw_fov2(gc, gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x-2],
	    gc->current_map->background_layer[    gc->player->map_y][gc->player->map_x-2],
	    gc->current_map->background_layer[    gc->player->map_y-1][gc->player->map_x-2]);
  
  draw_fov1(gc, gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x-1],
	    gc->current_map->background_layer[    gc->player->map_y][gc->player->map_x-1],
	    gc->current_map->background_layer[    gc->player->map_y-1][gc->player->map_x-1]);
  draw_oov1(gc,gc->current_map->object_layer[gc->player->map_y+1][gc->player->map_x-1],
	    gc->current_map->object_layer[    gc->player->map_y][gc->player->map_x-1],
	    gc->current_map->object_layer[    gc->player->map_y-1][gc->player->map_x-1]);
  draw_fov0(gc, gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x],    
	    gc->current_map->background_layer[    gc->player->map_y  ][gc->player->map_x],
	    gc->current_map->background_layer[    gc->player->map_y-1][gc->player->map_x]);
  draw_oov0(gc, gc->current_map->object_layer[gc->player->map_y+1][gc->player->map_x],    
	    gc->current_map->object_layer[    gc->player->map_y  ][gc->player->map_x],
	    gc->current_map->object_layer[    gc->player->map_y-1][gc->player->map_x]);
}

void draw_message_frame(GameCore *gc)
{
  int i;
  set_color(gc, 255, 255, 255);
  for(i=0; i<6; i++) {
    sdl_set_textpos(gc, gc->message_log.x + 5, gc->message_log.y + 5+(i*20)); 
    SDL_RenderCopy(gc->renderer,
		   sdl_printf_font(gc, gc->font0, gc->messagelist[i]),
		   NULL,
		   gc->c_text_size);
  }
}

void set_map_tile_color(GameCore *gc, int location_x, int location_y, int x, int y)
{
  if( y == 4 && x == 4) { //the players location
    SDL_SetRenderDrawColor(gc->renderer, 100,0,0,0);
  } 
  else if((location_y > 0 && location_x > 0 &&  // V--- set fog color
	   location_y < gc->mapsize &&
	   location_x < gc->mapsize) &&
	  gc->current_map->fog_layer[location_y][location_x] == 0 )
    {
      SDL_SetRenderDrawColor(gc->renderer, 20,20,20,0);
    }
  else if( (location_y > 0 && location_x > 0 &&
	    location_y < gc->mapsize &&
	    location_x < gc->mapsize) &&
	   gc->current_map->background_layer[location_y][location_x] == 2) {  //walls
    SDL_SetRenderDrawColor(gc->renderer, 50,50,50,0);
  }
  else if( (location_y > 0 && location_x > 0 && location_y < gc->mapsize &&
	    location_x < gc->mapsize) && gc->current_map->background_layer[location_y][location_x] == 3) { //tall walls
	SDL_SetRenderDrawColor(gc->renderer, 50,50,50,0);
  }
  else if( (location_y > 0 && location_x > 0 && location_y < gc->mapsize &&
	    location_x < gc->mapsize) && gc->current_map->background_layer[location_y][location_x] == 4) { //doors
    SDL_SetRenderDrawColor(gc->renderer, 50,80,50,0);
  }
  else { //-- set walkable
    SDL_SetRenderDrawColor(gc->renderer, 180,180,180,0);
  }
}
void draw_character_portraits(GameCore *gc)
{
  int fr_x, fr_y, cr_w, cr_h;
  SDL_Rect r;
  fr_x = gc->screen_size_x / 75; //5;
  fr_y = (gc->screen_size_y / 75)*74 - 128;
  cr_w = 128;
  cr_h = 128;
  gc->char_frame_rect = fast_rect(fr_x, fr_y, cr_w, cr_h );
  r= fast_rect(gc->player->portrait*128,0,128,128);
  SDL_RenderCopy(gc->renderer, gc->portraits_human_male,&r, &gc->char_frame_rect);
  SDL_RenderCopy(gc->renderer, gc->char_frame, NULL, &gc->char_frame_rect);
  //fr_x = fr_x+128;
  //gc->char_frame_rect = fast_rect(fr_x, fr_y, cr_w, cr_h );
  //SDL_RenderCopy(gc->renderer, gc->char_frame, NULL, &gc->char_frame_rect);
  //fr_x = fr_x+128;
  //gc->char_frame_rect = fast_rect(fr_x, fr_y, cr_w, cr_h );
  //SDL_RenderCopy(gc->renderer, gc->char_frame, NULL, &gc->char_frame_rect); 
  //fr_x = fr_x+128;
  //gc->char_frame_rect = fast_rect(fr_x, fr_y, cr_w, cr_h );
  //SDL_RenderCopy(gc->renderer, gc->char_frame, NULL, &gc->char_frame_rect);
}
void draw_mapport(GameCore *gc)
{
  int x,y,i, screen_fract;
  int fr_x, fr_y; //, cr_w, cr_h;
  int location_x, location_y;
  screen_fract = gc->screen_size_x / 38;
  SDL_Rect amap_tiles[52]; //how many tiles is V---loop*loop
  i=0;
  //SDL_RenderCopy(gc->renderer, gc->automap_frame, NULL, &gc->automap_frame_rect);//&gc->tabbed_pane); 
  for(y=0; y < 7; y++) { //vertical loop
    for(x=0; x < 7; x++) { //horizantal loop
      fr_x = gc->tabbed_pane.x + 1+(x * screen_fract); //set start x
      fr_y = gc->tabbed_pane.y + 1 + (y * screen_fract); //set start y
      amap_tiles[i] = fast_rect( fr_x, fr_y, screen_fract -1, screen_fract -1);
      location_x = gc->player->map_x -4+x;
      location_y = gc->player->map_y -4+y;
      set_map_tile_color(gc, location_x, location_y, x, y); //set thecolor 
      SDL_RenderFillRect(gc->renderer, &amap_tiles[i]); //render it
      //render something here.
      SDL_RenderCopy(gc->renderer, NULL, NULL, &amap_tiles[i]);
      i++;
    }
  }
  SDL_SetRenderDrawColor(gc->renderer, 0,0,0,0);
  set_color(gc, 255, 255, 255);
}
SDL_Rect fast_rect(int x, int y, int w, int h)
{
  SDL_Rect r;
  r.x = x; r.y = y; r.w=w; r.h=h;
  return r;			   
}
void fast_button(GameCore *gc, int x, int y, char *text)
{
  SDL_Rect r; //, tr;
  r = fast_rect(x, y, 283,55);
  //if x,y colliding with gc->mouse_x, and gc->mouse_y
  if(gc->mouse_x >= x && gc->mouse_x <= x+283 && gc->mouse_y >= y && gc->mouse_y <= y+55) {
    SDL_RenderCopy(gc->renderer, gc->t_buttons, &gc->button_highlighted, &r);
  }
  else {
    SDL_RenderCopy(gc->renderer, gc->t_buttons, &gc->button_raised, &r);
  }
  sdl_set_textpos(gc, x+50, y+15); set_color(gc, 255, 255, 255);
  SDL_RenderCopy(gc->renderer, sdl_printf_font(gc, gc->font0, text), NULL, gc->c_text_size);
}
void fast_radio(GameCore *gc, int x, int y, char *text, int selected) //does not uncheck?
{//18,14,40,40...54,14,40,40
  SDL_Rect r; //, tr;
  r = fast_rect(x, y, 30,30);
  if(selected == 0) {
    SDL_RenderCopy(gc->renderer, gc->t_buttons, &gc->radio_raised, &r);
  }
  else if(selected == 1) {
    SDL_RenderCopy(gc->renderer, gc->t_buttons, &gc->radio_pressed, &r);
  }
  sdl_set_textpos(gc, x+36, y); set_color(gc, 255, 255, 255);
  SDL_RenderCopy(gc->renderer, sdl_printf_font(gc, gc->font0, text), NULL, gc->c_text_size);
}
void draw_game_menu(GameCore *gc)
{
  int button_row, button_col; //, button_col1_to;
  button_row = 150;//+55
  button_col = 15;//
  SDL_RenderCopy(gc->renderer, gc->w_background, NULL, NULL); //put background
  //draw_background_texture(gc, gc->w_background);//SDLTexture *t
  
  //gl_draw_game_menu(gc);
  fast_button(gc, button_col,button_row,      "New Game");
  fast_button(gc, button_col,button_row+55*1, "Load Game");
  fast_button(gc, button_col,button_row+55*2, "Save Game");
  fast_button(gc, button_col,button_row+55*3, "Options");
  fast_button(gc, button_col,button_row+55*4, "Exit");
  //display_render(gc);
}



void resize_screen(GameCore *gc, int size_x, int size_y)
{ //doesn't work yet, must reload the textures.
  SDL_Rect vp;
  vp.x=0;
  vp.y=0;
  vp.w = size_x;
  vp.h = size_y;
  SDL_DestroyRenderer(gc->renderer);
  SDL_SetWindowSize(gc->win, size_x, size_y);
  SDL_SetWindowFullscreen(gc->win, SDL_WINDOW_FULLSCREEN);
  gc->renderer =
    SDL_CreateRenderer(gc->win, -1,
		       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (gc->renderer == NULL){
    printf("%s \n", SDL_GetError() );
  }
}
