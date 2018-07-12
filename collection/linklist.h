
#ifndef ADSLinklist_H
#define ADSLinklist_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utility.h"

typedef struct linklistcontainer linklistcontainer;
ADSClassProto(linklist);

/*Public Function*/
#define newlinklist(n) init_linklist(sizeof(n),__isADStype(#n))
linklist init_linklist(int datatype,short ads);

short linklist_getads(linklist self);

void linklistappend_NoCopy(linklist self,void * value);

#define linklist_append(self,value,type)  ADS_APPEND(linklistappend_ByRef,linklist_getads,self,value,type)
void linklistappend_ByRef(linklist self,void * value);


#define linklist_setitem(self,index,value,type) ADS_SETITEM(linklistsetitem_ByRef,linklist_getads,self,index,value,type)
void linklistsetitem_ByRef(linklist self,int index,void*value);

#define linklist_insert(self,index,value,type) ADS_SETITEM(linklistinsert_ByRef,linklist_getads,self,index,value,type)
void linklistinsert_ByRef(linklist self,int index,void*value);

int linklist_len(linklist self);

size_t linklist_sizeof(linklist self);

#define linklistgetitem_NoCopy(self,index,type) ADS_GETITEM_NOFREE(linklistgetitem_NoCopy_RtnRef,self,index,type)
void* linklistgetitem_NoCopy_RtnRef(linklist  self,int index);

#define linklist_getitem(self,index,type) ADS_GETITEM(linklist_getitem_RtnRef,self,index,type)
void* linklist_getitem_RtnRef(linklist  self,int index);

void linklist_delitem(linklist  self,int index);

bool islinklist_Empty(linklist self);

#define linklist_pop(self,type) ADS_POP(linklist_pop_RtnRef,self,type)
void* linklist_pop_RtnRef(linklist self);

#define linklist_popitem(self,index,type) ADS_GETITEM(linklist_popitem_RtnRef,self,index,type)
void* linklist_popitem_RtnRef(linklist self,int index);

void linklist_extend(linklist self,linklist other);

#define linklist_index(self,func,value,type) ADS_SENDFUNC(linklistindex_ByRef,linklist_getads,self,func,value,type)
int linklistindex_ByRef(linklist self,void * value,int (*comparefunction)(void*,void*));

#define linklist_remove(self,func,value,type) ADS_SENDFUNC(linklistremove_ByRef,linklist_getads,self,func,value,type)
void linklistremove_ByRef(linklist self,void * value,int (*comparefunction)(void*,void*));

void linklist_reverse(linklist self);

iterator linklist_iterator(linklist self);

void printlinklist(linklist self,void (*printfunction)(void*));

void* copylinklist(void *_self);

void linklist_clear(linklist self);

void freelinklist_NoDelete(void * _self);

void freelinklist(void * _self);

#define builtlinklist(self,type,...) {type aaa[] = {__VA_ARGS__};ADS_builtlinklist(self,aaa,sizeof(aaa)/sizeof(type));}
void ADS_builtlinklist(linklist self,void*arr,int n);

/*Private Function*/

#endif
