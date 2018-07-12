

#ifndef AVLTREE_C
#define AVLTREE_C


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utility.c"
#include "Avl.h"
#include "list.c"


ADSClass(Avltree)
{
	ADSinit(Avltree);
    int (*compare)(void *,void*) ;
	treenode* root;
	unsigned short datatype;
	unsigned short keytype;
	unsigned short height;
	unsigned short size;
	short ads;
	short keyads;
};

ADSLinkMV(Avltree,copyAvltree,freeAvltree);

struct treenode
{
	void * key;
	void * data;
	struct treenode * left;
	struct treenode *right;
	struct treenode *parent;
};

typedef struct treenode treenode;

void __treerotate(Avltree self,treenode*tn,bool direction);
void __treedoublerotate(Avltree self,treenode*tn,bool direction);
int __getlongestheight(treenode*tn);

Avltree init_Avltree(int keytype, int (*compare)(void * data1,void*data2),int datatype,short ads,short keyads)
{
	Avltree t = RawObject(Avltree);
	checkMemory(t);
	t->height = 0;
	t->size = 0;
	t->root = NULL;
	t->keytype  = keytype;
	t->datatype = datatype;
	t->compare = compare;
	t->ads = ads;
	t->keyads = keyads;
	return t;
}

short Avltree_getads(Avltree self)
{
	return self->ads;
}

short Avltree_getKeyads(Avltree self)
{
	return self->keyads;
}

void __treerotate(Avltree self,treenode*tn,bool direction)
{
	if(tn== NULL)
	{
		return;
	}
	treenode*parent = tn->parent,*child;
	if(direction == LEFT)
	{
		child = tn->left;
		tn->left = child->right;
		if(child->right != NULL)
		child->right->parent = tn;
		child->right = tn;
		child->parent = tn->parent;
		tn->parent = child;
	}
	else if(direction == RIGHT)
	{
		child = tn->right;
		tn->right = child->left;
		if(child->left != NULL)
		child->left->parent = tn;
		child->left = tn;
		child->parent = tn->parent;
		tn->parent = child;
	}
	if(parent == NULL)
	{
		self->root = child;
		return;
	}
	if(parent->left == tn)
	{
		parent->left = child;
	}
	else if(parent->right == tn)
	{
		parent->right = child;
	}
}

void __treedoublerotate(Avltree self,treenode*tn,bool direction)
{
	if(direction == LEFT)
	{
		__treerotate(self,tn->left,RIGHT);
		__treerotate(self,tn,LEFT);
	}
	else if(direction == RIGHT)
	{

		__treerotate(self,tn->right,LEFT);
		__treerotate(self,tn,RIGHT);
	}
}

int __getlongestheight(treenode*tn)
{
	int r=0,l=0;
	if(tn->right)
	{
		r = __getlongestheight(tn->right)+1;
	}
	if(tn->left)
	{
		l = __getlongestheight(tn->left)+1;
	}
	if(r>l) return r;
	else if (r == l) return r;
	else return l;
}

int __getleftheight(treenode*tn)
{
	if(tn->left)
	{
		return __getlongestheight(tn->left)+1;
	}
	return 0;
}

int __getrightheight(treenode*tn)
{
	if(tn->right)
	{
		return __getlongestheight(tn->right)+1;
	}
	return 0;
}

void __balancetreenode( Avltree self,treenode*tn)
{
	int hl = 0,hr=0;treenode*trav = tn->left;
	while(trav!= NULL)
	{
		trav = trav->left;
		hl++;
	}
	trav = tn->right;
	while(trav!= NULL)
	{
		trav = trav->right;
		hr++;
	}
	int l = __getleftheight(tn),r = __getrightheight(tn);
	if(l>r+1 && hl<l)
	{
		__treedoublerotate(self,tn,LEFT);
	}
	else if(r>l+1 && hr <r)
	{
		__treedoublerotate(self,tn,RIGHT);
	}
	else if(l>r+1)
	{
		__treerotate(self,tn,LEFT);
	}
	else if(r>l+1)
	{
		__treerotate(self,tn,RIGHT);
	}
}

int counttreestack = 0;
void __treenode2array(treenode * tn,treenode ** arr )
{
	if(tn)
	{
		arr[counttreestack++] = tn;
	}
	if(tn->left)
	{
		__treenode2array(tn->left,arr);
	}
	if(tn->right)
	{
		__treenode2array(tn->right,arr);
	}
}

void balanceAvltree( Avltree self)
{
	if(self->root == NULL) return;
	int i;
	counttreestack = 0;
	treenode * arr[self->size+1];
	__treenode2array(self->root,arr);
	treenode*trav;
	for(i =0;i<self->size;i++)
	{
		trav = arr[i];
		__balancetreenode(self,trav);
	}
	for(i =0;i<self->size;i++)
	{
		trav = arr[i];
		__balancetreenode(self,trav);
	}
}

int Avltree_len(Avltree self)
{
	return self->size;
}


void Avltreeinsert_ByRef(Avltree self,void*key,void* value)
{
	treenode*tn = (treenode*)mycalloc(1,sizeof(treenode));
	tn->data = approprite_copy(self->ads,value,self->datatype);
	tn->key = approprite_copy(self->keyads,key,self->keytype);
	self->size++;
	if(self->root == NULL)
	{
		self->root = tn;
		self->height++;
	}
	else
	{
		treenode*trav = self->root;
		while(trav != NULL)
		{
			if(appropriate_compare(self->compare,tn->key,trav->key,self->keytype) <= 0)
			{
				if(trav->left)
				{
					trav = trav->left;
					continue;
				}
				else
				{
					tn->parent = trav;
					trav->left = tn;
					break;
				}
			}
			else if(appropriate_compare(self->compare,tn->key,trav->key,self->keytype) > 0)
			{
				if(trav->right)
				{
					trav = trav->right;
					continue;
				}
				else
				{
					tn->parent = trav;
					trav->right = tn;
					break ;
				}
			}
		}
	}
	treenode*trav = tn;
	while(trav != NULL)
	{
		__balancetreenode(self,trav);
		trav = trav->parent;
	}
}

treenode * __getnode(Avltree self,void*key)
{
	treenode*trav = self->root;
	while(trav != NULL)
	{
		if(appropriate_compare(self->compare,key,trav->key,self->keytype)  == 0)
		{
			return trav;
		}
		if(trav->left)
		{
			if(appropriate_compare(self->compare,key,trav->key,self->keytype) < 0)
			{
				trav = trav->left;
				continue;
			}
		}
		if(trav->right)
		{
			if( appropriate_compare(self->compare,key,trav->key,self->keytype) > 0)
			{
				trav = trav->right;
				continue;
			}
		}
		break;
	}
	return NULL;
}

bool Avltreecontains_ByRef(Avltree self,void*key)
{
	treenode * j = __getnode(self,key);
	if(j!=NULL) return true;
	return false;
}

int __getnoofchild(treenode*tn)
{
	int i = 0;
	if(tn->left != NULL)
	{
		i++;
	}
	if(tn->right != NULL)
	{
		i++;
	}
	return i;
}


void Avltreedelete_ByRef(Avltree self,void*key)
{
	if(self->root == NULL) return;
	treenode*node = __getnode(self,key);
	if(node == NULL)
	{
		KeyError("Key Provided at address '%p' is not found in tree ",key);
	}
	treenode*parent = node->parent;
	int nc = __getnoofchild(node);
	if(nc==0)
	{
		if(parent == NULL)
		{
			self->root = NULL;
		}
		else
		{
			if(parent->left == node)
			{
				parent->left = NULL;
			}
			else if(parent->right == node)
			{
				parent->right = NULL;
			}
			else
			{
				ValueError("Parent mismatch in deletefunction of treenode");
			}
		}
	}
	else if(nc==1)
	{
		if(node->left)
		{
			if(parent == NULL)
			{
				self->root = node->left;
				node->left->parent =parent;
			}
			else if(parent->left == node)
			{
				parent->left = node->left;
				node->left->parent =parent;
			}
			else if(parent->right == node)
			{
				parent->right = node->left;
				node->left->parent =parent;
			}
			else
			{
				ValueError("Parent mismatch in deletefunction of treenode");
			}
		}
		else if(node->right)
		{
			if(parent == NULL)
			{
				self->root = node->right;
				node->right->parent =parent;
			}
			else if(parent->left == node)
			{
				parent->left = node->right;
				node->right->parent =parent;
			}
			else if(parent->right == node)
			{
				parent->right = node->right;
				node->right->parent = parent;
			}
			else
			{
				ValueError("Parent mismatch in deletefunction of treenode");
			}
		}
		else
		{
			SystemError("Nodecount dosn't match with the node");
		}
	}
	else if(nc == 2)
	{
		treenode*leastnode=node->left,*lparent ;
		while(leastnode->right != NULL)
		{
			leastnode = leastnode->right;
		}
		appropriate_delete(self->ads,node->data);
		appropriate_delete(self->keyads,node->key);
		node->data = leastnode->data;
		node->key = leastnode->key;
		lparent = leastnode->parent;
		if(lparent->right == leastnode )
		{
			if(leastnode->left)
			{
				lparent->right = leastnode->left;
				leastnode->left->parent = lparent;
			}
			else
			{
				lparent->right = NULL;
			}
		}
		else if(lparent->left == leastnode)
		{
			if(leastnode->left)
			{
				lparent->left = leastnode->left;
				leastnode->left->parent = lparent;
			}
			else
			{
				lparent->left = NULL;
			}
		}
		self->size--;
		treenode*trav = leastnode->parent;
		myfree(leastnode);
		while(trav != NULL)
		{
			__balancetreenode(self,trav);
			trav = trav->parent;
		}
		return;
	}
	appropriate_delete(self->ads,node->data);
	appropriate_delete(self->keyads,node->key);
	treenode*trav = node->parent;
	myfree(node);
	self->size--;
	while(trav != NULL)
	{
		__balancetreenode(self,trav);
		trav = trav->parent;
	}
}

void __freenode(treenode*tn,Avltree self)
{
	appropriate_delete(self->ads,tn->data) ;
	appropriate_delete(self->keyads,tn->key);
	if(tn->left)
	{
		__freenode(tn->left,self);
	}
	if(tn->right)
	{
		__freenode(tn->right,self);
	}
	myfree(tn);
}

void freeAvltree(void* _self)
{
	Avltree self =(Avltree)_self;
	assert( strcmp(self->type,"Avltree") == 0 ) ;
	if(self->root != NULL)
	__freenode(self->root,self);
	myfree(self);
}

void __printnode(treenode* tn,const char* buf,void (*keyprintfunction)(void*),void (*dataprintfunction)(void*))
{
	int n = strlen(buf);
	char b[n+5];
	printf(buf);
	strcpy(b,buf);
	keyprintfunction(tn->key);
	printf(": ");
	dataprintfunction(tn->data);
	printf("\n");
	if(tn->left && tn->right)
	{
		int l=-1;
		while(b[++l] != EndOfStr) if(b[l] != '\xb3')(b[l] == '\xc3') ? b[l] = '\xb3' : (b[l] = ' ') ;
		strcat(b,"\xc3\xc4\xc4");
		__printnode(tn->left,b,keyprintfunction,dataprintfunction);
		b[n] = '\xc0';
		__printnode(tn->right,b,keyprintfunction,dataprintfunction);
	}
	else if(tn->left || tn->right)
	{
		if(tn->left)
		{
			int l=-1;
			while(b[++l]!= EndOfStr) if(b[l] != '\xb3')(b[l] == '\xc3') ? b[l] = '\xb3' : (b[l] = ' ') ;
			strcat(b,"\xc0\xc4\xc4");
			__printnode(tn->left,b,keyprintfunction,dataprintfunction);
		}
		if(tn->right)
		{
			int l=-1;
			while(b[++l]!= EndOfStr) if(b[l] != '\xb3')(b[l] == '\xc3') ? b[l] = '\xb3' : (b[l] = ' ') ;
			strcat(b,"\xc0\xc4\xc4");
			__printnode(tn->right,b,keyprintfunction,dataprintfunction);
		}
	}
}

void printAvltree(Avltree self,void (*keyprintfunction)(void*),void (*dataprintfunction)(void*))
{
	printf("AVL Tree : \n\n");
	if(self->root != NULL) __printnode(self->root,"  ",keyprintfunction,dataprintfunction);
	printf("\n");
}

void __copynode(Avltree other,treenode* tn )
{
	Avltreeinsert_ByRef(other,tn->key,tn->data);
	if(tn->left)
	{
		__copynode(other,tn->left);
	}
	if(tn->right)
	{
		__copynode(other,tn->right);
	}
}

void * copyAvltree(void * _self)
{
	Avltree self = (Avltree)_self;
	Avltree t = init_Avltree(self->keytype,self->compare,self->datatype,self->ads,self->keyads);
	if(self->root != NULL) __copynode(t,self->root);
	return t;
}

void __treenode_traversal(list l , treenode * tn,int order,bool keyordata)
{
	if(order == INORDER)
	{
		if(tn->left)__treenode_traversal(l,tn->left,order,keyordata);
		if(keyordata) listappend_ByRef(l,tn->key);
		else listappend_ByRef(l,tn->data);
		if(tn->right)__treenode_traversal(l,tn->right,order,keyordata);
	}
	else if(order == PREORDER)
	{
		if(keyordata) listappend_ByRef(l,tn->key);
		else listappend_ByRef(l,tn->data);
		if(tn->left)__treenode_traversal(l,tn->left,order,keyordata);
		if(tn->right)__treenode_traversal(l,tn->right,order,keyordata);
	}
	else
	{
		if(tn->left)__treenode_traversal(l,tn->left,order,keyordata);
		if(tn->right)__treenode_traversal(l,tn->right,order,keyordata);
		if(keyordata) listappend_ByRef(l,tn->key);
		else listappend_ByRef(l,tn->data);
	}
}

list Avltree_traversal(Avltree self,int order,bool keyordata)
{
	list l = (keyordata)?init_list(self->keytype ,self->size ,self->keyads):init_list(self->datatype ,self->size ,self->ads);
	__treenode_traversal(l,self->root,order,keyordata);
	return l;
}


#endif



