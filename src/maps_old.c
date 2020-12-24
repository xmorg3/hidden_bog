#define JSMN_HEADER
#include "jsmn.h"  //parse the new jasn format

static const char *JSON_STRING =
  "{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
    "\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

typedef struct {
  jsmntype_t type; /* Token type */
  int start;       /* Token start position */
  int end;         /* Token end position */
  int size;        /* Number of child (nested) tokens */
} jsmntok_t;




//reads the old OSARE/flare map format
void read_map_file(PlayMap *m, const char *filename)
{
  FILE *f;
  long lSize;
  //int count, end, state;
  char *data;
  char *tempstr;
  size_t result;
  int x, y, i; //loop through reading the map
  
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
  //find width
  //printf("----freaded, now parsing map, %s--------\n",filename);
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

  //finding exits -> exit=1,1,map.txt\n
  i=0;
  for(i=0; i<7; i++) {
    tempstr = strtok( strstr(data, "exit"), ",=\n" );
    tempstr = strtok( NULL, ",=\n" ); //=
    //atoi x,y
    //assign mapname to exit to be loaded later.
  }
  //fclose(f);
  printf("finished reading file\n");
  free(data);
  //return m;
}//end void read_map_file



void read_map_file_json(PlayMap *m, const char *filename)
{
  FILE *f;
  long lSize;
  //int count, end, state;
  char *data;
  char *tempstr;
  size_t result;
  //read open and read files contents
  f = fopen(filename, "rb");
  if(f == NULL) { fputs("FileNotFound error",stderr); exit (1); } //error if file not found
  fseek(f , 0 , SEEK_END); //look through file
  lSize = ftell(f);//get file size
  rewind(f);//return to beginning
  data = (char*) malloc (sizeof(char)*lSize); //allocate memory
  if (data == NULL){fputs ("Memory error",stderr); exit (2);}
  result = fread (data,1,lSize,f); // copy the file into the buffer:
  if (result != lSize){fputs ("Reading error",stderr); exit (3);}
  fclose(f);
  //file is closed, data copied to buffer "data"

  jsmntok_t tokens[256];
  const char *js;
  int r;

  r = jsmn_parse(&parser, data, strlen(data), tokens, 256);
  //now you have tokens(265)
  
  jsmn_parser parser; //https://zserge.com/jsmn/
  jsmn_init(&parser);
}
