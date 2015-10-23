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


//Why I'm implementing a collision resolution strategy of chaining.
//I thought seriously about doing open addressing, but then on delete it would 
//push me towards doing lazy deletion which I do not want to do as it would redicue the number
//of elements that I could hold efficently.
//I opt for the increased space and perhaps O(n) access time to avoid this problem and make
//sure that I can always hold at least the minimum number of elements. 
//A better yet solution would be to do double hashing with chaining.




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
  struct Element* e;
  int i; 
  for(i = 0; i < map->size; i++) 
  {
    //if((map->element) + i == NULL) //fix increments!
    if((*(map->element + i))  == NULL)
    {
      printf("NULL\n");
      continue;
    }
    k = (*(map->element + i))->key; 
    v = (*(map->element + i))->value; 
    e = (*(map->element + i))->next;
    printf("(%s , %s)", k, (char*) v);
    if(e != NULL)
      printf("->(%s , %s)", e->key, (char*) e->value); //you should loop her

    printf("\n");
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

  if(*(map->element + offset) == NULL) //check this
  {
    *(map->element + offset) = e;
    return 1;
  }
  //Otherwise lets chain! 
  struct Element *chain =  *(map->element + offset);
  while(chain->next != NULL)
  {
    chain = chain->next;
  }
  chain->next = e;
  return 0; //i guess we didnt find anything
}

void* get(char *key, struct HashMap *map)
{
  int offset = hashCode(key, map);

  if(*(map->element + offset) == NULL)
    return NULL;
  if(!strcmp((*(map->element + offset))->key, key))
    return (*(map->element + offset))->value;
  
  struct Element *chain =  *(map->element + offset);
  while(chain->next != NULL)
  {
    if(!strcmp(chain->key, key))
      return chain->value;

    chain = chain->next;
  }
  return NULL;
}

void* delete(char *key, struct HashMap *map)
{
  int offset = hashCode(key, map);

  if(*(map->element + offset) == NULL)
    return NULL;
  if(!strcmp((*(map->element + offset))->key, key))
  {
    void* data = (*(map->element + offset))->value;
    *(map->element + offset) = (*(map->element + offset))->next;
    free(*(map->element + offset));
    return data;
  }
  
  struct Element *chain =  *(map->element + offset);
  struct Element *prev;
  while(chain->next != NULL)
  {
    if(!strcmp(chain->key, key))
    {
      void* data = chain->value;
      prev->next = chain->next;
      free(chain);
      return data;
    }
    prev = chain;
    chain = chain->next;
  }
  return NULL;
}


float load(struct HashMap *map)
{
  
}
