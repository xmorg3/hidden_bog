#include <SDL2/SDL.h>
#include "game.h"

/*
typedef struct _Scene { //Scene structure.
  char name[75]; //name of place
  int **tiles; //tiles!unsigned short
} Scene;
*/
//0 ground, 1 wall, 2 tall wall, 3 door
//4 archway, 5 water, 6 hole(void?)

PlayMap * new_map(char *name, int mapsize, char *filename ); //create the scene (map)
void read_map_file(PlayMap *m, const char *filename); //maps.c
void on_load_new_scene(GameCore *gc, PlayMap *m, char *scne_type); //what happens whne you load a new scene
void load_wall_textures(GameCore *gc, char *scene_type);

int test_map[20][20] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
  {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
  {1,2,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,2,1},
  {1,2,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,2,1},
  {1,2,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
  {1,2,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,2,1},
  {1,2,0,1,1,1,0,0,0,0,1,3,1,0,1,1,0,0,2,1},
  {1,2,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,2,1},
  {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
  {1,2,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,0,2,1},
  {1,2,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,0,2,1},
  {1,2,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,0,2,1},
  {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
  {1,2,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,2,1},
  {1,2,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,2,1},
  {1,2,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,2,1},
  {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
  {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int test_fog[20][20] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

PlayMap * new_map(char *name, int mapsize, char *filename)
{ //creates a new scene
  int i, j;
  PlayMap *current_map;
  current_map = (PlayMap*)malloc(sizeof (PlayMap)); //allocate teh current map
  strcpy(current_map->map_title, name); //name of map
  current_map->background_layer = (int**)malloc(mapsize * sizeof(int*)); //backgroun layer(osare)
  current_map->object_layer = (int**)malloc(mapsize * sizeof(int*)); //objects(like treasure chests?)
  current_map->collision_layer = (int**)malloc(mapsize * sizeof(int*)); //walls?
  current_map->fog_layer = (int**)malloc(mapsize * sizeof(int*)); //automapping
  for(i=0; i < mapsize; i++) { //allocating for the rows
	current_map->background_layer[i] = (int*) malloc(mapsize * sizeof(int));
	current_map->object_layer[i] = (int*) malloc(mapsize * sizeof(int));
	current_map->collision_layer[i] = (int*) malloc(mapsize * sizeof(int));
	current_map->fog_layer[i] = (int*) malloc(mapsize * sizeof(int));
  }
  if(filename != NULL){
	  read_map_file(current_map, filename);
  }
return current_map;
}


void on_load_new_scene(GameCore *gc, PlayMap *m, char *scene_type)
{
  load_map_wall_textures(gc, scene_type);
}
