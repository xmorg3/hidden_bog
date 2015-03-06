#include <string.h>
#include "game.h"

Actor * new_actor(char *name);
int mod_actor_stat(Actor *a, char *stat_name, int value);

int mod_actor_stat(Actor *a, char *stat_name, int value)
{
  if(strcmp(stat_name, "strength") == 0)
  {
    a->strength+=value;
  }
}
Actor *new_actor(char *name)
{
  Actor *a;
  a = (Actor *)malloc(sizeof(Actor));
  strcpy(a->name, name);
  a->sex = 1;
  a->health=1;
  a->fatigue=1;
  a->mana=1;
  a->level=1;
  a->experience=0;
  a->c_copper=0;  a->c_silver=0;  a->c_gold=0;
  a->strength=1;
  a->intelligence=1;
  a->agility=1;
  a->wisdom=1;
  a->stamina=1;
  a->charisma=1;
  a->luck=1;
  a->bonus_attr = 10;
  return a;
}

/*
typedef struct _Actor {
  char name[25];
  int sex; //1 male, 0 female
  int health, fatigue, mana;
  int level,
    experience,
    c_copper,   //currency
    c_silver,
    c_gold;
  int strength,
    intelligence,
    agility,
    wisdom,
    stamina,
    charisma,
    luck;
} Actor;

*/
