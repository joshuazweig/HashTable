#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  struct HashMap *map = constructor(10);
  set("A Key", "Arb Value", map);
  set("Another Key", "More data", map);
  set("A Third Key", "Some Data", map);

  printL(map);
  printf("\n");
  set("A Key", "Random Data", map); //Test Collision Resolution

  printL(map);
  printf("\n");

  char* s0 = (char*) get("A Key", map); //if you actuallly want to print the data cast to char * and print
  char* s1 = (char*) get("A Third Key", map);

  printf("Data 1: %s Data 2: %s\n", s0, s1);
  printf("\n");

  char* s2 = (char*) delete("firstKeys", map);
  printf("%s\n", s2);
  printf("\n");

  printL(map);

  printf("%f\n", load(map));
  return 0;
}
