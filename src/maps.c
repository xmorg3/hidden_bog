#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"

//#include "maps.h"
//void read_map_file(PlayMap *m,  const char *filename); 
//char * lookup_value(char *data, char * tag);
void free_playmap(PlayMap *m);
void write_map_file(char *mapname, char **mapchars, int height, int width, const char *fn);
void world_gen(SDL_Surface *s, int catlevel, int templevel, int evlevel);
int game_load_scene(GameCore *gc);
void load_exits(GameCore *gc); //parse maps looking for exit tags.
void read_csv_map_file(PlayMap *m, int maplayer, const char *filename);
//scene.c calls read_map_file functions in function PlayMap *new_map
//
//typedef struct _OsareMap {
//  int width;
//  int height;
//  int tilewidth;
//  int tileheight;
//  int location[3]; //
//  char *music;
//  char *tileset;
//  char *map_title;
//  //ignore tilesets for now :p
//  unsigned int *background_layer;
//  unsigned int *object_layer;
//  unsigned int *collision_layer;
//} OsareMap;

//char *lookup_value(char *data, char * tag)
//{
//  char *new_str;
//  new_str = strstr(data, tag);
//}

//reads the CSV map format.  tiled seems to have stopped supporting osar's format so here is the CSV.  CSV files are stored separatly per layer. but *should* be easier to work with. called from loadresources in resources.c
void read_csv_map_file(PlayMap *m, int maplayer, const char *filename)
{
  FILE *f;
  long lSize;
  //int count, end, state;
  char *data;
  char *tempstr;
  size_t result;
  int x, y, i; //loop through reading the map
  printf("filename for map is %s\n", filename);
  printf("size of the map is %d x %d\n", m->width, m->height);
  f = fopen(filename , "rb" ); //Open the file
  if(f == NULL) { fputs("FileNotFound error",stderr); exit (1); } //error if file not found
  fseek(f , 0 , SEEK_END); //look through file
  lSize = ftell(f);//get file size
  rewind(f);//return to beginning
  data = (char*) malloc (sizeof(char)*lSize); //allocate memory
  if (data == NULL){fputs ("Memory error",stderr); exit (2);}
  result = fread (data,1,lSize,f); // copy the file into the buffer:
  if (result != lSize){fputs ("Reading error",stderr); exit (3);}
  fclose(f);
  //int **background_layer; //walls and what you are standing on
  //int **object_layer; //objects, enemies, doors?
  //int **collision_layer; //walls?.
  tempstr = strtok(data, ",\n");
  if(maplayer == 0) { //background layer
    
    //m->background_layer[y][x] = atoi(strtok(data, ",\n")); //first strtok
    for(y=0; y< m->height -1; y++) {
      for(x=0; x< m->width -1; x++) {
	m->background_layer[y][x] = atoi(strtok(NULL, ",\n")); //printf("b %d x %d\n", x, y);
      }
    }
  }
  else if(maplayer == 1) { //object layer
    for(y=0; y< m->height -1; y++) {
      for(x=0; x< m->width -1; x++) {
	m->object_layer[y][x] = atoi(strtok(NULL, ",\n")); //printf("o %d x %d\n", x, y);
      }
    }
  }
  printf("finished reading file\n");
  free(data);
}



void free_playmap(PlayMap *m)
{
  free(m->collision_layer); //free layer
  free(m->object_layer);
  free(m->background_layer);
  free(m); //free map
}

void write_map_file(char *mapname, char **mapchars, int height, int width, const char *fn) {
  FILE *fp;
  int x,y;
  char mappath[100];
  mappath[0] = '\0';
  strcat(mappath, "data/");
  strcat(mappath, fn);
  fp = fopen(mappath, "w+");
  fputs (mapname, fp); fputc('\n', fp);
  for(y = 0; y < height; y++) {
    for(x=0; x< width; x++) {
      fputc(mapchars[y][x], fp);
    }
    fputc('\n', fp);
  }
  fputc('\n', fp); fputc('\n', fp);
  fclose(fp);
}
void world_gen(SDL_Surface *s, int catlevel, int templevel, int evlevel)
{
  int x, y;
  int tcolor, tred, tgreen, tblue;
  SDL_Rect maprect[300][400];
  SDL_LockSurface(s);
  for(y=0; y<300; y++) {
    for(x=0; x<400;x++)	{
      maprect[y][x].w = 2;
      maprect[y][x].h = 2;
      maprect[y][x].x = 2*x;
      maprect[y][x].y = 2*y;
      //seas
      if(x < 100 || x > 300) {
	tred = 0; tgreen = 0; tblue=100;
      }
      else {
	tred = 0; tgreen = 100; tblue = 0;
      }
      tcolor = SDL_MapRGB(s->format, 
			  tred + rand()%25, 
			  tgreen + rand()%25, 
			  tblue + rand()%25);
      SDL_FillRect(s, &maprect[y][x], tcolor);
      //sdlprintf(gc, 25, 25, "World Map"); print later :D
    }
  }
  SDL_UnlockSurface(s);
}
int game_load_scene(GameCore *gc)
{
  return 0;
}



