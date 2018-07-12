


#ifndef garbagecollector_H
#define garbagecollector_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include<time.h>
#include<stdbool.h>

#include "Error.h"


typedef unsigned int UINT;

/*allocate dynamic memory in a safe way maintaing a stack of occupied element .*/
void* mycalloc(int n,int size);

/*allocate dynamic memory in a safe way maintaing a stack of occupied element .*/
void* mymalloc(UINT size); 

/*prints the occupied stack .*/
void Garbagecheck(); 

/*frees the memory from occupied stack .*/
void myfree(void* a); 

#endif
