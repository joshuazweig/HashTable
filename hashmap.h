#ifndef _HASHMAP_H_
#define _HASHMAP_H_

struct Element
{
  char* key;
  void* value;
};

//I'm going to go for a collision mechanism of linear probing. 
//Quadradic probing may reduce clustering, but can also fail so I'll stick with the
//open addressing method of linear probing
//I opt for open addressing over chaining resolution to avoid the additional space 
//requirments of the chaining mechanism 
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
int hash(char *str);

#endif