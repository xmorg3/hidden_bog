#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"

//#include "maps.h"


void read_map_file(PlayMap *m,  const char *filename); 
//char * lookup_value(char *data, char * tag);
void free_playmap(PlayMap *m);
void write_map_file(char *mapname, char **mapchars, int height, int width, const char *fn);
void world_gen(SDL_Surface *s, int catlevel, int templevel, int evlevel);
int game_load_scene(GameCore *gc);
/*
typedef struct _OsareMap {
  int width;
  int height;
  int tilewidth;
  int tileheight;
  int location[3]; //
  char *music;
  char *tileset;
  char *map_title;
  //ignore tilesets for now :p
  unsigned int *background_layer;
  unsigned int *object_layer;
  unsigned int *collision_layer;
} OsareMap;
 */
/*char *lookup_value(char *data, char * tag)
{
  char *new_str;
  new_str = strstr(data, tag);
}*/

void read_data_file(GameCore *gc, void *table, const char *filename) //read a data file into a struct 
{
  FILE *f;  long lSize;
  int count, end, state;
  char *data,*tempstr;
  size_t result;
  int x, y, i; //loop through reading the map
  
  f = fopen(filename , "rb" ); //Open the file
  if(f == NULL) { fputs("FileNotFound error",stderr); exit (1); }
  fseek(f, 0, SEEK_END);
  lSize = ftell(f);
  rewind(f);
  data = (char*) malloc (sizeof(char)*lSize);
  if (data == NULL) 
    {fputs ("Memory error",stderr); exit (2);}
  result = fread (data,1,lSize,f); // copy the file into the buffer:
}

void read_map_file(PlayMap *m, const char *filename) 
{
  FILE *f;
  long lSize;
  int count, end, state;
  char *data;
  char *tempstr;
  size_t result;
  int x, y, i; //loop through reading the map
  
  f = fopen(filename , "rb" ); //Open the file
  if(f == NULL) { fputs("FileNotFound error",stderr); exit (1); }
  fseek(f , 0 , SEEK_END);
  lSize = ftell(f);
  rewind(f);
  data = (char*) malloc (sizeof(char)*lSize);
  if (data == NULL) 
    {fputs ("Memory error",stderr); exit (2);}
  result = fread (data,1,lSize,f); // copy the file into the buffer:
  if (result != lSize) 
    {fputs ("Reading error",stderr); exit (3);}
  fclose(f);
  //find width
  printf("----freaded, now parsing map, %s--------\n",filename);
  strtok(strstr(data,"width"), "=\n"); //text width
  m->width = atoi( strtok( NULL, "=\n")  ); //number width
  printf("Map width is %d, :D\n", m->width);
  strtok(strstr(data,"height"), "=\n"); //find height
  m->height = atoi( strtok(NULL, "=\n"));
  printf("Map height is %d, :D\n", m->height);  //We are OK up to here. (line3)
  for(y = 0; y < m->height; y++) {
    for(x = 0; x < m->width; x++) {
      m->fog_layer[y][x] = 0;
    }
  }  
  tempstr = strtok( strstr(data, "background"), "=" );
  tempstr = strtok( strstr(data, "background"), "=" );
  tempstr = strtok( strstr(data, "background"), "=" );
  tempstr = strtok( strstr(data, "background"), "=" );
  tempstr = strtok( strstr(data, "background"), "=" );
  printf("Looking for background: %s\n", tempstr);
  tempstr = strtok( strstr(data, "data"), "=\n" ); 
  printf("Looking for \"data\": %s\n", tempstr);
  tempstr = strtok( NULL, "=\n" );
  printf("Looking for map %s\n", tempstr);
  i=0;
  for(y = 0; y < m->height; y++) {
    for(x = 0; x < m->width; x++) { //ground layer
      m->background_layer[y][x] = atoi(strtok(NULL, ",\n"));
      i++;
    }
  }
  //Get the next layer(note this layer is with tiles 32x64?
  strtok(NULL, "\n");
  tempstr = strtok( strstr(data, "data"), "=\n" ); 
  printf("Looking for object data: %s\n", tempstr);
  tempstr = strtok( NULL, "=\n" );
  printf("looking for object layer.\n");
  i=0;
  for(y=0; y < m->height; y++) {
    for(x=0; x < m->width; x++) { //object layer.
      m->collision_layer[y][x] = atoi(strtok(NULL, ",\n"));
      printf("%d", m->object_layer[y][x]);
      i++;
    }
  }

  tempstr = strtok( strstr(data, "data"), "=\n" );
  printf("Looking for collision data: %s\n", tempstr);
  tempstr = strtok( NULL, "=\n" );
  printf("looking for collision layer.\n");
  i=0;
  for(y=0; y < m->height; y++) {
    for(x=0; x < m->width; x++) {
      //m->collision_layer[y][x] = 0;
      m->object_layer[y][x] = atoi(strtok(NULL, ",\n"));
      i++;
    }
  }
  //fclose(f);
  printf("finished reading file\n");
  free(data);
  //return m;
}

void free_playmap(PlayMap *m)
{
  free(m->collision_layer);
  free(m->object_layer);
  free(m->background_layer);
  free(m);
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
