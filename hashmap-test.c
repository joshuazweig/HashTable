#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  struct HashMap *map = constructor(10);
  set("firstKeys", "val", map);
  set("SecondgdgfdgKey", "other string", map);
  set("firstKeys", "val 2", map);

  int s0 = get("firstKeys", map);
  int s1 = get("nope", map);

  printf("%u   %u\n", s0, s1);

  //printL(map);

  return 0;
}
