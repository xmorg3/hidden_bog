//#include <stdio.h>
//void get_index_from_csv(char *data, char *filename, int index);
//void get_index_from_csv(char *data, char *filename, int index)
//{//}

#include "game.h"
#include <sqlite3.h>

//int sqlite3_exec(
//  sqlite3*,                                  /* An open database */
//  const char *sql,                           /* SQL to be evaluated */
//  int (*callback)(void*,int,char**,char**),  /* Callback function */
//  void *,                                    /* 1st argument to callback */
//  char **errmsg                              /* Error msg written here */
//);
int load_data_from_db(GameCore *gc);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  return 0;
}

int load_data_from_db(GameCore *gc)
{
  sqlite3 *db;
  int result_code;
  char *zErrMsg = 0;
  
  result_code = sqlite3_open("gamedata.db", &db);
  if( result_code ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  result_code = sqlite3_exec(db, "somesql", callback, 0, &zErrMsg);

  sqlite3_close(db);
  return 0;
}
