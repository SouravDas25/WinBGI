


#ifndef DRAWGRAPHICSHLINES_H
#define DRAWGRAPHICSHLINES_H
#include "HF.cpp"

#include <math.h>

#define MAXCOLORS   15
#define DEFAULTCOLOR -1

void intswap(int * a,int*b)
{
	int k = *a;
	*a = *b;
	*b = k;
}

struct patrn {
	unsigned char relative;
	unsigned char thickness;
	unsigned short pattern;
} ActiveLinePattern ;

void getlinesettings(struct linesettingstype *lineinfo)
{
	lineinfo->linestyle = __Current.linestyle;
	lineinfo->thickness = __Current.linethickness;
	lineinfo->upattern = __Current.linepattern;
}

unsigned short getlinepattern(int linestyle,unsigned short upatrn)
{
	unsigned short pattern ;
	switch(linestyle)
	{
		case SOLID_LINE : {
			pattern = 0xFFFF;
			break;
		}
		case DOTTED_LINE : {
			pattern = 0x3333;
			break;
		}
		case CENTER_LINE : {
			pattern = 0xF3CF;
			break;
		}
		case DASHED_LINE : {
			pattern = 0xFF00;
			break;
		}
		case USERBIT_LINE : {
			pattern = upatrn;
			break;
		}
	}
	return pattern;
}

void setlinestyle(int linestyle, unsigned int upattern,int thickness)
{
	__Current.linestyle = linestyle;
	__Current.linepattern = upattern;
	__Current.linethickness = thickness;
	ActiveLinePattern.pattern = getlinepattern(linestyle,upattern);
	ActiveLinePattern.relative = 0;
	ActiveLinePattern.thickness = thickness;
}

void initializelinestyle()
{
	ActiveLinePattern.pattern = getlinepattern(__Current.linestyle,__Current.linepattern);
	ActiveLinePattern.relative = 0;
	ActiveLinePattern.thickness = __Current.linethickness;
}

char getlinestylepixelbit()
{
	int a = ActiveLinePattern.relative-1;
	if(a == -1)a = 0;
	return (ActiveLinePattern.pattern >> (15 - a ) )&0x1;
}

void getlinestylepixelbitINC()
{
	ActiveLinePattern.relative = (ActiveLinePattern.relative + 1) %16;
}

void setlinepixel(int x,int y,int color)
{
	char bit = (ActiveLinePattern.pattern >> (15-ActiveLinePattern.relative) )&0x1;
	if(bit) 
	{
		putpixel(x,y,color);
	}
	ActiveLinePattern.relative = (ActiveLinePattern.relative + 1) %16;
}

pointtype LineActivePoints = {0,0};

void ppline( int x1, int y1, int x2, int y2 ) //draws a line if x1,y1 is less than x2,y2
{
	int dx,dy;
	int yadd = 1,xadd =1;
	int x,y;
	int di,ds,dt;
	dx=x2-x1;
	dy=y2-y1;
	if(dy < 0) yadd*=-1;
	if(dx < 0) xadd*=-1;
	if(abs(dy) > abs(dx))
	{
		x = x1; y= y1;
		ds = 2*dx;
		dt = 2*(dy-dx);
		di = dy-2*dx;
		while(y<=y2)
		{
			setlinepixel(x,y,DEFAULTCOLOR);
			if(di<0)
			{
				x+=xadd;
				di = di + dt;
			}
			else
			{
				di =di - ds;
			}
			y+=yadd;
		}
	}
	else
	{
		x = x1; y= y1;
		ds = 2*dy;
		dt = 2*(dy-dx);
		di = 2*dy-dx;
		while(x<=x2)
		{
			setlinepixel(x,y,DEFAULTCOLOR);
			x+=xadd;
			if(di<0)
			{
				di = di + ds;
			}
			else
			{
				y+=yadd;
				di =di + dt;
			}
		}
	}
}

void pnline( int x1, int y1, int x2, int y2 ) //draws a line if y2 and x1 is less than y1 and x2 respectively
{
	int dx,dy;
	int x,y;
	int di,ds,dt;
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dy) > abs(dx))
	{
		x = x1; y= y1;
		ds = 2*dx;
		dt = 2*(dy+dx);
		di = dy+2*dx;
		while(y2<=y)
		{
			setlinepixel(x,y,DEFAULTCOLOR);
			if(di<=0)
			{
				di = di + ds;
			}
			else
			{
				x++;
				di = di + dt;
			}
			y--;
		}
	}
	else
	{
		x = x1; y= y1;
		ds = 2*dy;
		dt = 2*(dy+dx);
		di = 2*dy+dx;
		while(x<=x2)
		{
			setlinepixel(x,y,DEFAULTCOLOR);
			x++;
			if(di<=0)
			{
				y--;
				di = di + dt;
			}
			else
			{
				di = di + ds;
			}
		}
	}
}

void line( int x1, int y1, int x2, int y2 )
{
	initializelinestyle();
	if((y2<y1) != (x2<x1))
	{
		if(x2<x1)
		{
			intswap(&x1,&x2);
			intswap(&y1,&y2);
		}
		pnline(x1,y1,x2,y2);
	}
	else
	{
		if(x2<x1)
		{
			intswap(&x1,&x2);
			intswap(&y1,&y2);
		}
		ppline(x1,y1,x2,y2);
	}
	LineActivePoints.x = x2;
	LineActivePoints.y = y2;
}

void linerel(int dx, int dy)
{
	int x1 = LineActivePoints.x,y1 = LineActivePoints.y;
	line(x1,y1,x1+dx,y1+dy);
}
void lineto(int x, int y)
{
	int x1 = LineActivePoints.x,y1 = LineActivePoints.y;
	line(x1,y1,x,y);
}

void cleardevice(void)
{
	setbkcolor(BLACK);
	LineActivePoints.x = 0;
	LineActivePoints.y=0;
}

void moverel(int dx, int dy)
{
	LineActivePoints.x += dx;
	LineActivePoints.y += dy;
}
void moveto(int x, int y)
{
	LineActivePoints.x = x;
	LineActivePoints.y = y;
}

int gety(void)
{
	return LineActivePoints.x;
}
int getx(void)
{
	return LineActivePoints.y;
}

void efla(int x, int y,int x2,int y2)
{
	int shortLen = y2-y;
	int longLen = x2-x;
	bool yLonger;
	if ((shortLen ^ (shortLen >> 31)) - (shortLen >> 31) > (longLen ^ (longLen >> 31)) - (longLen >> 31))
	{
		shortLen ^= longLen;
		longLen ^= shortLen;
		shortLen ^= longLen;

		yLonger = true;
	}
	else
	{
		yLonger = false;
	}
	int inc = (longLen < 0) ? -1 : 1;
	int multDiff = (longLen == 0) ? shortLen : shortLen / longLen ;
	int i;
	if (yLonger)
	{
		for (i = 0; i != longLen; i += inc)
		{
			setlinepixel(x + i*multDiff, y+i, DEFAULTCOLOR);
		}
	}
	else
	{
		for (i = 0; i != longLen; i += inc)
		{
			setlinepixel(x+i, y+i*multDiff, DEFAULTCOLOR);
		}
	}
}


#endif

