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

PlayMap * new_map(char *name, int mapsize, char *filename );
void read_map_file(PlayMap *m, const char *filename); //maps.c

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
  current_map = (PlayMap*)malloc(sizeof (PlayMap));
  strcpy(current_map->map_title, name);

  //gc->playmap->background_layer =  (int *)malloc(sizeof(int) * (100 * 100));        //with preallocating

  current_map->background_layer = (int**)malloc(mapsize * sizeof(int*));
  current_map->object_layer = (int**)malloc(mapsize * sizeof(int*));
  current_map->collision_layer = (int**)malloc(mapsize * sizeof(int*));
  current_map->fog_layer = (int**)malloc(mapsize * sizeof(int*));
  //current_map->background_layer = (int *)malloc(sizeof(int) * (mapsize*mapsize));
  //current_map->object_layer = (int *)malloc(sizeof(int) * (mapsize*mapsize));
  //current_map->collision_layer = (int *)malloc(sizeof(int) * (mapsize*mapsize));
  //current_map->fog_layer = (int *)malloc(sizeof(int) * (mapsize*mapsize));
  for(i=0; i < mapsize; i++) { //allocating for the rows
	current_map->background_layer[i] = (int*) malloc(mapsize * sizeof(int));
	current_map->object_layer[i] = (int*) malloc(mapsize * sizeof(int));
	current_map->collision_layer[i] = (int*) malloc(mapsize * sizeof(int));
	current_map->fog_layer[i] = (int*) malloc(mapsize * sizeof(int));
  }

  if(filename != NULL){
	  read_map_file(current_map, filename);
  }
  //loading the "test map"
  //for(j = 0; j < mapsize; j++) {
  //	  for(i = 0; i < mapsize; i++) {
  //	  scn->background_layer[j][i] = test_map[j][i];
  //  scn->fog_layer[j][i] = test_fog[j][i];
  //}
  //}
return current_map;
}

