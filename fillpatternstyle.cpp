


#ifndef GRAPHICSFILLPATTERN_H
#define GRAPHICSFILLPATTERN_H

#include "HF.cpp"
#include "utility.cpp"
#include "collection\stack.c"
#include "collection\linklist.c"
#include "misc.cpp"
#include "lines.cpp"

#define maxpatternbit 8

char emptyfillarray[8][8]={{0,0,0,0,0,0,0,0},
						   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0}};
					 	   
char solidfillarray[8][8]={{1,1,1,1,1,1,1,1},
						   {1,1,1,1,1,1,1,1},
						   {1,1,1,1,1,1,1,1},
					 	   {1,1,1,1,1,1,1,1},
					 	   {1,1,1,1,1,1,1,1},
					 	   {1,1,1,1,1,1,1,1},
					 	   {1,1,1,1,1,1,1,1},
					 	   {1,1,1,1,1,1,1,1}};

char linefillarray[8][8]= {{1,1,1,1,1,1,1,1},
						   {0,0,0,0,0,0,0,0},
					 	   {1,1,1,1,1,1,1,1},
					 	   {0,0,0,0,0,0,0,0},
					 	   {1,1,1,1,1,1,1,1},
					 	   {0,0,0,0,0,0,0,0},
					 	   {1,1,1,1,1,1,1,1},
					 	   {0,0,0,0,0,0,0,0}};
					 	   
char ltslashfillarray[8][8]=  {{0,0,0,1,0,0,0,1},
							   {0,0,1,0,0,0,1,0},
						 	   {0,1,0,0,0,1,0,0},
						 	   {1,0,0,0,1,0,0,0},
						 	   {0,0,0,1,0,0,0,1},
						 	   {0,0,1,0,0,0,1,0},
						 	   {0,1,0,0,0,1,0,0},
						 	   {1,0,0,0,1,0,0,0}};
					 	   	 
char slashfillarray[8][8]=    {{1,0,0,0,0,0,1,1},
							   {0,0,0,0,0,1,1,1},
						 	   {0,0,0,0,1,1,1,0},
						 	   {0,0,0,1,1,1,0,0},
						 	   {0,0,1,1,1,0,0,0},
						 	   {0,1,1,1,0,0,0,0},
						 	   {1,1,1,0,0,0,0,0},
						 	   {1,1,0,0,0,0,0,1}};
					 	   	
char ltbkslashfillarray[8][8]={{1,0,0,0,1,0,0,0},
							   {0,1,0,0,0,1,0,0},
						 	   {0,0,1,0,0,0,1,0},
						 	   {0,0,0,1,0,0,0,1},
						 	   {1,0,0,0,1,0,0,0},
						 	   {0,1,0,0,0,1,0,0},
						 	   {0,0,1,0,0,0,1,0},
						 	   {0,0,0,1,0,0,0,1}};

char bkslashfillarray[8][8]=  {{1,1,0,0,0,0,0,1},
							   {1,1,1,0,0,0,0,0},
						 	   {0,1,1,1,0,0,0,0},
						 	   {0,0,1,1,1,0,0,0},
						 	   {0,0,0,1,1,1,0,0},
						 	   {0,0,0,0,1,1,1,0},
						 	   {0,0,0,0,0,1,1,1},
						 	   {1,0,0,0,0,0,1,1}};

char hatchfillarray[8][8]=	  {{0,0,0,0,1,0,0,0},
							   {0,0,0,0,1,0,0,0},
						 	   {0,0,0,0,1,0,0,0},
						 	   {0,0,0,0,1,0,0,0},
						 	   {1,1,1,1,1,1,1,1},
						 	   {0,0,0,0,1,0,0,0},
						 	   {0,0,0,0,1,0,0,0},
						 	   {0,0,0,0,1,0,0,0}};
					 	   
char xhatchfillarray[8][8]=	  {{0,0,0,1,1,0,0,0},
							   {0,0,0,1,1,0,0,0},
						 	   {0,0,0,1,1,0,0,0},
						 	   {1,1,1,1,1,1,1,1},
						 	   {1,1,1,1,1,1,1,1},
						 	   {0,0,0,1,1,0,0,0},
						 	   {0,0,0,1,1,0,0,0},
						 	   {0,0,0,1,1,0,0,0}};

char interleavefillarray[8][8]=   {{1,0,0,0,0,0,0,1},
								   {0,1,0,0,0,0,1,0},
							 	   {0,0,1,0,0,1,0,0},
							 	   {0,0,0,1,1,0,0,0},
							 	   {0,0,0,1,1,0,0,0},
							 	   {0,0,1,0,0,1,0,0},
							 	   {0,1,0,0,0,0,1,0},
							 	   {1,0,0,0,0,0,0,1}};

char widedotfillarray[8][8]=  {{0,0,0,0,0,0,0,0},
							   {0,1,1,0,0,1,1,0},
						 	   {0,1,1,0,0,1,1,0},
						 	   {0,0,0,0,0,0,0,0},
						 	   {0,0,0,0,0,0,0,0},
						 	   {0,1,1,0,0,1,1,0},
						 	   {0,1,1,0,0,1,1,0},
						 	   {0,0,0,0,0,0,0,0}};

char closedotfillarray[8][8]= {{0,1,1,0,0,1,1,0},
							   {1,0,0,1,1,0,0,1},
						 	   {1,0,0,1,1,0,0,1},
						 	   {0,1,1,0,0,1,1,0},
						 	   {0,1,1,0,0,1,1,0},
						 	   {1,0,0,1,1,0,0,1},
						 	   {1,0,0,1,1,0,0,1},
						 	   {0,1,1,0,0,1,1,0}};
						 	   
char userfillarray[8][8]= {{0,0,0,0,0,0,0,0},
						   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0},
					 	   {0,0,0,0,0,0,0,0}};
					 
bool getfillarray(int x,int y,char*array)
{
	return *(array+y*maxpatternbit+x);
}

int fillarray2points(char * array,pointtype * parray )
{
	int x,y ,count = 0;
	for(y=0;y<maxpatternbit;y++)
	{
		for(x = 0;x<maxpatternbit;x++)
		{
			if( *(array+y*maxpatternbit+x) == 1)
			{
				parray[count].x = x;
				parray[count].y = y;
				count++;
			}
		}
	}
	return count;
}

void setfillpattern(const unsigned char *upattern, int color)
{
	int x,y;char patrn,bit;
	for(y=0;y<maxpatternbit;y++)
	{
		patrn = upattern[y];
		for(x=0;x<maxpatternbit;x++)
		{
			bit = (patrn >> x)&0x1;
			if(bit) userfillarray[y][x] = 1;
		}
	}
	setfillstyle(USER_FILL,color);
}

char * getpatternarray(BYTE pattern)
{
	char * array;
	switch(pattern)
	{
		case EMPTY_FILL : {
			array = &emptyfillarray[0][0];
			break;
		}
		case SOLID_FILL : {
			array = &solidfillarray[0][0];
			break;
		}
		case LINE_FILL :{
			array = &linefillarray[0][0];
			break;
		}
		case LTSLASH_FILL : {
			array = &ltslashfillarray[0][0];
			break;
		}
		case SLASH_FILL : {
			array = &slashfillarray[0][0];
			break;
		}
		case BKSLASH_FILL : {
			array = &bkslashfillarray[0][0];
			break;
		}
		case LTBKSLASH_FILL : {
			array = &ltbkslashfillarray[0][0];
			break;
		}
		case WIDE_DOT_FILL : {
			array = &widedotfillarray[0][0];
			break;
		}
		case CLOSE_DOT_FILL : {
			array = &closedotfillarray[0][0];
			break;
		}
		case HATCH_FILL : {
			array = &hatchfillarray[0][0];
			break;
		}
		case XHATCH_FILL : {
			array = &xhatchfillarray[0][0];
			break;
		}
		case INTERLEAVE_FILL : {
			array = &interleavefillarray[0][0];
			break;
		}
		case USER_FILL : {
			array = &userfillarray[0][0];
			break;
		}
	}
	return array;
}

void getfillpattern(char * pattern)
{
	int i,p;char bit;
	char * array = getpatternarray(Internalgetfillpattern());
	for(i=0;i<8;i++)
	{
		bit = 0 ;
		for(p=0;p<8;p++)
		{
			bool b = getfillarray(i,p,array);
			bit <<= 1;
			bit |= b;
		}
		pattern[i] = bit;
	}
}

void getfillsettings(struct fillsettingstype *fillinfo)
{
	fillinfo->pattern = Internalgetfillpattern();
	fillinfo->color = getfillcolor();
}

typedef struct floodpoint {
	pointtype absolute, relative;
} floodpoint ;

int xrelative8x8(int x)
{
	if(x >= 8 ) return x%8;
	if(x < 0 ) return 8+x;
	return x;
}

int yrelative8x8(int y)
{
	if(y >= 8 ) return y%8;
	if(y < 0 ) return 8+y;
	return y;
}

void DrawBorder(int color)
{
	struct linesettingstype pls; 
	getlinesettings(&pls);
	setlinestyle(SOLID_LINE,0,pls.thickness);
	int xmax = getmaxx()-1;
	int ymax = getmaxy()-1;
	int c = getcolor();
	int st = 1;
	setcolor(color);
	line(st,st,xmax,st);
	line(xmax,st,xmax,ymax);
	line(xmax,ymax,st,ymax);
	line(st,ymax,st,st);
	setcolor(c);
	setlinestyle(pls.linestyle,pls.upattern,pls.thickness);
}

int getXmax(int y,int x,linklist ybucket)
{
	ads_foreach(l,linklist_iterator(ybucket),linklist)
	{
		int vy = linklistgetitem_NoCopy(l,0,int);
		if(vy == y)
		{
			int x1 = linklistgetitem_NoCopy(l,1,int);
			int x2 = linklistgetitem_NoCopy(l,2,int);
			if( x<=x2 && x>=x1 )
			{
				return x2;
			}
		}
	}ads_next(l);
	return x;
}

bool isybucketthere(int y,int x,linklist ybucket)
{
	ads_foreach(l,linklist_iterator(ybucket),linklist)
	{
		int vy = linklistgetitem_NoCopy(l,0,int);
		if(vy == y)
		{
			int x1 = linklistgetitem_NoCopy(l,1,int);
			int x2 = linklistgetitem_NoCopy(l,2,int);
			if( x<=x2 && x>=x1 )
			{
				return true;
			}
		}
	}ads_next(l);
	return false;
}

void printlistoflist(void * a)
{
	printf("\n");
	printlinklist(cast(a,linklist),printint);
}

void insert2ybucket(int y,int x1,int x2 ,linklist ybucket)
{
	linklist yl = newlinklist(int);
	builtlinklist(yl,int,y,x1,x2);
	linklist_append(ybucket,yl,linklist);
	freelinklist(yl);
}

void floodfillputpixel(int x, int y,int relx,int rely,char * array)
{
	int arrayval = getfillarray(relx,rely,array);
	if( arrayval == 1 )
	{
		putpixel( x,y,getfillcolor() );
	}
}

int calculateRelx(int xnew,int xold,int relxold)
{
	return (relxold + ( abs(xnew-xold) %8) )%8;
}

void floodfillscanline(int x,int y,int relx,int rely,int xright ,int bordercolor,stack floodfillstack,linklist ybucket)
{
	int pixelcor;
	while(x <= xright)
	{
		bool pflag = 0;
		int xstart = x;
		pixelcor = getpixel(x,y);
		while( (pixelcor != bordercolor) && ( pixelcor != getfillcolor() ) &&  ( x < xright ) )
		{
			pflag = 1;
			if( isybucketthere(y,x,ybucket) )
			{
				int tx = getXmax(y,x,ybucket);
				x = tx;
				pflag = 0;
			}
			x++;
			pixelcor = getpixel(x,y);
		}
		relx = calculateRelx(x,xstart,relx);
		if(pflag)
		{
			pixelcor = getpixel(x,y);
			if((x == xright) && (pixelcor != bordercolor) && (pixelcor != getfillcolor()) )
			{
				floodpoint p; 
				p.absolute.x = x;
				p.absolute.y = y;
				p.relative.x = relx;
				p.relative.y = rely;
				stack_push(floodfillstack,p,floodpoint);
			}
			else
			{
				floodpoint p; 
				p.absolute.x = x-1;
				p.absolute.y = y;
				p.relative.x = xrelative8x8(relx-1);
				p.relative.y = rely;
				stack_push(floodfillstack,p,floodpoint);
			}
			pflag =0;
		}
		
		int xenter = x;
		pixelcor = getpixel(x,y);
		while( ( pixelcor == bordercolor ||  pixelcor == getfillcolor()  )  && ( x<xright ) )
		{
			x++;
			pixelcor = getpixel(x,y);
		}
		relx = calculateRelx(x,xenter,relx);
		if(x == xenter )
		{
			x++;
			relx = xrelative8x8(relx+1);
		} 
	}
}

void floodfillputline(pointtype abs,pointtype rel,int bordercolor,char * array,int * xleft,int*xleftrel,int * xright,int*xrightrel)
{
	int x,y,pixelcor,relx,rely;
	x = abs.x ;
	y = abs.y;
	relx = xrelative8x8(rel.x);
	rely = rel.y;
	pixelcor = getpixel(x,y) ;
	while(  pixelcor != bordercolor )
	{
		floodfillputpixel(x,y,relx,rely,array);
		x++;
		relx = xrelative8x8(relx+1);
		pixelcor= getpixel(x,y);
	}
	*xright = x-1;
	*xrightrel = xrelative8x8(relx-1);
	
	x = abs.x -1;
	relx = xrelative8x8(rel.x-1);
	pixelcor = getpixel(x,y) ;
	while(pixelcor != bordercolor)
	{
		floodfillputpixel(x,y,relx,rely,array);
		x--;
		relx = xrelative8x8( relx-1 );
		pixelcor = getpixel( x,y ) ;
	}
	*xleft = x+1;
	*xleftrel = xrelative8x8(relx+1);
}



void floodfillpatternScan(pointtype abs,pointtype rel,int bordercolor,char * array,stack floodfillstack,linklist ybucket)
{
	int x,y,relx,rely,xright,xrightrel,xleft,xleftrel;

	if( !isybucketthere(abs.y,abs.x,ybucket) )
	{
		floodfillputline(abs,rel,bordercolor,array,&xleft,&xleftrel,&xright,&xrightrel);
		insert2ybucket(abs.y,xleft-1,xright+1,ybucket);
	}
	
	/*check scan line above*/
	y = abs.y+1;
	rely = yrelative8x8(rel.y+1);
	x = xleft;
	relx = xleftrel;
	floodfillscanline(x,y,relx,rely,xright,bordercolor,floodfillstack,ybucket);
	
	/*scan the line below*/
	y = abs.y-1;
	rely = yrelative8x8(rel.y-1);
	x = xleft;
	relx = xleftrel;
	floodfillscanline(x,y,relx,rely,xright,bordercolor,floodfillstack,ybucket);
}

void floodfill(int x, int y, int bordercolor)
{
	DrawBorder(bordercolor);
	floodpoint p;
	p.absolute.y =y;
	p.absolute.x =x;
	p.relative.x = 0;
	p.relative.y = 0;
	stack floodfillstack = newstack(floodpoint);
	linklist ybucket = newlinklist(linklist);
	char * array = getpatternarray(Internalgetfillpattern());
	stack_push(floodfillstack,p,floodpoint);
	
	while( isstack_Empty(floodfillstack) != true )
	{
		p = stack_pop(floodfillstack,floodpoint);
		floodfillpatternScan(p.absolute,p.relative,bordercolor,array,floodfillstack,ybucket);
	}
	DrawBorder(BLACK);
	ads_delete(floodfillstack,ybucket);
	
}

#endif

