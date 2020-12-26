#include "game.h"
#include <string.h>

//void handle_keydown(GameCore *gc);
//void handle_mousebutton_down(GameCore *gc);
int update(GameCore *gc);
void set_player_direction(GameCore *gc, int mod);
void set_player_move_foreward(GameCore *gc);
void set_player_move_backward(GameCore *gc);
void print_in_messagebox(GameCore *gc, char *text);
void print_debug_map(GameCore *gc); //update.c
int get_movable(int tile); //update.c get movable tile 0 cant move 1 can move

int update(GameCore *gc)
{ //basic game updater code
  //Poll for SDL_Event's
  SDL_GetMouseState(&gc->mouse_x, &gc->mouse_y);
  return gc->game_state;
}


void print_in_messagebox(GameCore *gc, char *text)
{
  //print a message in the top of the messagebox, and shifts the previous text down. if max is reached shift out.
  strcpy(gc->messagelist[6], gc->messagelist[5]);
  strcpy(gc->messagelist[5], gc->messagelist[4]);
  strcpy(gc->messagelist[4], gc->messagelist[3]);
  strcpy(gc->messagelist[3], gc->messagelist[2]);
  strcpy(gc->messagelist[2], gc->messagelist[1]);
  strcpy(gc->messagelist[1], gc->messagelist[0]);
  strcpy(gc->messagelist[0], text);
}
int get_moveable(int tile) // 0 cant move, 1 can move
{
  if(tile == GRASS) {
    return 1;
  }
  else {
    return 0;
  }
}
void print_debug_map(GameCore *gc)
{
  int x,y;
  static int player_moves = 0;

  player_moves++;
  printf("player at x: %d y: %d move: %d\n", gc->player->map_x, gc->player->map_y, player_moves);
  //for(y = gc->player->map_y-3; y < gc->player->map_y+3; y++) {
  //  for(x = gc->player->map_x-3; x < gc->player->map_x+3; x++) {
  for(y = 0; y < gc->current_map->height; y++) {
    for(x=0; x < gc->current_map->width; x++) {
      if(y== gc->player->map_y && x == gc->player->map_x){
	printf("@");
      }
      else {
	if(y >= 0 && x >= 0 && y < gc->mapsize && x < gc->mapsize) {
	  printf("%d", gc->current_map->background_layer[y][x]);
	}
      }
    }printf("\n");
  }printf("\n");
}

void set_player_direction(GameCore *gc, int mod)
{ //NORTH,  EAST,  SOUTH,  WEST
  gc->player->direction += mod;
  if(gc->player->direction < NORTH) {
    gc->player->direction = WEST;
    print_in_messagebox(gc, "You have turned west");
  }
  if(gc->player->direction > WEST) {
    gc->player->direction = NORTH;
    print_in_messagebox(gc, "You have turned north");
  }
  print_debug_map(gc);
}
void set_player_move_foreward(GameCore *gc) //update.c
{//if location = n,  current_map[y-1][x] //prevent outof bound loops
  //int x,y;
  if(gc->player->direction == NORTH && gc->player->map_y > 2) { 
    if( get_moveable(gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x] ) == 1) {  
	gc->player->map_y--;
	gc->current_map->fog_layer[gc->player->map_y-1][gc->player->map_x] = 1;
	gc->current_map->fog_layer[gc->player->map_y-1][gc->player->map_x+1] = 1;
	gc->current_map->fog_layer[gc->player->map_y-1][gc->player->map_x-1] = 1;
	if( (gc->player->map_y -2) > 0 )
	  gc->current_map->fog_layer[gc->player->map_y-2][gc->player->map_x] = 1;
      }
      else if (gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x] == 4) { //4=door
      	//move north through door //change zone? if its a zone change, interior to exterior?
      }
    
  }
  if(gc->player->direction == EAST && gc->player->map_x < gc->mapsize -2) {
    if( get_moveable( gc->current_map->background_layer[gc->player->map_y][gc->player->map_x+1] ) == 1)
      {
	gc->player->map_x++;
	gc->current_map->fog_layer[gc->player->map_y][gc->player->map_x+1] = 1;
	gc->current_map->fog_layer[gc->player->map_y-1][gc->player->map_x+1] = 1;
	gc->current_map->fog_layer[gc->player->map_y+1][gc->player->map_x+1] = 1;
	if( (gc->player->map_x +2) < gc->mapsize )
	  gc->current_map->fog_layer[gc->player->map_y][gc->player->map_x+2] = 1;
      }
  }
  if(gc->player->direction == SOUTH && gc->player->map_y < gc->mapsize -2) { 
    if(get_moveable(gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x] ) == 1)
      {
	gc->player->map_y++;
	gc->current_map->fog_layer[gc->player->map_y+1][gc->player->map_x] = 1;
	gc->current_map->fog_layer[gc->player->map_y+1][gc->player->map_x+1] = 1;
	gc->current_map->fog_layer[gc->player->map_y+1][gc->player->map_x-1] = 1;
	if( (gc->player->map_y +2) < gc->mapsize )
	  gc->current_map->fog_layer[gc->player->map_y+2][gc->player->map_x] = 1;
	
      }
  }
  if(gc->player->direction == WEST && gc->player->map_x > 2) {
    if( get_moveable(gc->current_map->background_layer[gc->player->map_y][gc->player->map_x-1]) == 1)
      {
	gc->player->map_x--;
	gc->current_map->fog_layer[gc->player->map_y][gc->player->map_x-1] = 1;
	gc->current_map->fog_layer[gc->player->map_y-1][gc->player->map_x-1] = 1;
	gc->current_map->fog_layer[gc->player->map_y+1][gc->player->map_x-1] = 1;
	if( (gc->player->map_x -2 ) > 0 )
	  gc->current_map->fog_layer[gc->player->map_y][gc->player->map_x-2] = 1;
      }
  }
  print_debug_map(gc);
}
void set_player_move_backward(GameCore *gc) //update.c                                                                                                                  
{
  if(gc->player->direction == NORTH) {
    if(get_moveable(gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x]) == 1)
    gc->player->map_y++;
  }
  if(gc->player->direction == EAST) { 
    if(get_moveable(gc->current_map->background_layer[gc->player->map_y][gc->player->map_x-1]) == 1)
    gc->player->map_x--;
  }
  if(gc->player->direction == SOUTH) {
    if(get_moveable(gc->current_map->background_layer[gc->player->map_y-1][gc->player->map_x]) == 1)
    gc->player->map_y--;
  }
  if(gc->player->direction == WEST) {
    if(get_moveable(gc->current_map->background_layer[gc->player->map_y][gc->player->map_x+1]) == 1)
    gc->player->map_x++;
  } 
  print_debug_map(gc);
}

