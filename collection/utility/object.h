


#ifndef C_ObjectOriented_H
#define C_ObjectOriented_H

#include "GC.h"
#include "Types.h"

#define ADS_StructOf(name) name##_object_struct
#define ADS_MethodStructName(name) name##_method_struct
#define ADS_MethodVariableName(name) name##_method_variable


#define ADSClass(name)  typedef struct ADS_StructOf(name) ADS_StructOf(name) ; \
						typedef struct ADS_MethodStructName(name) ADS_MethodStructName(name);\
						struct ADS_MethodStructName(name) { \
							void* (*copyconstructor)(void*) ; \
							void (*destructor)(void*) ; \
							const char * type; \
						};\
						struct ADS_StructOf(name)
						
#define ADSinit(name) struct ADS_MethodStructName(name)* tomethod;const char* type

#define ADSLinkMV(name,cc,d)  void* cc(void*); \
								void d(void*); ADS_MethodStructName(name) ADS_MethodVariableName(name) = {cc,d,#name}
						
#define ADSClassProto(name) typedef struct ADS_StructOf(name)* name

#define Allocate(type) (type*)mycalloc(1,sizeof(type))
#define Deallocate(variable) myfree(variable)



#define RawObject(name) (name)__rawobject(sizeof(ADS_StructOf(name)),&ADS_MethodVariableName(name))
void* __rawobject(int objectsize,void*mp);

void* Duplicate(void*var);

#define ads_delete(...) {void* aaa[] = {__VA_ARGS__};ads__delete(aaa,sizeof(aaa)/sizeof(void*));}
void ads__delete(void**var,int n);


#endif
