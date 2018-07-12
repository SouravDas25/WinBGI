


#ifndef ADSUTILITY_C
#define ADSUTILITY_C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>
#include<stdarg.h>
#include <time.h>
#include <stdbool.h>

#include "utility\error.h"
#include "utility\datareplicator.c"
#include "utility\gc.c"
#include "utility\iterator.c"
#include "utility\defaultargs.h"
#include "utility\object.c"
#include "utility\Types.c"
#include "utility.h"
#include "utility\timeit.c"



/*reprfunction*/

/*takes the address of the variable and send it to stdio */

void printchar(void*add)
{
	printf("%c",*(char*)add);
}

void printint(void*add)
{
	printf("%d",*(int*)add);
}

void printfloat(void*add)
{
	printf("%f",*(float*)add);
}

void printdouble(void*add)
{
	printf("%f",*(double*)add);
}

void printbool(bool a)
{
	if(a == true) printf("true");
	else printf("false");
}

/*compare*/
/*take the address of two variable and return int as compared value*/

int charcompare(void*a,void*b)
{
	char x= *(char*)a,y=*(char*)b;
	if(x>y)return 1;
	if(x<y)return -1;
	return 0;
}

int intcompare(void*a,void*b)
{
	int x= *(int*)a,y=*(int*)b;
	if(x>y)return 1;
	if(x<y)return -1;
	return 0;
}

int floatcompare(void*a,void*b)
{
	int x= *(float*)a,y=*(float*)b;
	if(x>y)return 1;
	if(x<y)return -1;
	return 0;
}

int doublecompare(void*a,void*b)
{
	int x= *(double*)a,y=*(double*)b;
	if(x>y)return 1;
	if(x<y)return -1;
	return 0;
}

int appropriate_compare(int (*comparefunction)(void*,void*),void*data1,void*data2,int datatype)
{
	int c ;
	if(comparefunction != INBUILTCMP)
	{
		c = comparefunction(data1,data2);
	}
	else c = memcmp(data1,data2,datatype);
	return c;
}

/*utility*/ 

bool isprime(int n) 
{
	int i,sqr;
	if((n & 0x1)==0) return false;
	sqr = sqrt(n);
	for(i=3;i<=sqr;i+=2)
	{
		if(n%i==0) return false;
	}
	return true;
}

int nextprime(int start) /*return the prime number after the given number*/
{
	int i;
	for(i=start+1;;i++)
	{
		if(isprime(i)==true) return i;
	}
	return -1;
}

int previousprime(int start) /*return the prime number before the given number*/
{
	int i;
	for(i=start;i>2;i--)
	{
		if(isprime(i)==true) return i;
	}
	return 2;
}

uint64_t cstring_hash(const char*buffer) /*produces a hash value of a string */
{
	uint64_t val=0,i,len=strlen(buffer);
	val = buffer[0]>>7;
	for(i=0;i<len;i++)
	{
		val += 1000003*val^buffer[i];
	}
	val = val ^ len ;
	return val;
}

uint64_t int64_hash(void*add)
{
	uint64_t x = *(uint64_t*)add;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    x = x ^ (x >> 31);
    return x;
}

uint64_t double_hash(void*add)
{
	double d =*(double*)add;
	if(d == 0) return 0;
	else
	{
		int exponent;
		double mantissa = frexp(d,&exponent);
		return (2*fabs(mantissa)-1)*~exponent;
	}
}

#endif

