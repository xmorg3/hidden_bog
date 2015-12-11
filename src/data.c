//#include <stdio.h>
//void get_index_from_csv(char *data, char *filename, int index);
//void get_index_from_csv(char *data, char *filename, int index)
//{//}

#include "game.h"
#include <sqlite3.h>
#include <stdio.h>

#define RECORD_MAX 25

Actor a[RECORD_MAX];

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
{ 
  int i, next_actor;
  //load all into ?
  //CAllback is performed on each row, for lop is not required!!!
  //mapid	name	gender	health	healthmax	image	faction	hitdice	hitbonus	damagedice	damagebonus	weapon	lootlist	talklist
  //0-------1--------2------3-4----5--------------6-----7-8-9-10-11----12------13
  //14------15-------16----17-18---19------------20----21-22-23-24-25--26-----27
  //1000	a pirate	female(i)	8	8	fpirate_01.png	pirate	1	0	1	1	saber	pirate	female_pirate
  for(i=0; i<RECORD_MAX; i++){if(a[i].npc_map_id == -1){next_actor = i;}} //find the next empty space.
  printf("%s|%s|%s", argv[0],argv[1],argv[2]);
  
  a[next_actor].npc_map_id = atoi(argv[0]); 
  strcpy(a[next_actor].name, argv[1]);
  a[next_actor].sex = atoi(argv[2]); 
  a[next_actor].health = atoi(argv[3]);
  a[next_actor].health_max = atoi(argv[4]);
  
  printf("values : %d\n", argc);
  
  return 0;
}
static int cb_get_item(void *NotUsed, int argc, char **argv, char **azColName)
{
  return 0;
}

int load_data_from_db(GameCore *gc)
{
  sqlite3 *db;
  int result_code, actor_count_loop;
  char *zErrMsg = 0;
  for(actor_count_loop=0; actor_count_loop < RECORD_MAX; actor_count_loop++) {a[actor_count_loop].npc_map_id = -1;}
  result_code = sqlite3_open("data/gamedata.db", &db);
  if( result_code ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  result_code = sqlite3_exec(db, "select * from npc;", cb_get_npc, 0, &zErrMsg);
  //result_code = sqlite3_exec(db, "select * from item;", cb_get_item, 0, &zErrMsg);

  sqlite3_close(db);
  return 0;
}
