
#ifndef ADSLinklist_C
#define ADSLinklist_C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utility.c"

#include "linklist.h"

struct linklistcontainer                            /*declaring linklist node using structure*/
{
	void * value;                                   /*void* to hold any kind of datatype it is actually a pointer to ant kind of datatype*/
	struct linklistcontainer * next;                /*pointer to next node in linklist or NULL if no node available*/
};

typedef struct linklistcontainer linklistcontainer;

ADSClass(linklist) {                  /*ADSClass is a macro define in object.h header file it is use to create object like structure*/
	ADSinit(lnklist);                 /*ADSinit is a macro define in object.h it is used to declare standard class method and class type*/
    linklistcontainer * head;         /*node where the linklist start*/
	linklistcontainer * tail;         /*node where the linklist end*/
	linklistcontainer * now;		  /*address of the recently accessed item*/
	linklistcontainer * previous;	  /*address of the previous node of recently accessed item*/
	unsigned short nowindex;		  /*index of the recently accessed item*/
	short size;  					  /*no of node in linklist*/
	unsigned short datatype;		  /*no of bytes the use to store its value eg int use 2 or 4*/
	short ads;						  /*it is use to indicate wheathe the datatype is a ABSTRACT DATA STRUCTURE(ADS) OR NOT*/
};

ADSLinkMV(linklist,copylinklist,freelinklist);

linklistcontainer* linklist_XOR(linklistcontainer*arg1,linklistcontainer*arg2)
{
	return (linklistcontainer*) ((size_t)arg1^(size_t)arg2);
}

void Adslinklist_setiterator(linklist self,linklistcontainer*now,linklistcontainer*prev,int index)
{
	self->now = now;
	self->previous = prev;
	self->nowindex = index;
}

linklist init_linklist(int datatype,short ads)
{
	linklist  l = RawObject(linklist);
	l->head = NULL;
	l ->tail = NULL;
	l->size = 0;
	l->datatype = datatype;
	l->ads = ads;
	l->now = NULL;
	l->previous = NULL;
	l->nowindex = -1;
	return l;
}

short linklist_getads(linklist self)
{
	return self->ads;
}

void linklistappend_NoCopy(linklist self,void * value)
{
	linklistcontainer * l = (linklistcontainer *)mycalloc(1,sizeof(linklistcontainer)),*prev = self->tail,*next = NULL ;
	checkMemory(l);
	l->value = value;
	l->next = linklist_XOR(prev,next);
	if(self->head == NULL)
	{
		self->head = l;
		self->tail = l;
	}
	else
	{
		prev = linklist_XOR(self->tail->next,NULL);
		self->tail->next = linklist_XOR(prev,l);
		self->tail = l;
	}
	self->size ++;
}

void linklistappend_ByRef(linklist self,void * value)
{
	if(value == NULL)
	{
		MemoryError("Cannot copy NULL in Linklist Append");
	}
	void * cal = approprite_copy(self->ads,value,self->datatype);
	linklistappend_NoCopy(self,cal);
}

linklistcontainer* Ads_traverseThriter(linklist self,int index,linklistcontainer **addofprev,linklistcontainer **addofnext)
{
	int i;linklistcontainer * trav = NULL,*prev = NULL,*next=NULL;
	if(self->now == NULL || self->previous == NULL) return NULL;
	if( ( abs(index-self->nowindex) < index) && ( abs(index-self->nowindex) < abs(linklist_len(self)-1 - index)) )
	{
		trav = self->now;
		prev = self->previous;
		for(i=self->nowindex;i<index;i++)
		{
			next = linklist_XOR(trav->next,prev);
			prev = trav;
			trav = next;
		}
		if(addofprev)*addofprev = prev;
		if(addofnext)*addofnext = linklist_XOR(trav->next,prev);
		Adslinklist_setiterator(self,trav,prev,index);
	}
	else if( ( abs(self->nowindex-index) < index) &&  ( abs(self->nowindex-index) < abs(linklist_len(self)-1-index)) )
	{
		trav = self->previous;
		next = self->now;
		for(i=self->nowindex;i>index;i--)
		{
			prev = linklist_XOR(trav->next,next);
			next = trav;
			trav = prev;
		}
		if(addofprev)*addofnext = next;
		if(addofnext)*addofprev = linklist_XOR(trav->next,next);
		Adslinklist_setiterator(self,trav,linklist_XOR(trav->next,next),index);
	}
	return trav;
}

linklistcontainer* ADS_linklisttransverse(linklist self,int index,linklistcontainer **addofprev,linklistcontainer **addofnext)
{
	if(index<0 || index >= self->size)
	{
		IndexError("linklist Transverse Function %d",index);
	}
	int i ;linklistcontainer * trav = self->head,*prev = NULL,*next=NULL;
	if(trav==NULL)
	{
		MemoryError("Can't access an empty linklist");
	}
	if(self->now != NULL)
	{
		trav = Ads_traverseThriter(self,index ,addofprev,addofnext);
		if(trav != NULL) return trav;
	}
	if(index <= self->size/2)
	{
		trav = self->head;
		prev = NULL;
		for(i=0;i<index;i++)
		{
			next = linklist_XOR(trav->next,prev);
			prev = trav;
			trav = next;
		}
		if(addofprev)*addofprev = prev;
		if(addofnext)*addofnext = linklist_XOR(trav->next,prev);
		Adslinklist_setiterator(self,trav,prev,index);
	}
	else
	{
		trav = self->tail;
		next = NULL;
		for(i=self->size-1;i>index;i--)
		{
			prev = linklist_XOR(trav->next,next);
			next = trav;
			trav = prev;
		}
		if(addofprev)*addofnext = next;
		if(addofnext)*addofprev = linklist_XOR(trav->next,next);
		Adslinklist_setiterator(self,trav,linklist_XOR(trav->next,next),index);
	}
	return trav;
}

void linklistsetitem_ByRef(linklist self,int index,void*value)
{
	if(index<0 || index >= self->size)
	{
		IndexError("linklist Setitem Function %d",index);
	}
	if(value == NULL)
	{
		MemoryError("Cannot copy NULL in Linklist Setitem");
	}
	linklistcontainer * trav = ADS_linklisttransverse(self,index,NULL,NULL);
	if(trav == NULL)
	{
		MemoryError("Can't access an empty linklist");
	}
	void * cal = approprite_copy(self->ads,value,self->datatype);
	if(trav->value != NULL)  appropriate_delete(self->ads,trav->value) ;
	trav->value = cal;
}

void linklistinsert_ByRef(linklist self,int index,void*value)
{
	if(index < 0 || index >= self->size)
	{
		IndexError("linklist Setitem Function %d",index);
	}
	if(value == NULL)
	{
		MemoryError("Cannot copy NULL in linklist Setitem");
	}
	if(self->head == NULL)
	{
		MemoryError("Can't access an empty linklist");
	}
	void * cal = approprite_copy(self->ads,value,self->datatype);
	linklistcontainer * l = (linklistcontainer*)mycalloc(1,sizeof(linklistcontainer));
	l->value = cal;
	linklistcontainer * trav ,*prev ,*next=NULL;
	if(index == 0)
	{
		trav = self->head;
		prev = NULL;
		next = linklist_XOR(trav->next,prev);
		self->head = l;
		trav->next = linklist_XOR(l,next);
		l->next = linklist_XOR(prev,trav);
		Adslinklist_setiterator(self,self->head,NULL,index);
	}
	else
	{
		trav = ADS_linklisttransverse(self,index,&prev,&next);
		linklistcontainer * prevofprev = linklist_XOR(prev->next,trav);
		l->next = linklist_XOR(prev,trav);
		prev->next = linklist_XOR(prevofprev,l);
		trav->next = linklist_XOR(l,next);
		Adslinklist_setiterator(self,l,prev,index);
	}
	self->size++;
}

int linklist_len(linklist self)
{
	return self->size;
}

size_t linklist_sizeof(linklist self)
{
	size_t s = sizeof(*self);
	s+= linklist_len(self) * (sizeof(linklistcontainer) + self->datatype);
	return s;
}

void* linklistgetitem_NoCopy_RtnRef(linklist  self,int index)
{
	if(index<0 || index >= self->size)
	{
		IndexError("linklist Getitem Function %d",index);
	}
	linklistcontainer * trav = ADS_linklisttransverse(self,index,NULL,NULL);
	if(trav == NULL)
	{
		MemoryError("Can't access an empty linklist");
	}
	return trav->value;
}

void* linklist_getitem_RtnRef(linklist  self,int index)
{
	void * cal ,*value = linklistgetitem_NoCopy_RtnRef(self,index) ;
	cal = approprite_copy(self->ads,value,self->datatype);
	return cal;
}

void linklist_delitem(linklist  self,int index)
{
	if(index<0 || index >= self->size)
	{
		IndexError("linklist Delitem Function %d",index);
	}
	linklistcontainer * trav = self->head,*p,*prev = NULL,*next,*prevofprev,*nextofnext;
	if(trav== NULL)
	{
		MemoryError("Can't delete from an empty linklist");
	}
	trav = ADS_linklisttransverse(self,index,&prev,&next);
	if(index == 0)
	{
		p = self->head;
		next = linklist_XOR(self->head->next,NULL);
		if(next != NULL)
		{
			nextofnext = linklist_XOR(next->next,p);
			next->next = linklist_XOR(nextofnext,NULL);
		}
		else
		{
			self->tail = next;
		}
		self->head = next ;
		Adslinklist_setiterator(self,self->head,NULL,index);
	}
	else
	{
		p = trav;
		prevofprev = linklist_XOR(prev->next,trav);
		prev->next = linklist_XOR(prevofprev,next);
		if(next != NULL)
		{
			nextofnext = linklist_XOR(next->next,trav);
			next->next = linklist_XOR(nextofnext,prev);
		}
		else
		{
			self->tail = prev;
		}
		Adslinklist_setiterator(self,next,prev,index);
	}
	self->size--;
	appropriate_delete(self->ads,p->value);
	myfree(p);
}

bool islinklist_Empty(linklist self)
{
	if(self->head == NULL)return true;
	return false;
}

void* linklist_pop_RtnRef(linklist self)
{
	linklistcontainer * p = self->head,*next,*nextofnext;
	if(p == NULL)
	{
		MemoryError("Cannot Pop From Empty linklist");
	}
	void * val = p->value;
	next = linklist_XOR(self->head->next,NULL);
	if(next != NULL)
	{
		nextofnext = linklist_XOR(next->next,p);
		next->next = linklist_XOR(nextofnext,NULL);
	}
	else
	{
		self->tail = NULL;
	}
	Adslinklist_setiterator(self,self->head,NULL,0);
	self->head = next ;
	myfree(p);
	self->size--;
	return val;
}

void* linklist_popitem_RtnRef(linklist self,int index)
{
	if(index<0 || index >= self->size)
	{
		IndexError("linklist Popitem Function %d",index);
	}
	void * v = linklist_getitem_RtnRef(self,index);
	linklist_delitem(self,index);
	return v;
}

void linklist_extend(linklist self,linklist other)
{
	linklistcontainer * trav=NULL,*p=NULL,*prev = NULL,*next=NULL;
	trav = other->head;
	while(trav != NULL)
	{
		p = trav;
		next = linklist_XOR(trav->next,prev);
		prev = trav;
		trav = next;
		linklistappend_ByRef(self,p->value);
	}
}

int linklistindex_ByRef(linklist self,void * value,int (*comparefunction)(void*,void*))
{
	linklistcontainer * trav,*prev = NULL,*next;
	trav = self->head;int i = 0;
	while(trav != NULL)
	{
		if (appropriate_compare(comparefunction,trav->value,value,self->datatype) == 0 )
		{
			return i;
		}
		next = linklist_XOR(trav->next,prev);
		prev = trav;
		trav = next;
		i++;
	}
	return -1;
}

void linklistremove_ByRef(linklist self,void * value,int (*comparefunction)(void*,void*))
{
	int index = linklistindex_ByRef(self,value,comparefunction);
	if(index != -1 ) linklist_delitem(self,index);
}

void linklist_reverse(linklist self)
{
	linklistcontainer * trav = self->head;
	self->head = self->tail;
	self->tail = trav;
	self->nowindex = linklist_len(self) - self->nowindex;
	trav = self->now;
	self->now = self->previous;
	self->previous = self->now;
}

void* __linklistiterstart(iterator* i)
{
	linklist s = (linklist)i->object;
	return linklistgetitem_NoCopy_RtnRef(s,i->count);
}

void* __linklistiternext(iterator* i)
{
	linklist s = (linklist)i->object;
	i->max = (unsigned)linklist_len(s);
	if((unsigned)linklist_len(s)>i->count)
	{
		return linklistgetitem_NoCopy_RtnRef(s,i->count);
	}
	return NULL;
}

iterator linklist_iterator(linklist self)
{
	iterator i = newiterator(self,__linklistiternext,__linklistiterstart,linklist_len(self),NULL);
	return i;
}


void printlinklist(linklist self,void (*printfunction)(void*))
{
	linklistcontainer * trav,*prev = NULL,*next;
	trav = self->head;
	printf("linklist[ ");
	while(trav != NULL)
	{
		printfunction(trav->value);
		next = linklist_XOR(trav->next,prev);
		prev = trav;
		trav = next;
		if(trav != NULL)
		{
			printf(" , ");
		}
	}
	printf(" ]");
}

void* copylinklist(void *_self)
{
	linklist self = ((linklist)_self);
	assert(strcmp(self->type,"linklist") == 0);
	linklist l = init_linklist(self->datatype,self->ads);
	linklistcontainer * trav,*p,*prev = NULL,*next;
	trav = self->head;
	while(trav != NULL)
	{
		p = trav;
		next = linklist_XOR(trav->next,prev);
		prev = trav;
		trav = next;
		linklistappend_ByRef(l,p->value);
	}
	return l;
}

void linklist_clear(linklist self)
{
	linklistcontainer * trav=NULL,*p=NULL,*prev = NULL,*next=NULL;
	trav = self->head;
	while(trav != NULL)
	{
		p = trav;
		next = linklist_XOR(trav->next,prev);
		prev = trav;
		trav = next;
		appropriate_delete(self->ads,p->value) ;
		myfree(p);
	}
	self->head = NULL;
	self->tail = NULL;
	self->size = 0;
	Adslinklist_setiterator(self,NULL,NULL,-1);
}

void freelinklist_NoDelete(void * _self)
{
	linklist self = ((linklist)_self);
	assert(strcmp(self->type,"linklist") == 0);
	linklistcontainer * trav,*p,*prev = NULL,*next;
	trav = self->head;
	while(trav != NULL)
	{
		p = trav;
		next = linklist_XOR(trav->next,prev);
		prev = trav;
		trav = next;
		myfree(p);
	}
	myfree(self);
}

void freelinklist(void * _self)
{
	linklist self = ((linklist)_self);
	assert(strcmp(self->type,"linklist") == 0);
	linklistcontainer * trav=NULL,*p=NULL,*prev = NULL,*next=NULL;
	trav = self->head;
	while(trav != NULL)
	{
		p = trav;
		next = linklist_XOR(trav->next,prev);
		prev = trav;
		trav = next;
		appropriate_delete(self->ads,p->value) ;
		myfree(p);
	}
	myfree(self);
}

void ADS_builtlinklist(linklist self,void*arr,int n)
{
	int i;char * c = (char*)arr;int datatype = self->datatype;
	for(i = 0;i<n;i++)
	{
		void * val = c;
		val = evaluate_pointer(self->ads,(void**)val);
		linklistappend_ByRef(self,val);
		c = (c+datatype);
	}
}

#endif
