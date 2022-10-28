#include <SDL.h>

#include "game.h"

void draw(GameCore *gc, SDL_Texture *t, const SDL_Rect *size);
SDL_Rect fast_rect(int x, int y, int w, int h);

void draw_playport_north(GameCore *gc);
void draw_playport_east(GameCore *gc);
void draw_playport_south(GameCore *gc);
void draw_playport_west(GameCore *gc);

void draw_fov2(GameCore *gc, int left, int middle, int right);
void draw_fov1(GameCore *gc, int left, int middle, int right);
void draw_fov0(GameCore *gc, int left, int middle, int right);

void drawto_frame(GameCore *gc, SDL_Texture* img, const SDL_Rect* dstrect);
void drawto_viewport(GameCore *gc, SDL_Texture *img);
SDL_Texture * get_texture_by_objectid(GameCore *gc, int textureid);

void draw_oov0(GameCore *gc, int left, int middle, int right);
void draw_oov1(GameCore *gc, int left, int middle, int right);

//legend moved to game.h
//#define WOOD_WALL  1
//#define STONE_WALL 2
//#define GREEN_TREE 5

void draw_playport_north(GameCore *gc)
{  //int current_tile; //set value to whatever tile we are rendering.
  if(gc->player->map_y-2 > 0)
    draw_fov2(gc, gc->current_map->background_layer[gc->player->map_y-2][gc->player->map_x-1],
	      gc->current_map->background_layer[    gc->player->map_y-2][gc->player->map_x],
	      gc->current_map->background_layer[    gc->player->map_y-2][gc->player->map_x+1]);  if(gc->player->map_y-1 > 0)
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
{  //int current_tile; //set value to whatever tile we are rendering.
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
{  //int current_tile; //set value to whatever tile we are rendering.
  int ms = gc->mapsize;
  int mapy = gc->player->map_y;
  //if(mapy +2 > ms)
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
  int ms=gc->mapsize;
  int mapx = gc->player->map_x;
  if(mapx -2 > 0)
    draw_fov2(gc, gc->current_map->background_layer[gc->player->map_y+1][gc->player->map_x-2],
	      gc->current_map->background_layer[ gc->player->map_y][gc->player->map_x-2],
	      gc->current_map->background_layer[ gc->player->map_y-1][gc->player->map_x-2]);
  
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

// -- 

void draw_fov2(GameCore *gc, int left, int middle, int right)
{//gc->wall_all
  SDL_Rect left_wall, right_wall, middle_wall;
  left_wall = fast_rect(618, 0, 118, 273);
  right_wall = fast_rect(0, 0, 118, 273);
  middle_wall = fast_rect(115, 0, 505,273);
  if( left == WOOD_WALL) { drawto_viewport(gc, gc->wall_left_fov2_blank);  }
  if ( left == STONE_WALL ) { drawto_viewport(gc, gc->tall_wall_left_fov2); }
  if( left == 4) {  drawto_viewport(gc, gc->wall_left_fov2_blank);
    drawto_viewport(gc, gc->door_left_fov2_blank);
  }
  if( right == WOOD_WALL) { drawto_viewport(gc,gc->wall_right_fov2_blank);}
  if( right == STONE_WALL) { drawto_viewport(gc,gc->tall_wall_right_fov2);}
  if( right == 4) { drawto_viewport(gc,gc->wall_right_fov2_blank);
    drawto_viewport(gc,gc->door_right_fov2_blank);
  }
  
  if( middle== WOOD_WALL) {drawto_viewport(gc,gc->wall_front_fov1_blank);}
  if( middle== STONE_WALL) {drawto_viewport(gc,gc->tall_wall_front_fov1);}
  if( middle==4) {drawto_viewport(gc,gc->wall_front_fov1_blank);
    drawto_viewport(gc,gc->door_front_fov1_blank);
  }
}
void draw_fov1(GameCore *gc, int left, int middle, int right)
{
  SDL_Rect left_wall, right_wall, middle_wall;
  left_wall = fast_rect(618, 0, 118, 273);
  right_wall = fast_rect(0, 0, 118, 273);
  middle_wall = fast_rect(115, 0, 505,273);
  if( left==WOOD_WALL )  { drawto_viewport(gc, gc->wall_left_fov1_blank); }
  if( left ==STONE_WALL)  { drawto_viewport(gc, gc->tall_wall_left_fov1);  }
  if( left == 4)  { drawto_viewport(gc,gc->wall_left_fov1_blank);
    drawto_viewport(gc, gc->door_left_fov1_blank);
  }
  if( right ==WOOD_WALL) { drawto_viewport(gc,gc->wall_right_fov1_blank);}
  if( right ==STONE_WALL) { drawto_viewport(gc,gc->tall_wall_right_fov1); } 
  if( right == 4)  { drawto_viewport(gc,gc->wall_right_fov1_blank);
    drawto_viewport(gc,gc->door_right_fov1_blank);
  }
  if( middle==WOOD_WALL)  { drawto_viewport(gc, gc->wall_front_fov0_blank); }
  if( middle ==STONE_WALL)  {drawto_viewport(gc, gc->tall_wall_front_fov0);  }
  if( middle == 4)  { drawto_viewport(gc, gc->wall_front_fov0_blank);
    drawto_viewport(gc, gc->door_front_fov0_blank);
  }
}
//field of view, 0
void draw_fov0(GameCore *gc, int left, int middle, int right)
{
  SDL_Rect left_wall, right_wall, middle_wall;
  //SDL_Rect drect;
  left_wall = fast_rect(618, 0, 118, 273);
  right_wall = fast_rect(0, 0, 118, 273);
  middle_wall = fast_rect(115, 0, 505,273);
  // ------------------------------------->walls
  if( left==WOOD_WALL)  { drawto_viewport(gc, gc->wall_left_fov0_blank);  }
  if( left ==STONE_WALL)  { drawto_viewport(gc, gc->tall_wall_left_fov0);  }
  if( left == 4)  { drawto_viewport(gc, gc->wall_left_fov0_blank);
    drawto_viewport(gc, gc->door_left_fov0_blank);
  }
  if( right==WOOD_WALL  ) { drawto_viewport(gc, gc->wall_right_fov0_blank); }
  if( right ==STONE_WALL ) { drawto_viewport(gc, gc->tall_wall_right_fov0);  }
  if( right == 4)  {
    drawto_viewport(gc, gc->wall_right_fov0_blank);
    drawto_viewport(gc, gc->door_right_fov0_blank);
  }
  if( middle==WOOD_WALL)  { //middle wall
    drawto_viewport(gc, gc->wall_front_fov0_blank);
  }
  if( middle ==STONE_WALL)  { //middle wall
    drawto_viewport(gc, gc->tall_wall_front_fov0);
  } 
  if( middle == 4)  {
    drawto_viewport(gc, gc->wall_front_fov0_blank);
    drawto_viewport(gc, gc->door_front_fov0_blank);
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
    draw(gc, get_texture_by_objectid(gc,left), &gc->vp0_object_left);
  }
  if( right >=1000 ) {
    draw(gc, get_texture_by_objectid(gc,right),&gc->vp0_object_right);
    //SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,right), NULL,&gc->vp0_object_right);//, &gc->player_viewport);
  }
  if(middle >= 1000) { //its an object
    draw(gc, get_texture_by_objectid(gc,middle), &gc->player_viewport);
    //SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,middle), NULL, &gc->player_viewport); //NOTE! make them as big as the viewport!
  }
}

void draw_oov1(GameCore *gc, int left, int middle, int right) //drop objects in view
{
  if( left >=1000 ) {
    draw(gc, get_texture_by_objectid(gc,left), &gc->vp1_object_left);
    //SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,left), NULL, &gc->vp1_object_left);//, &gc->player_viewport);
  }
  if( right >=1000 ) {
    draw(gc, get_texture_by_objectid(gc,right),&gc->vp1_object_right);
    //SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,right), NULL,&gc->vp1_object_right);//, &gc->player_viewport);
  }
  if(middle >= 1000) { //its an object
    draw(gc,  get_texture_by_objectid(gc,middle), &gc->vp1_object_middle);
    //SDL_RenderCopy(gc->renderer, get_texture_by_objectid(gc,middle), NULL, &gc->vp1_object_middle); //NOTE! make them as big as the viewport!
  } //vp0_object_left, vp0_object_right, 
  
}
