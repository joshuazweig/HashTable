#ifndef _HASHMAP_H_
#define _HASHMAP_H_

struct Element
{
  char* key;
  void* value;
  int deleted;
};

struct HashMap
{
  struct Element** element;
  int size;
};

struct HashMap* constructor(int s);
int set(char* key, void* val, struct HashMap *map);
void* get(char *key, struct HashMap *map);
void* delete(char *key, struct HashMap *map);
float load(struct HashMap *map);
int hashCode(char *str, struct HashMap *map);
void hashFree(struct HashMap* map);
void printL(struct HashMap* map);


#endif