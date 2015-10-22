#include "hashmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  printf("Sanity Check\n");
  struct HashMap *map = constructor(10);
  int success = set("firstKey", "val", map);

  printf("%u\n", success);

  return 0;
}