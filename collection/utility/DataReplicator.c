

#ifndef DATAREPLICATOR_C
#define DATAREPLICATOR_C

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
#include "gc.c"
#include "object.c"

#include "datareplicator.h"

void* copy(void * b,int size) /*takes the address and size of a variable and return a dynamically allocated copy of it*/
{
	void * v;
	if(size == 0)
	{
		MemoryError("Cannot allocate memory with 0 size in copy function");
	}
	if( b == NULL)
	{
		ValueError("Cannot copy a NULL in copy function");
	}
	v = mycalloc(1,size);
	checkMemory(v);
	return memmove(v,b,size);
}

void* approprite_copy(int isads ,void*value,int datatype) /*make a copy of the datatype provided if datatype is 
ADS it calls copyconstructor else copy function */
{
	void * cal ;
	if (isads == 1 )
	{
		cal = Duplicate(value);
	}
	else cal = copy(value,datatype);
	return cal;
}

void appropriate_delete(int isads,void*value) 
{
	if (isads == 1 )
	{
		ads_delete(value);
	}
	else myfree(value);
}

void* evaluate_pointer(int isads,void**value) 
{
	void * val;
	if(isads == 1)
	{
		val = *value;
	}
	else val = (void*)value;
	return val;
}

#endif

