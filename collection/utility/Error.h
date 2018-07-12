
#ifndef ADSError_H
#define ADSError_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include <time.h>
#include<stdbool.h>

#define IndexError(...) printf("\nError Captured In file %s In line %d \n\nIndexError : Index Out of Range in ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define ListAllocationError(...) printf("\nError Captured In file %s In line %d \n\nAllocationError : Out of Memory Cannot Expand Size of the List in ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define TypeError(...) printf("\nError Captured In file %s In line %d \n\nTypeError : ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define ValueError(...) printf("\nError Captured In file %s In line %d \n\nValueError : ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define SystemError(...) printf("\nError Captured In file %s In line %d \n\nSystemError : ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define FormattingError(...) printf("\nError Captured In file %s In line %d \n\nFormattingError : ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define MemoryError(...)   printf("\nError Captured In file %s In line %d \n\nMemoryError : ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define KeyError(...)   printf("\nError Captured In file %s In line %d \n\nKeyError : ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define IterOverFlowError(...)   printf("\nError Captured In file %s In line %d \n\nIterOverFlowError : ",__FILE__,__LINE__);\
printf(__VA_ARGS__);printf("\n\n");\
system("pause");exit(EXIT_FAILURE)

#define checkMemory(n) if(n == NULL){MemoryError("Out of Memory");}

#define checkType(self,typ)  assert(strcmp(self->type,#typ) == 0)


#endif
