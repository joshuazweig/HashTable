#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  struct HashMap *map = constructor(10);
  set("firstKeys", "val", map);
  set("SecondgdgfdgKey", "other string", map);
  set("firstKeys", "val 2", map);

  printL(map);

  return 0;
}
