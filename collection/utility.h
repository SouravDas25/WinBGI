

#ifndef ADSUTILITY_H
#define ADSUTILITY_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include<time.h>
#include<stdbool.h>

#include "utility\error.h"
#include "utility\datareplicator.h"
#include "utility\gc.h"
#include "utility\iterator.h"
#include "utility\defaultargs.h"
#include "utility\object.h"
#include "utility\Types.h"

#define False false
#define True true

#define LEFT true
#define RIGHT false

#define bool2cstring(b) (b == true)? "true" : "false"
 
#define EndOfStr '\0'

#define LB printf("\n");
#define ln printf("\n");

/*reprfunction*/
/*takes the address of the variable and send it to stdio */

void printchar(void*add);
void printint(void*add);
void printfloat(void*add);
void printdouble(void*add);
void printbool(bool a);

#define printarray(arr,n,printfunction) { printf("\nArray( "); int __PRINTARRAYLOOPVARI__; for( __PRINTARRAYLOOPVARI__ = 0;\
__PRINTARRAYLOOPVARI__< n;__PRINTARRAYLOOPVARI__++){ printfunction(&arr[__PRINTARRAYLOOPVARI__]);\
if(__PRINTARRAYLOOPVARI__ < n-1)printf(" , "); } printf(" )\n");}

/*compare*/
/*take the address of two variable and return int as compared value*/

int charcompare(void*a,void*b);
int intcompare(void*a,void*b);
int floatcompare(void*a,void*b);
int doublecompare(void*a,void*b);
int appropriate_compare(int (*comparefunction)(void*,void*),void*data1,void*data2,int datatype);

/*utility*/ 

bool isprime(int n) ;
int nextprime(int start); /*return the prime number after the given number*/
int previousprime(int start); /*return the prime number before the given number*/
uint64_t cstring_hash(const char*buffer); /*produces a hash value of a string */


#endif


