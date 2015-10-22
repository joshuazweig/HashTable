#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  struct HashMap *map = constructor(10);
  int success = set("firstKey", "val", map);
  set("firstKey", "val 2", map);
  set("SeconhdfghdfghdK", 0, map);

  printL(map);

  return 0;
}