


#ifndef GRAPHICSDOTHELLIPSE_H
#define GRAPHICSDOTHELLIPSE_H

#include "lines.cpp"
#include <math.h>
#include "HF.cpp"
#include "utility.cpp"
#include "fillpatternstyle.cpp"
#include "circle.cpp"

void ellipse( int xc, int yc, int stangle, int endangle,int xradius, int yradius )
{
	initializelinestyle();
    int a=xradius,b=yradius;
    int x = 0,y=b;
    int aa = a*a;int bb=b*b,bb2 = bb*2,aa2 = aa*2;
    int fy=aa2*b,fx = 0;
    int p = bb-aa*b+0.25*aa;
    double deg;
	while(fx<fy)
	{
		deg = iatan2(+x,+y);
		if( deg <= endangle && deg >= stangle ) setlinepixel(xc+x,yc+y,DEFAULTCOLOR);
		else getlinestylepixelbitINC();
		deg = iatan2(-x,-y);
		if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc-x,yc-y,DEFAULTCOLOR);
		deg = iatan2(-x,+y);
		if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc-x,yc+y,DEFAULTCOLOR);
		deg = iatan2(+x,-y);
		if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc+x,yc-y,DEFAULTCOLOR);
		x++;
		fx = fx+bb2;
		if(p<0)	
		{
			p = p +fx + bb;
		}
		else
		{
			y--;
			fy = fy-aa2;
			p = p+fx+bb-fy;
		}
	}
	deg = iatan2(+x,+y);
	if(deg <= endangle && deg >= stangle ) setlinepixel(xc+x,yc+y,DEFAULTCOLOR);
	else getlinestylepixelbitINC();
	deg = iatan2(-x,-y);
	if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc-x,yc-y,DEFAULTCOLOR);
	deg = iatan2(-x,+y);
	if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc-x,yc+y,DEFAULTCOLOR);
	deg = iatan2(+x,-y);
	if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc+x,yc-y,DEFAULTCOLOR);
	p = bb*(x+0.5)*(x+0.5)+aa*(y-1)*(y-1)-aa*bb;
	while(y>0)
	{
		y--;
		fy = fy -aa2;
		if(p>=0)
		{
			p = p - fy +aa;
		}
		else
		{
			x++;
			fx = fx +bb2;
			p = p+fx-fy+aa;
		}
		deg = iatan2(+x,+y);
		if(deg <= endangle && deg >= stangle ) setlinepixel(xc+x,yc+y,DEFAULTCOLOR);
		else getlinestylepixelbitINC();
		deg = iatan2(-x,-y);
		if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc-x,yc-y,DEFAULTCOLOR);
		deg = iatan2(-x,+y);
		if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc-x,yc+y,DEFAULTCOLOR);
		deg = iatan2(+x,-y);
		if(deg <= endangle && deg >= stangle && getlinestylepixelbit() ) putpixel(xc+x,yc-y,DEFAULTCOLOR);
	}
}

bool isellipseContains(int xc,int yc,int _xRadius,int _yRadius, int x,int y)
{
    if (_xRadius <= 0 || _yRadius <= 0) return false;
    int nx = x - xc ;
    int ny = y - yc ;
    return ((double)(nx * nx)
             / (_xRadius * _xRadius)) + ((double)(ny * ny) / (_yRadius * _yRadius))
        <= 1.0;
}

void fillellipse( int xc, int yc, int horizontalaxis, int vericalaxis )
{
	int x , y ;
	int ymax = yc + vericalaxis ;
	int xmax = xc + horizontalaxis ;
	pointtype parray[maxpatternbit*maxpatternbit];
	char * array = getpatternarray(Internalgetfillpattern());
	int size = fillarray2points(array,parray);
	for( y = yc - vericalaxis ; y < ymax ; y+= maxpatternbit )
	{
		for(x = xc - horizontalaxis ; x < xmax ; x+= maxpatternbit)
		{
			int i;
			for(i=0;i<size;i++)
			{
				if(isellipseContains(xc,yc,horizontalaxis,vericalaxis, x + parray[i].x , y + parray[i].y) == true)
				{
					putpixel(x + parray[i].x ,y + parray[i].y ,getfillcolor());
				}
			}
		}
	}
}

#endif

