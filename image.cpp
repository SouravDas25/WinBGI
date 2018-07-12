


#ifndef GRAPHICSDOTHIMAGECOMPRESSION_H
#define GRAPHICSDOTHIMAGECOMPRESSION_H

#include "HF.cpp"

extern turbograph __Current;

typedef struct {
	char color;
	bool endofline;
	short size;
}runlength;

unsigned int imagesize(int left, int top, int right, int bottom)
{
	int x , y,size=0,prevcolor = -1,clr ;
	for(y=top;y<=bottom;y++)
	{
		prevcolor = -1;
		for(x=left;x<=right;x++)
		{
			clr = getpixel(x,y);
			if(clr != prevcolor)
			{
				size += sizeof(runlength) ;
			}
			prevcolor = clr;
		}
	}
	return size+sizeof(int);
}

int bgigetopcolor(int x,int y,int color,int op)
{
	switch(op)
	{
		case COPY_PUT : return color;
		case XOR_PUT : return color^getpixel(x,y);
		case OR_PUT : return color|getpixel(x,y);
		case AND_PUT : return color&getpixel(x,y);
		case NOT_PUT : return !color;
		default : return color;
	}
}

void putimage(int left, int top, const void *bitmap,int op)
{
	int * bit = (int*)bitmap;
	int size = bit[0];
	runlength * rbit = (runlength*)bitmap;
	rbit++;
	int i,p,y=top,x=left;
	for(i = 0 ;i<size;i++)
	{
		for(p=0;p<rbit->size;p++)
		{
			putpixel(x,y,bgigetopcolor(x,y,rbit->color,op));
			x++;
		}
		if(rbit->endofline == true)
		{
			y++;
			x=left;
		}
		rbit++;
	}
}

runlength* getlinebuffer(int left,int right,int y , runlength* rbit,int * size )
{
	int x = left,prevcolor = -1,clr,cnt = 1;
	rbit++;
	*size += 1;
	prevcolor = getpixel(x,y);
	rbit->color = prevcolor;
	rbit->endofline = false;
	for(x=left+1;x<=right;x++)
	{
		clr = getpixel(x,y);
		if(clr != prevcolor )
		{
			rbit->size = cnt;
			cnt = 1;
			rbit++;
			*size += 1;
			rbit->color = clr;
			rbit->endofline = false;
		}
		else cnt++;
		prevcolor = clr;
	}
	rbit->size = cnt;
	rbit->endofline = true;
	return rbit;
}

void getimage(int left, int top, int right, int bottom,void * bitmap)
{
	int * bit = (int*)bitmap;
	runlength * rbit = (runlength*)bitmap;
	int  y,size = 0 ;
	for(y=top;y<=bottom;y++)
	{
		rbit = getlinebuffer(left,right,y,rbit,&size);
	}
	bit[0] = size;
}

#endif

