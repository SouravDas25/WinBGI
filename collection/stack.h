


#ifndef ADS_Stck_H
#define ADS_Stck_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utility.h"

typedef struct stackcontainer stackcontainer;

ADSClassProto(stack);

//Public Function
#define newstack(n) init_stack(sizeof(n),__isADStype(#n))
stack init_stack(int datatype, short ads ); //constructor of the stack

short stack_getads(stack self);

#define stack_push(self,value,type) ADS_APPEND(stackpush_ByRef,stack_getads,self,value,type)
void stackpush_ByRef(stack self,void * value);

#define stack_pop(self,type) ADS_POP(stack_pop_RtnRef,self,type)
void* stack_pop_RtnRef(stack self);

#define stack_front(self,type) ADS_POP(stack_front_RtnRef,self,type)
void* stack_front_RtnRef(stack self);

int stack_len(stack  self); // returns the no of element in the stack

void printstack(stack self,void (*printfunction)(void*));

bool isstack_Empty(stack self); //checks weather the stack is empty or not

void stack_reverse(stack self);

iterator stack_iterator(stack self);

void * copystack(void* _self);

void freestack(void * _self); //destroctor of the stack

#define builtstack(self,type,...) {type aaa[] = {__VA_ARGS__};ADS_builtstack(self,aaa,sizeof(aaa)/sizeof(type));}
void ADS_builtstack(stack self,void*arr,int n);

//Private Function
void* __stackiterstart(iterator* i);
void* __stackiternext(iterator* i);

#endif


