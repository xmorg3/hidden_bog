
#include <sqlite3.h>

int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  
}
