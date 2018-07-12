
/**
	@file list.h
	@brief Macro and Function prototype for list ADS Datatype.

	@author SD(Sourav Das)
*/

#ifndef ADSLIST_H
#define ADSLIST_H

#include "utility.h"

/*Class Prototype of list.*/
ADSClassProto(list);

/*Public Function*/

//! A Macro Function for initializing list variable with appropriate type and size.
/*!
 \param n type argument [the type of object to be stored in the list]
 \param s minimum size of the list or vetor array
 \see init_list(int datatype,int size, short ads)
 \return a list object
*/
#define newlist(n,s)  init_list(sizeof(n) ,s ,__isADStype(#n))

//!Constructor of list class
list init_list(int datatype,int size, short ads);

//! List Length Function.
int list_len(list self);

//! ADS type Flags.
short list_getads(list self);

//! List Append Function No Data Replication.
void listappend_NoCopy(list self,void * value);

//! List Append Macro.
/*!
   \param self a list instance
   \param value the variable to insert into list
   \see listappend_ByRef(list self,void * value)
*/
#define list_append(self,value,type) ADS_APPEND(listappend_ByRef,list_getads,self,value,type)

//! List Append Function With Data Replication.
void listappend_ByRef(list self,void * value);

//! List Getitem Function Without Data Replication.
/*!
   \param self a list instance
   \param index a integer position
   \see listgetitem_NoCopy_RtnRef(list self,int index)
   \return element stored at that position
*/
#define listgetitem_NoCopy(self,index,type) ADS_GETITEM_NOFREE(listgetitem_NoCopy_RtnRef,self,index,type)

//! List Getitem Function Without Data Replication.
void* listgetitem_NoCopy_RtnRef(list self,int index);

//! List Getitem Function With Data Replication.
/*!
   \param self a list instance
   \param index a integer position
   \see list_getitem_RtnRef(list self,int index)
   \return copy of element stored at that position
*/
#define list_getitem(self,index,type) ADS_GETITEM(list_getitem_RtnRef,self,index,type)

//! List Getitem Function With Data Replication.
void* list_getitem_RtnRef(list self,int index);

//! Overwrite a element at a pertucular index.
/*!
   \param self a list instance
   \param index a integer position
   \param value variable which will overwrite the current value
   \see listsetitem_ByRef(list self,int index,void*value)
*/
#define list_setitem(self,index,value,type) ADS_SETITEM(listsetitem_ByRef,list_getads,self,index,value,type)

//! Overwrite a element at a pertucular index..
void listsetitem_ByRef(list self,int index,void*value);

//! Insert a element at the Position provided.
/*!
   \param self a list instance
   \param index a integer position
   \param value variable which will be inserted
   \see listinsert_ByRef(list self,int index,void*value)
*/
#define list_insert(self,index,value,type) ADS_SETITEM(listinsert_ByRef,list_getads,self,index,value,type)

//! Insert a copy of the element at the Position provided.
void listinsert_ByRef(list self,int index,void*value);

//! Adds all elements from one list to another.
void list_extend(list self,list other);

//! Reverse the list Provided.
void list_reverse(list self);

//! Delete the element at the index provided.
void list_delitem(list self,int index) ;

//! Removes the first elements a returs it.
/*!
   \param self a list instance
   \param type datatype of the element
   \see  listpop_RtnRef(list self);
*/
#define list_pop(self,type) ADS_POP(listpop_RtnRef,self,type)


void* listpop_RtnRef(list self);

//!decrease the occupied memory of the list to fit all the items.
void list_shrink(list self);

//!call the given function on all its data.
void list_map(list self,void(*function)(void*value));

//!return a iterator over the list Should not be used without foreach loop.
iterator list_iterator(list self);

//!print the entire list to stdout.
void printlist(list self,void(*print)(void*value));

//!removes all  item from list.
void list_clear(list l );

//!return a copy of the list and its item.
void* copylist(void *l);

//!destructor of the list.
void freelist(void* l );

//!return int index of the value provided if value not present return -1.
#define list_index(self,func,value,type) ADS_SENDFUNC(listindex_ByRef,list_getads,self,func,value,type)
int listindex_ByRef(list self,void *value,int (*compare)(void*,void*)) ;

//!return the no of time the value appear in the list if compare function is not given uses mem compare.
#define list_count(self,func,value,type) ADS_SENDFUNC(listcount_ByRef,list_getads,self,func,value,type)
int listcount_ByRef(list self,void * value,int (*compare)(void*,void*));

//!deletes all the occurence of the value from the list.
#define list_remove(self,func,value,type) ADS_SENDFUNC(listremove_ByRef,list_getads,self,func,value,type)
void listremove_ByRef(list self,void * value,int (*compare)(void*,void*));

//!sorts the list .
void list_sort(list self,int (*compare)(void*,void*));

//! Uses a binarysearch to search an element in the list.
#define list_binarysearch(self,func,value,type) ADS_SENDFUNC(listbinarysearch_ByRef,list_getads,self,func,value,type)
int listbinarysearch_ByRef(list self,void * value ,int (*compare)(void*,void*) ) ;


#define builtlist(self,type,...) {type ADS__aaa[] = {__VA_ARGS__};ADS__builtList(self,ADS__aaa,sizeof(ADS__aaa)/sizeof(type));}
void ADS__builtList(list self,void*arr,int n);

#endif
