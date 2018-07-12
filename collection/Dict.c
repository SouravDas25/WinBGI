



#ifndef ADSDict_C
#define ADSDict_C


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "utility.c"
#include "List.c"
#include "linklist.c"

#include "dict.h"

ADSClass(dict)
{
	ADSinit(dict);
	linklist * raw;
    uint64_t (*hashfunction)(void*);
    unsigned short nfkeys ;
 	unsigned short memory ;
	unsigned short keytype ;
	short keyads;
	unsigned short datatype ;
	short ads;
}; 

ADSLinkMV(dict,copydict,freedict);

struct AdsDictPair {
	void*key;
	void* data;
};

typedef struct AdsDictPair AdsDictPair;

dict init_dict(int keytype,uint64_t (*hashfunction)(void*),int keyads,int datatype,int size, short ads)
{
	dict d = RawObject(dict);
	size = nextprime(size);
	d->raw = (linklist*)mycalloc(size,sizeof(linklist));
 	d->memory = size;
	d->nfkeys = 0;
	d->datatype = datatype;
	d->ads = ads;
	d->keytype = keytype;
	d->keyads = keyads;
	d->hashfunction = hashfunction;
	return d;
}

short dict_keyads(dict self)
{
	return self->keyads;
}

short dict_getads(dict self)
{
	return self->ads;
}

int ADS_dictgetindex(void*key,uint64_t (*hashfunction)(void*),int capacity)
{
	int index = hashfunction(key)%capacity;
	return index;
}

void ADS_dictreallocation(dict self)
{
	void * tmpkey;
	AdsDictPair tmpADP;
	int newsize = nextprime((self->memory*2)),i,p;
	linklist* h = (linklist*)mycalloc(newsize,sizeof(linklist));
	for(i=0;i<self->memory;i++)
	{
		if(self->raw[i]!=NULL)
		{
			for(p=0; p < linklist_len(self->raw[i]) ;p++)
			{
				tmpADP = linklist_getitem(self->raw[i],p,AdsDictPair);
				tmpkey = tmpADP.key;
				int newindex = ADS_dictgetindex(tmpkey,self->hashfunction,newsize);
				if(h[newindex] == NULL)
				{
					h[newindex] = newlinklist(AdsDictPair);
				}
				linklist_append(h[newindex],tmpADP,AdsDictPair);
			}
			freelinklist(self->raw[i]);
		}
	}
	self->memory = newsize;
	myfree(self->raw);
	self->raw = h;
}

#define dict_haskey(self,key,type) ADS_APPEND(dicthaskey_ByRef,dict_keyads,self,key,type)
bool dicthaskey_ByRef(dict  self,void* key)
{
	int i,p;
	AdsDictPair tmpADP;
	void*tmpkey;
	i = ADS_dictgetindex(key,self->hashfunction,self->memory);
	if(self->raw[i] != NULL)
	{
		for(p=0;p< linklist_len(self->raw[i]) ;p++)
		{
			tmpADP = linklist_getitem(self->raw[i],p,AdsDictPair);
			tmpkey = tmpADP.key;
			if(self->hashfunction(tmpkey) == self->hashfunction(key) )
			{
				return true;
			}
		}
	}
	return false;
}

int dict_len(dict self)
{
	return self->nfkeys;
}

list dict_keys(dict self)
{
	int i,p;
	void* tmpkey;
	AdsDictPair tmpADP;
	list l = init_list(self->keytype,self->nfkeys,self->keyads);
	for(i = 0;i<self->memory;i++)
	{
		if(self->raw[i]!=NULL)
		{
			for(p=0;p< linklist_len(self->raw[i]) ;p++)
			{
				tmpADP = linklist_getitem(self->raw[i],p,AdsDictPair);
				tmpkey = tmpADP.key;
				listappend_ByRef(l,tmpkey);
			}
		}
	}
	return l;
}

list dict_values(dict self)
{
	int i,p;
	AdsDictPair tmpADP;
	void* tmpval;
	list l = init_list(self->datatype,self->nfkeys,self->ads);
	for(i = 0;i<self->memory;i++)
	{
		if(self->raw[i] != NULL)
		{
			for(p=0;p< linklist_len(self->raw[i]) ; p++)
			{
				tmpADP = linklist_getitem(self->raw[i],p,AdsDictPair);
				tmpval = tmpADP.data;
				listappend_ByRef(l,tmpval);
			}
		}
	}
	return l;
}

#define dict_setitem(self,key,value,keytype,valuetype) ADS_KEYVALUE(dictsetitem_ByRef,dict_getads,dict_keyads,self,key,value,keytype,valuetype)
void dictsetitem_ByRef(dict self,void* key,void*value)
{
	double load = (double) self->nfkeys/(double) self->memory;
	if( load >= 0.6000)
	{
		ADS_dictreallocation(self);
	}
	if(key == NULL)
	{
		ValueError("Cannot Set Dict With Null Key");
	}
	AdsDictPair tmpADP,tmpgetADP;
	int index = ADS_dictgetindex(key,self->hashfunction,self->memory);
	if(value != NULL)
	{
		void * ckey = approprite_copy(self->keyads,key,self->keytype);
		void * v = approprite_copy(self->ads,value,self->datatype);
		tmpADP.key = ckey;
		tmpADP.data = v;
		if( self->raw[index] == NULL )
		{
			self->raw[index] = newlinklist(AdsDictPair);
		}
		else
		{
			int i=0;
			void* tmpkey,*tmpval;
			for(i=0 ; i < linklist_len(self->raw[index]) ; i++)
			{
				tmpgetADP = linklist_getitem(self->raw[index],i,AdsDictPair);
				tmpkey = tmpgetADP.key;
				tmpval = tmpgetADP.data;
				if( self->hashfunction(tmpkey) == self->hashfunction(key) )
				{
					linklist_setitem(self->raw[index],i,tmpADP,AdsDictPair);
					appropriate_delete(self->keyads,tmpkey);
					appropriate_delete(self->ads,tmpval);
					return;
				}
			}
		}
		linklist_append(self->raw[index],tmpADP,AdsDictPair);
		self->nfkeys++;
	}
}

#define dict_getitem(self,key,keytype,returntype) ADS_KEYVALUETYPE_NOFREE(dictgetitem_NoCopy_RtnRef,dict_keyads,self,key,keytype,returntype)
void* dictgetitem_NoCopy_RtnRef(dict self,void* key)
{
	AdsDictPair tmpADP;
	int index = ADS_dictgetindex(key,self->hashfunction,self->memory);
	if(self->raw[index] == NULL)
	{
		KeyError("Key '%p' Not Found",key);
	}
	else
	{
		int i;
		for(i=0; i < linklist_len(self->raw[index]) ;i++)
		{
			tmpADP = linklist_getitem(self->raw[index],i,AdsDictPair);
			if( self->hashfunction(tmpADP.key) == self->hashfunction(key) )
			{
				return tmpADP.data ;
			}
		}
		KeyError("Key %p Not Found",key);
	}
}

void* dict_getitem_RtnRef(dict self,void* key)
{
	void* tmpkey;
	AdsDictPair tmpADP;
	int index = ADS_dictgetindex(key,self->hashfunction,self->memory);
	if(self->raw[index] == NULL)
	{
		KeyError("Key %p Not Found",key);
	}
	else
	{
		int i;
		for(i=0;i< linklist_len(self->raw[index]) ;i++)
		{
			tmpADP = linklist_getitem(self->raw[index],i,AdsDictPair);
			tmpkey = tmpADP.key;
			if( self->hashfunction(tmpkey) == self->hashfunction(key) )
			{
				void*v = approprite_copy(self->ads,tmpADP.data,self->datatype);
				return v;
			}
		}
		KeyError("Key %p Not Found",key);
	}
}

#define dict_popitem(self,key,keytype,returntype) ADS_KEYVALUETYPE(dict_popitem_RtnRef,dict_keyads,self,key,keytype,returntype)
void* dict_popitem_RtnRef(dict self,void* key)
{
	int index = ADS_dictgetindex(key,self->hashfunction,self->memory);
	if(self->raw[index] == NULL)
	{
		KeyError("Key '%p' Not Found",key);
	}
	AdsDictPair tmpADP;
	int i;void* tmpkey;
	for(i=0;i< linklist_len(self->raw[index]) ;i++)
	{
		tmpADP = linklist_getitem(self->raw[index],i,AdsDictPair);
		tmpkey = tmpADP.key;
		if( self->hashfunction(tmpkey) == self->hashfunction(key) )
		{
			linklist_delitem(self->raw[index],i);
			appropriate_delete(self->keyads,tmpkey);
			self->nfkeys--;
			return tmpADP.data ;
		}
	}
	KeyError("Key '%p' Not Found",key);
}

#define dict_delitem(self,key,keytype) ADS_APPEND(dictdelitem_ByRef,dict_keyads,self,key,keytype)
void dictdelitem_ByRef(dict self,void* key)
{
	int index = ADS_dictgetindex(key,self->hashfunction,self->memory);
	if(self->raw[index] == NULL)
	{
		KeyError("Key '%p' Not Found",key);
	}
	int i;
	void* tmpkey;
	AdsDictPair tmpADP;
	for(i=0;i< linklist_len(self->raw[index]) ;i++)
	{
		tmpADP = linklist_getitem(self->raw[index],i,AdsDictPair);
		tmpkey = tmpADP.key;
		if( self->hashfunction(tmpkey) == self->hashfunction(key) )
		{
			linklist_delitem(self->raw[index],i);
			appropriate_delete(self->keyads,tmpkey);
			appropriate_delete(self->ads,tmpADP.data);
			self->nfkeys--;
			return ;
		}
	}
	KeyError("Key '%p' Not Found",key);
}

int dict_sizeof(dict self)
{
	int i,cou=0;
	for(i = 0;i<self->memory;i++)
	{
		if(self->raw[i]!=NULL)
		{
			cou += linklist_sizeof(self->raw[i]);
			cou += linklist_len(self->raw[i])*self->keytype;
			cou += linklist_len(self->raw[i])*self->datatype;
		}
	}
	cou += self->memory*sizeof(linklist*);
	cou += sizeof(ADS_StructOf(dict));
	return cou;
}

void dict_extend(dict self,dict other)
{
	if(self->datatype != other->datatype || self->ads != other->ads || self->keytype != other->keytype || self->keyads != other->keyads )
	{
		TypeError("Type Mismatch in dict Extend Function two dicts are for different datatypes");
	}
	list l = dict_keys(other);void * value,*key;
	int i;
	for(i=0;i<list_len(l);i++)
	{
		key = listgetitem_NoCopy_RtnRef(l,i);
		value = dictgetitem_NoCopy_RtnRef(other,key);
		dictsetitem_ByRef(self,key,value);
	}
	freelist(l);
}

void printdict(dict  self,void(*keyprintfunction)(void*),void (*dataprintfunction)(void*))
{
	int i,p;void* tmpkey;void* val;bool fir = true;
	printf("{ ");
	AdsDictPair tmpADP;
	for(i = 0;i<self->memory;i++)
	{
		if(self->raw[i] != NULL)
		{
			for( p = 0 ; p < linklist_len(self->raw[i]) ; p++ )
			{
				if(fir == false) printf(" , ");
				tmpADP = linklist_getitem(self->raw[i],p,AdsDictPair);
				tmpkey = tmpADP.key;
				val = tmpADP.data;
				keyprintfunction(tmpkey);
				printf(" : ");
				dataprintfunction(val);
				fir = false;
			}
		}
	}
	printf(" }");
}

void* copydict(void * _self)
{
	dict self = (dict)_self;
	assert(strcmp(self->type,"dict") == 0);
	dict d = init_dict(self->keytype,self->hashfunction,self->keyads,self->datatype,self->memory,self->ads);
	list  l =  dict_keys(self);
	int i ;void* key;void * value;
	for(i=0;i<list_len(l);i++)
	{
		key = listgetitem_NoCopy_RtnRef(l,i);
		value = dictgetitem_NoCopy_RtnRef(self,key);
		dictsetitem_ByRef(d,key,value);
	}
	freelist(l);
	return d;
}

void dict_clear(dict self)
{
	int i,p;
	AdsDictPair tmpADP;
	for(i=0;i<self->memory;i++)
	{
		if(self->raw[i] != NULL)
		{
			for( p = 0 ; p < linklist_len(self->raw[i]) ; p++ )
			{
				tmpADP = linklist_getitem(self->raw[i],p,AdsDictPair);
				appropriate_delete(self->keyads,tmpADP.key);
				appropriate_delete(self->ads,tmpADP.data);
			}
			freelinklist(self->raw[i]);
			self->raw[i] = NULL;
		}
	}
	self->nfkeys = 0;
}

void freedict(void* _self)
{
	dict self = (dict)_self;
	assert(strcmp(self->type,"dict") == 0);
	int i,p;
	AdsDictPair tmpADP;
	for(i=0;i<self->memory;i++)
	{
		if(self->raw[i] != NULL)
		{
			for( p = 0 ; p < linklist_len(self->raw[i]) ; p++ )
			{
				tmpADP = linklist_getitem(self->raw[i],p,AdsDictPair);
				appropriate_delete(self->keyads,tmpADP.key);
				appropriate_delete(self->ads,tmpADP.data);
			}
			freelinklist(self->raw[i]);
			self->raw[i] = NULL;
		}
	}
	myfree(self->raw);
	myfree(self);
}


#endif
