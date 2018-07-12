

#ifndef ADSITERATOR_C
#define ADSITERATOR_C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include <time.h>
#include<stdbool.h>
#include<stdint.h>

#include "datareplicator.c"
#include "iterator.h"

struct structiterator { /*iterator struct */
	void* object;
	void* (*startfunc)(struct structiterator* i);
	void* (*nextitem)(struct structiterator* i);
	void* extra;
	unsigned int max;
	unsigned int count;
};

iterator newiterator(void* self,void* (next)(iterator* i),void* (start)(iterator* i),int max,void * extra) /*iterator constructor */
{
	iterator i ;
	i.object = self;
	i.nextitem = next;
	i.startfunc = start;
	i.max = max;
	i.count = 0;
	i.extra = extra;
	return i;
}

void* iterator_start(void* _i)
{
	iterator* i = (iterator*)_i;
	i->count = 0;
	if(i->max <= i->count)
	{
		return NULL;
	}
	return i->startfunc(i);
}

void* iterator_next(void* _i)
{
	void*v;
	iterator* i = (iterator*)_i;
	i->count++;
	v= i->nextitem(i);
	if(i->max <= i->count)
	{
		v = NULL;
	}
	return v;
}

void* __arriterstart(iterator* i)
{
	return i->object;
}

void* __arriternext(iterator* i)
{
	long datatype ;char * c;
    memcpy(&datatype,&i->extra,sizeof(i->extra));
	c = (char*)i->object;
	i->object = c+datatype;
	return i->object;
}

iterator __array_iterator(void * arr,int64_t datatype,int size)
{
    void * v ;
	iterator i;
    memcpy(&v,&datatype,sizeof(int64_t));
	i = newiterator(arr,__arriternext,__arriterstart,size,v);
	return i;
}


#endif

