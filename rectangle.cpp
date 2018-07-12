



#ifndef GRAPHICSSHAPES_H
#define GRAPHICSSHAPES_H

#include "lines.cpp"
#include <math.h>
#include "HF.cpp"
#include "polygon.cpp"

#define DEFAULTCOLOR -1
#define DCLR DEFAULTCOLOR


void rectangle( int left, int top, int right, int bottom)
{
	int poly[] = {left,top,right,top,right,bottom,left,bottom};
	drawpoly(8,poly);
}

void bar(int left, int top, int right, int bottom)
{
	int c = getfillcolor(),p = Internalgetfillpattern();
	setfillstyle(SOLID_FILL,getcolor());
	int poly[] = {left,top,right,top,right,bottom,left,bottom};
	fillpoly(8,poly);
	setfillstyle(p,c);
}

void bar3d(int left, int top, int right, int bottom,int depth, int topflag)
{
	rectangle(left, top, right, bottom);
	line(right+depth,bottom-depth,right+depth,top-depth);
	line(right,bottom,right+depth,bottom-depth);
	line(right,top,right+depth,top-depth);
	line(right+depth,top-depth,left+depth,top-depth);
	line(left+depth,top-depth,left,top);
	if(topflag == 1)
	{
		floodfill(left+depth+1,top-depth+1,getcolor());
	}
}

#endif

