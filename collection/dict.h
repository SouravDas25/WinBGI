


#ifndef ADSDict_H
#define ADSDict_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define False false
#define True true


#include "utility.h"
#include "linklist.h"
#include "List.h"

typedef struct lnlist lnlist;

typedef struct listhead listhead;

ADSClassProto(dict);

/*Public Function*/

#define newdict(keytype,hashfunction,datatype,size) \
init_dict(sizeof(keytype),hashfunction,__isADStype(#keytype),sizeof(datatype),size,__isADStype(#datatype))
dict init_dict(int keytype,uint64_t (*hashfuntion)(void*),int keyads,int datatype,int size, short ads);

short dict_getads(dict self);
short dict_keyads(dict self);

bool dicthaskey_ByRef(dict  self,void* key);

int dict_len(dict self);

list dict_keys(dict self);

list dict_values(dict self);

void dictsetitem_ByRef(dict self,void* key,void*value);

void* dictgetitem_NoCopy_RtnRef(dict self,void* key);

void* dict_getitem_RtnRef(dict self,void* key);

void* dict_popitem_RtnRef(dict self,void* key);

void dictdelitem_ByRef(dict self,void* key);

int dict_sizeof(dict self);

void dict_extend(dict self,dict other);

void printdict(dict  self,void(*keyprintfunction)(void*),void (*dataprintfunction)(void*));

void * copydict(void * _self);

void dict_clear(dict self);

void freedict(void* _self);


//Private Function


#endif

