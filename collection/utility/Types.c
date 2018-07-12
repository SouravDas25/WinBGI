


#ifndef TYPESADS_C
#define TYPESADS_C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include<time.h>
#include<stdbool.h>

#include "Types.h"

static const char * __adstypelist[] = {"list","tuple","linklist","string","dict","set","Avltree","stack","queue","heap","minheap","maxheap",
"extrie","graph","deque","tree","treeleaf"};
unsigned short noftypes = sizeof(__adstypelist)/sizeof(char*);

int __isADStype(const char * typname)
{
	size_t i ;
	for(i=0;i<noftypes;i++)
	{
		if(strcmp(typname,__adstypelist[i]) == 0) return 1;
	}
	return -1;
}

#endif


