

#ifndef ADSITERATOR_H
#define ADSITERATOR_H

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

#include "datareplicator.h"

typedef struct structiterator structiterator;
typedef structiterator iterator;

/*Creates a new iterator object.*/
iterator newiterator(void* self,void* (next)(iterator* i),void* (start)(iterator* i),int max,void * extra); /*iterator constructor */

/*frees the iterator object.*/
void freeiterator(iterator* i);

/*iterator start function.*/ 
void* iterator_start(void* _i);

/*iterator next Function.*/ 
void* iterator_next(void* _i);

#define scanitem(var,type) ({ void* v = var ; \
								type d = (*(type*)v) ;\
								myfree(v) ;\
								d ; })

#define refitem(var,type) (*(type*)var)
#define cast(var,type) ((type)var)

#define ADS_GETITEM_NOFREE(function,self,index_or_key,type) ({\
			void * ADS_AUTOFREE_GETITEM_NOFREE_VOID_PTR_VAR_ = function(self,index_or_key);\
			type * ADS_AUTOFREE_GETITEM_NOFREE_TYPE_PTR_VAR_ = (__isADStype(#type) == -1) ? (type*)ADS_AUTOFREE_GETITEM_NOFREE_VOID_PTR_VAR_ : \
			(type*)&ADS_AUTOFREE_GETITEM_NOFREE_VOID_PTR_VAR_;*ADS_AUTOFREE_GETITEM_NOFREE_TYPE_PTR_VAR_;})

#define ADS_GETITEM(function,self,index_or_key,type) ({\
			void * _ADSAUTOFREE_GETITEM_VOID_PTR_VAR_ = function(self,index_or_key);\
			type _ADSAUTOFREE_GETITEM_TYPE_VAR_;\
			if(__isADStype(#type) == -1){ \
				memcpy(&_ADSAUTOFREE_GETITEM_TYPE_VAR_,_ADSAUTOFREE_GETITEM_VOID_PTR_VAR_,sizeof(type));\
				myfree(_ADSAUTOFREE_GETITEM_VOID_PTR_VAR_);\
			} \
			else {  memcpy(&_ADSAUTOFREE_GETITEM_TYPE_VAR_,&_ADSAUTOFREE_GETITEM_VOID_PTR_VAR_,sizeof(type));\
			} \
			 	_ADSAUTOFREE_GETITEM_TYPE_VAR_;})

#define ADS_KEYVALUETYPE_NOFREE(function,adsfunc,self,key,keytype,type) ({\
		keytype ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__ = (key); \
		void * ADS_AUTOFREE_GETITEM_NOFREE_VOID_PTR_VAR_ = \
		function(self,evaluate_pointer(adsfunc(self),(void**)&ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__));;\
		type * ADS_AUTOFREE_GETITEM_NOFREE_TYPE_PTR_VAR_ = (__isADStype(#type) == -1) ? (type*)ADS_AUTOFREE_GETITEM_NOFREE_VOID_PTR_VAR_ : \
		(type*)&ADS_AUTOFREE_GETITEM_NOFREE_VOID_PTR_VAR_;*ADS_AUTOFREE_GETITEM_NOFREE_TYPE_PTR_VAR_;})

#define ADS_KEYVALUETYPE(function,adsfunc,self,key,keytype,type) ({\
		keytype  ADS_Check_KEYTYPEVAR_INTERMIDIATE_NOTNEED__ = (key);\
		void * _ADSAUTOFREE_GETITEM_VOID_PTR_VAR_ = function(self,\
		evaluate_pointer(adsfunc(self),(void**)&ADS_Check_KEYTYPEVAR_INTERMIDIATE_NOTNEED__));\
		type _ADSAUTOFREE_GETITEM_TYPE_VAR_;\
		if(__isADStype(#type) == -1) { \
			memcpy(&_ADSAUTOFREE_GETITEM_TYPE_VAR_,_ADSAUTOFREE_GETITEM_VOID_PTR_VAR_,sizeof(type));\
			myfree(_ADSAUTOFREE_GETITEM_VOID_PTR_VAR_);\
		} \
		else {  memcpy(&_ADSAUTOFREE_GETITEM_TYPE_VAR_,&_ADSAUTOFREE_GETITEM_VOID_PTR_VAR_,sizeof(type));\
		} \
		_ADSAUTOFREE_GETITEM_TYPE_VAR_;})

#define ADS_POP(function,self,type) ({\
			void * _ADSAUTOFREE_POP_VOID_PTR_VAR_ = function(self);\
			type _ADSAUTOFREE_POP_TYPE_VAR_; \
			if(__isADStype(#type) == -1){ \
				memcpy(&_ADSAUTOFREE_POP_TYPE_VAR_,_ADSAUTOFREE_POP_VOID_PTR_VAR_,sizeof(type));\
				myfree(_ADSAUTOFREE_POP_VOID_PTR_VAR_);\
			} \
			else { memcpy(&_ADSAUTOFREE_POP_TYPE_VAR_,&_ADSAUTOFREE_POP_VOID_PTR_VAR_,sizeof(type)); }\
			 	_ADSAUTOFREE_POP_TYPE_VAR_;})

#define ADS_APPEND(function,adsfunc,self,value,type) ({ \
		type ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__ = (value);\
		function(self,evaluate_pointer(adsfunc(self),(void**)&ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__));	})
		
#define ADS_KEYVALUE(function,adsfunc,keyadsfunc,self,key,value,keytype,datatype) ({ \
		keytype  ADS_Check_KEYTYPEVAR_INTERMIDIATE_NOTNEED__ = (key);\
		datatype ADS_Check_DATATYPEVAR_INTERMIDIATE_NOTNEED__ = (value);\
		function(self,evaluate_pointer(keyadsfunc(self),(void**)&ADS_Check_KEYTYPEVAR_INTERMIDIATE_NOTNEED__)\
		,evaluate_pointer(adsfunc(self),(void**)&ADS_Check_DATATYPEVAR_INTERMIDIATE_NOTNEED__));	})
		
#define ADS_SETITEM(function,adsfunc,self,index,value,type) ({ \
		type ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__ = (value);\
		function(self,index,evaluate_pointer(adsfunc(self),(void**)&ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__));	})

#define ADS_SENDFUNC(function,adsfunc,self,sendfunc,value,type) ({ \
		type ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__ = (value);\
		function(self,evaluate_pointer(adsfunc(self),(void**)&ADS_Check_TYPEVAR_INTERMIDIATE_NOTNEED__),sendfunc);	})


/*a foreach loop it takes a iterator a calls the iterator start and next function till a stop is encountered. */ 
#define ads_foreach(loopvar,iterfunc,type)   \
{ iterator __I##loopvar##__ = iterfunc;void *___##loopvar##__;short __ADS##LoopVAR##___ = __isADStype(#type); \
for(___##loopvar##__ = iterator_start(&__I##loopvar##__); ___##loopvar##__ != NULL ; ___##loopvar##__ = iterator_next(&__I##loopvar##__)) \
{  type * ____add##loopvar__ = (__ADS##LoopVAR##___ == -1) ? (type*)___##loopvar##__ : (type*)&___##loopvar##__;\
   type loopvar = *____add##loopvar__;

/*End part of the foreach loop.*/
#define ads_next(loopvar) } }

/* A iterator over an array.*/
#define array_iterator(array,size) __array_iterator(array,sizeof(*array),size)
structiterator __array_iterator(void * arr,int64_t datatype,int size);

#endif

