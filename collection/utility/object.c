
#ifndef C_ObjectOriented_C
#define C_ObjectOriented_C

#include "GC.c"
#include "Types.c"

#include "object.h"

typedef struct {
	void* (*copyconstructor)(void*);
    void (*destructor)(void*);
    char * type;
}objectmethoddummy;

typedef struct {
	objectmethoddummy * tomethod;
	char * type;
}objectdummy;

void* __rawobject(int objectsize,void*mp)
{
	void * v = mycalloc(1,objectsize);
	objectmethoddummy * o = (objectmethoddummy*)mp;
	((objectdummy*)v)->tomethod = o;
	((objectdummy*)v)->type = o->type;
	return v;
}

void* Duplicate(void*var)
{
	return ((objectdummy*)var)->tomethod->copyconstructor(var);
}

void ads__delete(void**var,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		((objectdummy*)var[i])->tomethod->destructor(var[i]);
	}
}

#endif
