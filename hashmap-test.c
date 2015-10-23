#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  struct HashMap *map = constructor(10);
  set("firstKeys", "val", map);
  set("SecondgdgfdgKey", "other string", map);
  set("firstKeys", "val 2", map);

  char* s0 = (char*) get("firstKeys", map); //if you actuallly want to print the data cast to char * and print
  char* s1 = (char*) get("nope", map);

  printf("%s   %s\n", s0, s1);

  char* s2 = (char*) delete("firstKeys", map);
  printf("%s\n", s2);
  printL(map);

  return 0;
}
