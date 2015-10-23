#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h> //I know you said no libs, but for C these two are somewhat necessary
#include <string.h> //same for string...

//Since C is not an object oriented, I require a parameter 
//for the methods in the spec that passes in the pointer to a hashmap for the 
//functions to act on
//Sorry I had to go beyond the parameter list defined by the spec, but I think that
//this is the best practice for solving the question in C.

//Fixed size means I should open address! 

//Helpers
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
//Returns a pointer to the pointer that points to the element at position 0 in the hashmap
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
