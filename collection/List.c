
#ifndef ADSLIST_C
#define ADSLIST_C

#include "utility.c"
#include "list.h"

/**
* cointainer of list data item
*/
typedef struct {
	void*data;
} item ;

/**
* List
* 	class declaratoion of the ADS datatype list 
*    	initialise or constructor link to the class
*/
ADSClass(list) 
{  
	ADSinit(list); 
    item* raw;    /*!< pointer to variable size array */
    unsigned short size; /*!< current no of element in it*/
    unsigned short memory; /*!< max no of element the array can hold*/
    unsigned short datatype; /*!< datatype present in elements*/
    short ads; 
}; 

/**
* Links copyconstructor and destructor to the class 
*/
ADSLinkMV(list,copylist,freelist); 

/*!
 \param datatype takes the size of a datatype
 \param size minimum size of the list or vetor array
 \param ads is the storing datatype ADS type
 \see newlist(n,s)
 \return list object
*/
list init_list(int datatype,int size, short ads) 
{
	list l = RawObject(list);
	size = size + 1;
	l->datatype = datatype;
	l->memory = size;
	l->ads = ads;
	l->raw = (item*)mycalloc(size,sizeof(item));
	l->size = 0;
	return l;
}

/*!
   \param self takes a list instance
   \return No of item in the list at present
*/
int list_len(list self) 
{
	return self->size;
}

int list_memory(list self)
{
	return self->memory;
}

short list_getads(list self)
{
	return self->ads;
}

void ADS_list_rellocate(list self)
{
	int newsize;item* tmp;
	if(list_len(self)<5)
	{
		newsize = list_len(self)*3.12;
	}
	else if(list_len(self)>100)
	{
		newsize = list_len(self)*1.5;
	}
	else
	{
		newsize = list_len(self)*2.15;
	}
	tmp = (item*)mycalloc(newsize,sizeof(item));
	if(tmp==NULL)
	{
		MemoryError("In list Reallocte Function");
	}
	tmp = (item*)memcpy(tmp,self->raw,self->size*sizeof(item));
	myfree(self->raw);
	self->raw = tmp;
	self->memory = newsize;
}

/*!
	*insert a element at the end of the list without making a copy
   \param self takes a list instance
   \param value address of the variable to insert
*/
void listappend_NoCopy(list self,void * value) 
{
	int index = self->size;
	if(index>=self->memory-1)
	{
		ADS_list_rellocate(self);
	}
	self->raw[index].data = value;
	self->size++;
}

/*!
	*insert a copy of the element at the end of the list 
	\param self a list instance
	\param value address of the variable to insert
	\see list_append(self,value)
*/
void listappend_ByRef(list self,void * value)
{
	void*val = approprite_copy(self->ads,value,self->datatype);
	listappend_NoCopy(self,val);
}


/*!
   \param self a list instance
   \param index a integer position 
   \see listgetitem_NoCopy(self,index,type)
   \return address of the element stored at that position 
*/
void* listgetitem_NoCopy_RtnRef(list self,int index) 
{
	if(index>=self->size||index<0)
	{
		IndexError("in listgetitem function with index %d ",index);
	}
	return self->raw[index].data;
}


/*!
   \param self a list instance
   \param index a integer position 
   \see list_getitem(self,index,type)
   \return address of the copied element stored at that position 
*/
void* list_getitem_RtnRef(list self,int index) 
{
	void * v;
	if(index>=self->size||index<0)
	{
		IndexError("in listgetitem function with index %d ",index);
	}
	v =  approprite_copy(self->ads,self->raw[index].data,self->datatype);
	return v;
}

/*!
   \param self a list instance
   \param index a integer position 
   \param address of the variable which will overwrite the current value
   \see list_setitem(self,index,value)
*/
void listsetitem_ByRef(list self,int index,void*value)
{
	if(index>=self->size||index<0)
	{
		IndexError("in listgetlength function with index %d ",index);
	}
	if(value == NULL)
	{
		ValueError("Cannot set null value to the list");
	}
	if (self->raw[index].data != NULL )
	{
		appropriate_delete(self->ads,self->raw[index].data);
	}
	self->raw[index].data = approprite_copy(self->ads,value,self->datatype);
}

/*!
   \param self a list instance
   \param index a integer position 
   \param address of the variable which will be inserted
   \see list_insert(self,index,value)
*/
void listinsert_ByRef(list self,int index,void*value)
{
	int i;
	if(index>=self->size||index<0)
	{
		IndexError("in listgetlength function with index %d ",index);
	}
	if(value == NULL)
	{
		ValueError("Cannot set null value to the list");
	}
	if(self->size >=self->memory-1)
	{
		ADS_list_rellocate(self);
	}
	for(i=self->size-1;i>=index;i--)
	{
		self->raw[i+1].data = self->raw[i].data;
		self->raw[i].data = NULL;
	}
	listsetitem_ByRef(self,index,value);
	self->size++;
}

/*!
	*append all elements in other list to self list
   \param self a list instance
   \param other a list instance
*/
void list_extend(list self,list other)
{
	int le,i;
	if(self->datatype != other->datatype)
	{
		TypeError("Type mismatch of two list in list extend");
	}
	le = list_len(other);
	for(i=0;i<le;i++)
	{
		listappend_ByRef(self,listgetitem_NoCopy_RtnRef(other,i));
	}
}

void __list_swap(list self,int index1,int index2)
{
	void *tmp;
	if(index1>=self->size||index1<0)
	{
		IndexError("in listgetlength function with index %d ",index1);
	}
	if(index2>=self->size||index2<0)
	{
		IndexError("in listgetlength function with index %d ",index2);
	}
	tmp = self->raw[index1].data;
	self->raw[index1].data = self->raw[index2].data;
	self->raw[index2].data = tmp;
}


void list_reverse(list self)
{
	int size = list_len(self)-1,i;
	for(i=0; i <= (size-1)>>1 ;i++)
	{
		__list_swap(self,i,size-i);
	}
}

/*!
   \param self a list instance
   \param index a integer position
*/
void list_delitem(list self,int index)
{
	int i;
	if(index>=self->size||index<0)
	{
		IndexError("in listgetitem function with index %d ",index);
	}
	appropriate_delete(self->ads,self->raw[index].data);
	i = index;
	for(i=index;i<self->size;i++)
	{
		self->raw[i].data = self->raw[i+1].data;
		self->raw[i+1].data = NULL;
	}
	self->size--;
}

void* listpop_RtnRef(list self)
{
	void* v = list_getitem_RtnRef(self,0);
	list_delitem(self,0);
	return v;
}

void list_shrink(list self)
{
	int newsize = list_len(self);
	item* tmp = (item*)mycalloc(newsize,sizeof(item));
	if(tmp==NULL)
	{
		MemoryError("In List Shrink Function");
	}
	tmp = (item*)memcpy(tmp,self->raw,self->size*sizeof(item));
	myfree(self->raw);
	self->raw = tmp;
	self->memory = newsize;
}

void list_map(list self,void(*function)(void*value))
{
	int i,l = list_len(self);
	for(i=0;i<l;i++)
	{
		function(listgetitem_NoCopy_RtnRef(self,i));
	}
}

void* __listiterstart(iterator* i)
{
	list s = (list)i->object;
	return listgetitem_NoCopy_RtnRef(s,i->count);
}

void* __listiternext(iterator* i)
{
	list s = (list)i->object;
	i->max = (unsigned)list_len(s);
	if((unsigned)list_len(s)>i->count)
	{
		return listgetitem_NoCopy_RtnRef(s,i->count);
	}
	return NULL;;
}

iterator list_iterator(list self)
{
	iterator i = newiterator(self,__listiternext,__listiterstart,list_len(self),NULL);
	return i;
}

void printlist(list self,void(*print)(void*value))
{
	int i,l = list_len(self);
	printf("[ ");
	for(i=0;i<l;i++)
	{
		print(listgetitem_NoCopy_RtnRef(self,i));
		if(i!=l-1)
		{
			printf(" , ");
		}
	}
	printf(" ]");
}

void* copylist(void *l)
{
	list self = (list)l;
	list  nwlst = init_list(self->datatype,self->size,self->ads);
	int len = ((list)l)->size,i ;
	for(i=0;i<len;i++)
	{
		listappend_ByRef(nwlst,listgetitem_NoCopy_RtnRef(((list)l),i));
	}
	return nwlst;
}

void list_clear(list l ) 
{
	list self = (list)l;
	int i ;
	for(i=0;i<self->size;i++)
	{
		appropriate_delete(self->ads,self->raw[i].data);
		self->raw[i].data = NULL;
	}
	l->size = 0;
}

void freelist(void* l )
{
	list self = (list)l;
	int i ;
	for(i=0;i<self->size;i++)
	{
		appropriate_delete(self->ads,self->raw[i].data);
	}
	myfree(self->raw);
	myfree(self);
}

int listindex_ByRef(list self,void *value,int (*compare)(void*,void*))
{
	int i ;
	for(i=0;i<self->size;i++)
	{
		int c = appropriate_compare(compare,value,listgetitem_NoCopy_RtnRef(self,i),self->datatype);
		if(c == 0)
		{
			return i;
		}
	}
	return -1;
}

int listcount_ByRef(list self,void * value,int (*compare)(void*,void*))
{
	int i,cou=0 ;
	for(i=0;i<self->size;i++)
	{
		int c = appropriate_compare(compare,value,listgetitem_NoCopy_RtnRef(self,i),self->datatype);
		if(c == 0)
		{
			cou++;
		}
	}
	return cou;
}

void listremove_ByRef(list self,void * value,int (*compare)(void*,void*))
{
	int i ;
	for(i=0;i<self->size;i++)
	{
		int c ;
		c = appropriate_compare(compare,value,listgetitem_NoCopy_RtnRef(self,i),self->datatype);
		if(c == 0)
		{
			list_delitem(self,i);
			i--;
		}
	}
}

void list_sort(list self,int (*compare)(void*,void*))
{
	int i,p;void * curr;
    for(i=1;i<self->size;i++)
    {
        curr = self->raw[i].data ;
        for(p=i-1;p>=0;p--)
        {
        	int c = appropriate_compare(compare,self->raw[p].data,curr,self->datatype);
            if(c == -1)
            break;
            self->raw[p+1].data = self->raw[p].data;
        }
        self->raw[p+1].data = curr;
    }
}

int listbinarysearch_ByRef(list self,void * value ,int (*compare)(void*,void*) ) 
{
    int high = self->size-1,low=0,ai=0,index;
    list_sort(self,compare);
    while((high>low)&& (high-low != 0)&& (high-low != 1))
    {
        index= (high-low)/2;
    	int c1 = compare(value,self->raw[high].data),
    	c2 = compare(value,self->raw[low].data);
   		if(c2==0) return low;
   		if(c1==0 ) return high;
        c1 = compare(value,self->raw[high].data),
        c2 = compare(value,self->raw[low].data);
        if(c1 == 1||c2 == -1 )return -1;
        ai = low + index;
        c1 = compare(value,self->raw[ai].data);
        if(c1 == 0) return ai;
        else if(c1 == -1) high = ai;
        else if(c1 == 1) low = ai;
    }
    return -1;
}

void ADS__builtList(list self,void*arr,int n)
{
	int i;char * c = (char*)arr;int datatype = self->datatype;
	for(i = 0;i<n;i++)
	{
		void * val = c;
		val = evaluate_pointer(self->ads,(void**)val);
		listappend_ByRef(self,val);
		c = (c+datatype);
	}
}

#endif
