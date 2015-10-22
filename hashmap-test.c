#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  struct HashMap *map = constructor(10);
  set("firstKey", "val", map);
  set("firstKey", "val 2", map);
  set("SecondKey", "other string", map);

  printL(map);

  return 0;
}