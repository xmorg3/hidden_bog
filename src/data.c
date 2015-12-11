//#include <stdio.h>
//void get_index_from_csv(char *data, char *filename, int index);
//void get_index_from_csv(char *data, char *filename, int index)
//{//}

#include "game.h"
#include <sqlite3.h>
#include <stdio.h>

//int sqlite3_exec(
//  sqlite3*,                                  /* An open database */
//  const char *sql,                           /* SQL to be evaluated */
//  int (*callback)(void*,int,char**,char**),  /* Callback function */
//  void *,                                    /* 1st argument to callback */
//  char **errmsg                              /* Error msg written here */
//);
int load_data_from_db(GameCore *gc);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
static int cb_get_npc(void *NotUsed, int argc, char **argv, char **azColName)
{ //load all into ?
  int i;
  Actor *a;
  //1000	a pirate	female	8	8	fpirate_01.png	pirate	1	0	1	1	saber	pirate	female_pirate
  a = (Actor *)malloc(sizeof(Actor *argc); //allocate the npc's
  for(i=0; i<argc; i++){
    a->npc_map_id = atoi(argv[i][1]); printf("testing load %s", a->npc_map_id);
  }
  
  return 0;
}
static int cb_get_item(void *NotUsed, int argc, char **argv, char **azColName)
{
  return 0;
}

int load_data_from_db(GameCore *gc)
{
  sqlite3 *db;
  int result_code;
  char *zErrMsg = 0;
  
  result_code = sqlite3_open("data/gamedata.db", &db);
  if( result_code ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  result_code = sqlite3_exec(db, "select * from npc;", cb_get_npc, 0, &zErrMsg);
  result_code = sqlite3_exec(db, "select * from item;", cb_get_item, 0, &zErrMsg);

  sqlite3_close(db);
  return 0;
}
