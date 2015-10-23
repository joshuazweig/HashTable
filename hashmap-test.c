#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  struct HashMap *map = constructor(10);
  set("A Key", "Arb Value", map);
  set("Another Key", "More data", map);
  set("A Third Key", "Some Data", map);

  printf("The hashmap currently looks like this:\n");
  printL(map);
  printf("\n");
  set("A Key", "Random Data", map); //Test Collision Resolution

  printf("The hashmap currently looks like this:\n");
  printL(map);
  printf("\n");

  char* s0 = (char*) get("A Key", map); //if you actuallly want to print the data cast to char * and print
  char* s1 = (char*) get("A Third Key", map);

  printf("Data 1: %s Data 2: %s\n", s0, s1);
  printf("\n");

  char* s2 = (char*) delete("firstKeys", map);
  printf("%s\n", s2);
  printf("\n");

  printf("The hashmap currently looks like this:\n");
  printL(map);

  printf("Load Factor Test: %f\n\n\n", load(map));

  printf("Test functions on full hashmap strucutre\n");
  set("one", "Arb Value", map);
  set("two", "More data", map);
  set("three", "Some Data", map);  
  set("four", "Arb Value", map);
  set("five", "More data", map);
  set("six", "Some Data", map);  
  set("seven", "Arb Value", map);
  set("eight", "More data", map);
  set("nine", "Some Data", map);

  printf("The hashmap currently looks like this:\n");
  printL(map);

  hashFree(map);

  return 0;
}
