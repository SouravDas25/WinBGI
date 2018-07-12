

#ifndef garbagecollector_C
#define garbagecollector_C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include<time.h>
#include<stdbool.h>
#include<stdint.h>

#include "Error.h"
#include "GC.h"

typedef struct __gcpointer { /*stack node struct declaration*/
	void* allocated ;
	struct __gcpointer* next ;
	short size;
	short NumberOfItems;
} __gcpointer ;

int64_t ADS_TOTALMEMORYMAP = 0;
int64_t ADS_GC_TotalMemoryUSED = 0;
static int __maxGCalocateinlist__ = 0; /*maximum number of dynamically alocated data active in occupied stack at some point */
static int __LenGCcalls__ = 0; /*current no of active dynamically allocated data in occupied stack */
static int __TotalGCcalls__ = 0; /*total no of call made to mycalloc*/
static __gcpointer* __gcobjhead__ = NULL; /*stack head for occupied stack */

void* mycalloc(int n,int size) /*allocate dynamic memory in a safe way maintaing a stack of occupied element */
{
	void * b = calloc(n,size);
	__gcpointer* p = (__gcpointer*)calloc(1,sizeof(__gcpointer));
	checkMemory(b);checkMemory(p);
	p->allocated = b;
	p->NumberOfItems = n;
	p->size = size;
	p->next = __gcobjhead__;
	ADS_TOTALMEMORYMAP += n*size;
	__gcobjhead__ = p;
	__TotalGCcalls__++;
	__LenGCcalls__++;
	if(__LenGCcalls__ > __maxGCalocateinlist__)
	__maxGCalocateinlist__ = __LenGCcalls__ ;
	if(ADS_TOTALMEMORYMAP > ADS_GC_TotalMemoryUSED ) ADS_GC_TotalMemoryUSED = ADS_TOTALMEMORYMAP;
	return b;
}

void* mymalloc(UINT size) /*allocate dynamic memory in a safe way maintaing a stack of occupied element */
{
	return mycalloc(1,size);
}

void Garbagecheck() /*prints the occupied stack */
{
	__gcpointer* trav ,*prev ;
	trav = __gcobjhead__;
	prev = NULL;
	printf("\n\n\n Allocated [ ");
	while(trav != NULL)
	{
		printf("\n%p, n = %d , size = %d ",trav->allocated,trav->NumberOfItems,trav->size);
		prev = trav;
		trav = trav->next;
	}
	trav = prev;
	printf(" ]\n MaxGC = %d ,ActiveAllocated = %d ,Totalcalls = %d\n",__maxGCalocateinlist__,__LenGCcalls__,__TotalGCcalls__);
	printf(" Total Dynamic Memory Used = %I64d KiB %I64d Bytes.",ADS_GC_TotalMemoryUSED/1024,ADS_GC_TotalMemoryUSED%1024);
}

void myfree(void* a) /*frees the memory from occupied stack */
{
	__gcpointer* trav,*prev;
	if(a == NULL)
	{
		MemoryError("Cannot Free a NULL pointer");
	}
	trav = __gcobjhead__;
	prev = NULL;
	while(trav != NULL)
	{
		if(trav->allocated == a)
		{
			ADS_TOTALMEMORYMAP -= trav->NumberOfItems*trav->size;
			if(prev == NULL) __gcobjhead__ = trav->next;
			else prev->next = trav->next;
			free(a);
			free(trav);
			__LenGCcalls__--;
			return;
		}
		prev = trav;
		trav = trav->next;
	}
	MemoryError("Memory address %p provided is a dangling pointer",a);
}

#endif

