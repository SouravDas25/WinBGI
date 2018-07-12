




#ifndef ADSAVLTREE_H
#define ADSAVLTREE_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utility.h"
#include "list.h"

typedef struct treenode treenode;

ADSClassProto(Avltree);

#define INORDER 0
#define PREORDER 1
#define POSTORDER 2
#define AvltreeKEY 1
#define AvltreeDATA 0

//Public Function
#define newAvltree(n,cmpf,d)  init_Avltree(sizeof(n),cmpf,sizeof(d),__isADStype(#d),__isADStype(#n))
Avltree init_Avltree(int keytype, int (*compare)(void * data1,void*data2),int datatype,short ads,short keyads);

short Avltree_getads(Avltree self);
short Avltree_getKeyads(Avltree self);

void balanceAvltree( Avltree self);

#define Avltree_insert(self,key,value,keytype,datatype) ADS_KEYVALUE(Avltreeinsert_ByRef,Avltree_getads,\
Avltree_getKeyads,self,key,value,keytype,datatype)
void Avltreeinsert_ByRef(Avltree self,void* key,void* value);

#define Avltree_contains(self,key,type)  ADS_APPEND(Avltreecontains_ByRef,Avltree_getKeyads,self,key,type)
bool Avltreecontains_ByRef(Avltree self,void*key);

#define Avltree_delete(self,key,type)  ADS_APPEND(Avltreedelete_ByRef,Avltree_getKeyads,self,key,type)
void Avltreedelete_ByRef(Avltree self,void*key);

void freeAvltree(void* _self);
void printAvltree(Avltree self,void (*keyprintfunction)(void*),void (*dataprintfunction)(void*));
void * copyAvltree(void * _self);
list Avltree_keytraversal(Avltree self,int order,bool Keyordata);


//Private Function

#endif



