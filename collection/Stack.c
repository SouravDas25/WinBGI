



#ifndef ADS_Stck_C
#define ADS_Stck_C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utility.c"
#include "stack.h"

ADSClass(stack)
{
	ADSinit(stack);
    stackcontainer * head; //contains the current element to pop , pushing an poping all happens at the head
	unsigned int size; //store no of element that can be poped
	unsigned short datatype; //store the size of memory to allocate when new elements are pushed
	short ads;
};

ADSLinkMV(stack,copystack,freestack);

struct stackcontainer
{
	void * value;
	struct stackcontainer * next;
};

typedef struct stackcontainer stackcontainer;

stack init_stack(int datatype, short ads ) //constructor of the stack
{
	stack  l = RawObject(stack);
	checkMemory(l);
	l->head = NULL;
	l->size = 0;
	l->datatype = datatype;
	l->ads =ads;
	return l;
}

short stack_getads(stack self)
{
	return self->ads;
}

void stackpush_ByRef(stack self,void * value)
/*insert a new element in the stack (makes a copy of the data and stores the copy dosn't do any thing with the original)
Adds the new data to head and increment size */
{
	stackcontainer * l = (stackcontainer*)mycalloc(1,sizeof(stackcontainer));
	checkMemory(l);
	l->value = approprite_copy(self->ads,value,self->datatype);
	l->next = self->head;
	self->head = l;
	self->size += 1;
}

void* stack_pop_RtnRef(stack self)
/*removes a element from the stack and return it*/
{
	stackcontainer * trav = self->head;
	if(trav == NULL)
	{
		ValueError("Can't pop an empty stack");
	}
	self->head = self->head->next;
	self->size -= 1;
	void* v = trav->value;
	myfree(trav);
	return v;
}

void* stack_front_RtnRef(stack self)
{
	return approprite_copy(self->ads,self->head->value,self->datatype);
}

int stack_len(stack  self)// returns the no of element in the stack
{
	return self->size;
}

void printstack(stack self,void (*printfunction)(void*))
{
	stackcontainer * trav = self->head;
	printf("stack( ");
	while(trav != NULL)
	{
		printfunction(trav->value);
		if(trav->next != NULL)
		{
			printf(" , ");
		}
		trav = trav->next;
	}
	printf(" )");
}

bool isstack_Empty(stack self)
{
	if(self->head == NULL) return true;
	return false;
}

void stack_reverse(stack self)
{
	stackcontainer * trav = self->head,*previous = NULL,*next;
	while(trav != NULL)
	{
		next = trav->next;
		trav->next = previous;
		previous = trav;
		trav = next;
	}
	self->head = previous;
}

void* __stackiterstart(iterator* i)
{
	stack s = (stack)i->object;
	i->object = s->head;
	return ((stackcontainer*)i->object)->value;
}

void* __stackiternext(iterator* i)
{
	if(i->object != NULL)
	{
		i->object = ((stackcontainer*)i->object)->next;
		if(i->object != NULL) return ((stackcontainer*)i->object)->value;
		return NULL;
	}
	IterOverFlowError("in Stackiterator");
}

iterator stack_iterator(stack self)
{
	iterator i = newiterator(self,__stackiternext,__stackiterstart,stack_len(self),NULL);
	return i;
}


void * copystack(void* _self)
{
	stack self = (stack)_self;
	assert(strcmp(self->type,"stack") == 0);
	stack nwstck = init_stack(self->datatype,self->ads);
	stackcontainer * trav = self->head;
	while(trav != NULL)
	{
		stackpush_ByRef(nwstck,trav->value);
		trav = trav->next;
	}
	stack_reverse(nwstck);
	return nwstck;
}

void freestack(void * _self) //destroctor of the stack
{
	stack self = (stack)_self;
	assert(strcmp(self->type,"stack") == 0);
	int i ;stackcontainer * trav = self->head,*p;
	for(i=0;trav != NULL;i++)
	{
		p = trav;
		trav = trav->next;
		appropriate_delete(self->ads,p->value);
		myfree(p);
	}
	myfree(self);
}

void ADS_builtstack(stack self,void*arr,int n)
{
	int i;char * c = (char*)arr;int datatype = self->datatype;
	for(i = 0;i<n;i++)
	{
		void * val = c;
		val = evaluate_pointer(self->ads,(void**)val);
		stackpush_ByRef(self,val);
		c = (c+datatype);
	}
}

#endif
