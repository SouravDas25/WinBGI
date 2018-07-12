

#ifndef ADSDATAREPLICATOR_H
#define ADSDATAREPLICATOR_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include <time.h>
#include<stdbool.h>

#include "Error.h"
#include "gc.h"
#include "object.h"

#define INBUILTCMP (int(*)(void*,void*))-1
#define COPYPDT (void*(*)(void*))-1
#define FREEPDT myfree

#define copyctype COPYPDT
#define freectype FREEPDT

/*takes the address and size of a variable and return a dynamically allocated copy of it.*/
void* copy(void * b,int size); 

/* make a copy of the datatype provided if datatype is ADS then it calls copyconstructor else copy function .*/
void* approprite_copy(int isads ,void*value,int datatype); 

/*frees memory occupied by objects if ADS type then calls destructor.*/ 
void appropriate_delete(int isads,void*value) ;

void* evaluate_pointer(int isads,void**value) ;

#endif
