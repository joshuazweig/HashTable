#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h> //I know you said no libs, but for C these two are somewhat necessary and included in other languages aboce C on the stack
#include <string.h> //same for string...

//Since C is not an object oriented, I require a parameter 
//for the methods in the spec that passes in the pointer to a hashmap for the 
//functions to act on
//Sorry I had to go beyond the parameter list defined by the spec, but I think that
//this is the best practice for solving the question in C.

//////////////////////////Helper Methods/////////////////////

//Hashfunction
//djb2 by Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html
int hashCode(char *str, struct HashMap *map)
{
      int hash = 5381;
      int c;

      while ((c = *str++))
          hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

      if(hash < 0)
        hash *= -1;
      hash %= (map->size);

      return hash;
}

//I grabbed this function from Stack overflow
int isPrime(int n) // assuming n > 1
{
    int i,root;

    if (n%2 == 0 || n%3 == 0)
        return 0;

    root = (int)sqrt(n);

    for (i=5; i<=root; i+=6)
    {
        if (n%i == 0)
           return 0;
    }

    for (i=7; i<=root; i+=6)
    {
        if (n%i == 0)
           return 0;
    }

    return 1;
}

//Returns first prime greater than or equal to n
int nextPrime(int n)
{
  if(isPrime(n))
    return n;

  int nextPrime = n + 1;
  while(!isPrime(nextPrime))
  {
    nextPrime++;
  //  printf("%u \n", nextPrime);
  }
  return nextPrime;
}

//Prints contents of list
void printL(struct HashMap* map)
{
  char* k;
  void* v;
  int i; 
  for(i = 0; i < map->size; i++) 
  {
    //if((map->element) + i == NULL) //fix increments!
    if((*(map->element + i)) == NULL || (*(map->element + i))->deleted == 1)
    {
      printf("NULL\n");
      continue;
    }
    k = (*(map->element + i))->key; 
    v = (*(map->element + i))->value; 
    printf("(%s , %s) \n", k, (char*) v);
  }
}

//I will not free the data pointer because I should not be controlling the lifetime of a data reference
void hashFree(struct HashMap* map)
{
  int i = 0;
  struct Element* e;
  for(i = 0; i < map->size; i++)
  {
    e = *(map->element + i);
    free(e);
  }
  free(map->element);
  free(map);
}
/////////////////////////////////////////////////////////////

/*
* The function is used to construct an instance of a HashTable. 
* Param: integer that is the size of the hash table (max elements that can be held)
* Returns: A pointer to the HashMap struct. 
* This function will terminate the calling program if not enough memory can be allocated for the struct
*/
struct HashMap* constructor(int s)
{
  struct HashMap *map;
  map = (struct HashMap*)malloc(sizeof(struct HashMap));
  if(!map)
    exit(1); //malloc failed
  int size = nextPrime(s);
  map->size = size;

  map->element = (struct Element**)malloc((sizeof(struct Element*) * size) + (sizeof(struct Element) * size));
  //Now the element ** should hold an array of null pointers
  //I can malloc each time I can to the hash val
  return map;
}

/*
* This function will add a key value pair into the HashTable 
* Params: char* key - the key that will be used to index the data
*         void* val - a pointer to any data object reference
          struct *HashMap map - The map for the data to be set into
* return: 1 on success 0 on failure (since C has no bool)
          Failure condition is that the table is full
*/
int set(char* key, void* val, struct HashMap *map)
{
  //Lets find where it is supposed to go
  int offset = hashCode(key, map);
  //printf("%u\n", offset);
  struct Element *e = (struct Element*)malloc(sizeof(struct Element));
  if(!e)
    return 0; //Failure
  
  e->key = key; e->value = val; //Now we have an element, where do we put it?

  if(*(map->element + offset) == NULL || ((*(map->element + offset))->deleted == 1)) //check this
  {
    *(map->element + offset) = e;
    return 1;
  }
  //Otherwise lets open address! 
  int originalOff = offset;
  offset++;
  while(*(map->element + offset) != NULL && ((*(map->element + offset))->deleted != 1))
  {
    if(originalOff == offset) //its full
      return 0;
    offset++;
  }
  *(map->element + offset) = e;
  return 1;
}

/*
* Returns the data pointer associated with a given key
* If two elements have the same key the first one in the table will be returned
* Params: char* key - the key that will be used to index the data
          struct *HashMap map - The map for the data to be retrieved from
* Returns: The data object reference, returns null pointer if the key is
           not mapped to in the table
*/
void* get(char *key, struct HashMap *map)
{
  int offset = hashCode(key, map);

  if(*(map->element + offset) == NULL)
    return NULL;
  if(!strcmp((*(map->element + offset))->key, key) && (*(map->element + offset))->deleted != 1)
    return (*(map->element + offset))->value;
  
  int originalOff = offset;
  offset++;
  while(*(map->element + offset) != NULL)
   {
    if(!strcmp(key,(*(map->element + offset))->key) && ((*(map->element + offset))->deleted != 1))
      return (*(map->element + offset))->value;
    
    offset++;
    if(originalOff == offset)
      return NULL;
  }
  //if(*(map->element + offset) != NULL && ((*(map->element + offset))->deleted != 1) && !strcmp(key,(*(map->element + offset))->key))
   // return (*(map->element + offset))->value;
  return NULL;
}

/*
* Marks the Element referenced by key as deleted
* The element does not actually get deleted in effort to not break the open addressing
* collision resolution strategy
* If two elements have the same key the first one in the table will be deleted
* Params: char* key - the key that will be used to index the data
          struct *HashMap map - The map for the data to be deleted from
* Returns: The data object reference of the deleted element, 
           returns null pointer if the key is not mapped to in the table
*/
void* delete(char *key, struct HashMap *map)
{
  int offset = hashCode(key, map);

 if(*(map->element + offset) == NULL)
    return NULL;
  if(!strcmp((*(map->element + offset))->key, key) && (*(map->element + offset))->deleted != 1)
  {
    (*(map->element + offset))->deleted = 1; //should i change the key to null?
    return (*(map->element + offset))->value;
  }
  int originalOff = offset;
  offset++;
  while(*(map->element + offset) != NULL)
   {
    if(!strcmp(key,(*(map->element + offset))->key) && ((*(map->element + offset))->deleted != 1))
    {
      (*(map->element + offset))->deleted = 1; //should i change the key to null?
      return (*(map->element + offset))->value;
    }
    
    offset++;
    if(originalOff == offset)
      return NULL;
  }
  //if(*(map->element + offset) != NULL && ((*(map->element + offset))->deleted != 1) && !strcmp(key,(*(map->element + offset))->key))
   // return (*(map->element + offset))->value;
  return NULL;
}

/*
* Calculates the load factor of the hashmap by the formula
* # elmenets / max # elements
* Params: Pointer to the struct to find the load factor of
* Returns: float = the load factor of the table
*/
float load(struct HashMap *map)
{
  int i = 0;
  int numFilled = 0;
  for(i = 0; i < map->size; i++)
  {
    if(*(map->element + i) != NULL && (*(map->element + i))->deleted != 1)
      numFilled++;
  }

  return (float)numFilled/(float)map->size;
}
