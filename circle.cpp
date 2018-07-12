


#ifndef GRAPHICSDOTH_CIRCLE
#define GRAPHICSDOTH_CIRCLE

#include "HF.cpp"
#include "lines.cpp"
#include <math.h>

#define DEFAULTCOLOR -1
#define DCLR DEFAULTCOLOR

double toRadians(double x)
{
	return x/(180.0/ 3.14159265358979323846 );
}

double toDegrees(double x)
{
	return (180.0/ 3.14159265358979323846 )*x;
}

void circle( int x0, int y0, int radius )
{
	initializelinestyle();
	int x = 0;
	int y =  radius;
	int di = 1-radius;
	while(x<=y)
	{
		putpixel(x0+x,y0+y,DEFAULTCOLOR);
		putpixel(x0+y,y0+x,DEFAULTCOLOR);
		putpixel(x0-y,y0+x,DEFAULTCOLOR);
		putpixel(x0-x,y0+y,DEFAULTCOLOR);
		putpixel(x0-x,y0-y,DEFAULTCOLOR);
		putpixel(x0-y,y0-x,DEFAULTCOLOR);
		putpixel(x0+y,y0-x,DEFAULTCOLOR);
		putpixel(x0+x,y0-y,DEFAULTCOLOR);
		if( di < 0 )
		di = di + (x<<1) + 3;
		else
		{
			di = di + ( ( x - y ) << 1) + 5;
			y--;
		}
		x++;
	}
}

void fillcircle( int x0, int y0, int radius )
{
	int x = 0;
	int y =  radius;
	int di = 1-radius;
	while(x<=y)
	{
		efla(x0+x,y0+y,x0+x,y0-y);
		efla(x0-x,y0+y,x0-x,y0-y);
		efla(x0+y,y0+x,x0+y,y0-x);
		efla(x0-y,y0+x,x0-y,y0-x);
		if( di < 0 )
		di = di + (x<<1) + 3;
		else
		{
			di = di + ( ( x - y ) << 1) + 5;
			y--;
		}
		x++;
	}
}

double iatan2(double x,double y) 
{
	double deg = toDegrees(atan2(y,x));
	if(deg < 0 ) return 360.0+deg;
	else return deg ;
}

struct arccoordstype LastArcFromBGI ;

void arc( int x0, int y0, int stangle, int endangle, int radius )
{
	LastArcFromBGI.x = x0;
	LastArcFromBGI.y = y0;
	LastArcFromBGI.xstart = x0 + radius*cos(toRadians(stangle));
	LastArcFromBGI.xend = x0 + radius*cos(toRadians(endangle));
	LastArcFromBGI.ystart = y0 + radius*sin(toRadians(stangle));
	LastArcFromBGI.yend = y0 + radius*sin(toRadians(endangle));
	int x = 0;
	int y =  radius;
	int di = 1-radius;
	while(x<=y)
	{
		double deg = iatan2(+x,+y);
		if( deg <= endangle && deg >= stangle ) putpixel(x0+x,y0+y,DEFAULTCOLOR);
		deg = iatan2(+y,+x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0+y,y0+x,DEFAULTCOLOR);
		deg = iatan2(-y,+x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-y,y0+x,DEFAULTCOLOR);
		deg = iatan2(-x,+y);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-x,y0+y,DEFAULTCOLOR);
		deg = iatan2(-x,-y);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-x,y0-y,DEFAULTCOLOR);
		deg = iatan2(-y,-x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-y,y0-x,DEFAULTCOLOR);
		deg = iatan2(+y,-x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0+y,y0-x,DEFAULTCOLOR);
		deg = iatan2(+x,-y);
		if(deg <= endangle && deg >= stangle ) putpixel(x0+x,y0-y,DEFAULTCOLOR);
		if(di<0)
		di = di+(x<<1)+3;
		else
		{
			di = di +((x-y)<<1)+5;
			y--;
		}
		x++;
	}
}

void getarccoords(struct arccoordstype *arccoords)
{
	*arccoords = LastArcFromBGI;
}

void sector( int x0, int y0, int stangle, int endangle, int radius )
{
	int x = 0;
	int y =  radius;
	int di = 1-radius;
	while(x<=y)
	{
		double deg = iatan2(+x,+y);
		if( deg <= endangle && deg >= stangle ) putpixel(x0+x,y0+y,DEFAULTCOLOR);
		deg = iatan2(+y,+x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0+y,y0+x,DEFAULTCOLOR);
		deg = iatan2(-y,+x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-y,y0+x,DEFAULTCOLOR);
		deg = iatan2(-x,+y);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-x,y0+y,DEFAULTCOLOR);
		deg = iatan2(-x,-y);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-x,y0-y,DEFAULTCOLOR);
		deg = iatan2(-y,-x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0-y,y0-x,DEFAULTCOLOR);
		deg = iatan2(+y,-x);
		if(deg <= endangle && deg >= stangle ) putpixel(x0+y,y0-x,DEFAULTCOLOR);
		deg = iatan2(+x,-y);
		if(deg <= endangle && deg >= stangle ) putpixel(x0+x,y0-y,DEFAULTCOLOR);
		if(di<0)
		di = di+(x<<1)+3;
		else
		{
			di = di + ((x-y)<<1)+5;
			y--;
		}
		x++;
	}
	int x1,y1;
	struct linesettingstype pls; 
	getlinesettings(&pls);
	setlinestyle(SOLID_LINE,0,pls.thickness);
	x1 = x0 + radius * cos(toRadians(stangle));
	y1 = y0 + radius * sin(toRadians(stangle));
	line(x0,y0,x1,y1);
	x1 = x0 + radius * cos(toRadians(endangle));
	y1 = y0 + radius * sin(toRadians(endangle));
	line(x0,y0,x1,y1);
	x1 = x0 + (radius>>1) * cos(toRadians((stangle+endangle)>>1));
	y1 = y0 + (radius>>1) * sin(toRadians((stangle+endangle)>>1));
	floodfill(x1,y1,getcolor());
	setlinestyle(pls.linestyle,pls.upattern,pls.thickness);
}

void pieslice(int x, int y, int stangle, int endangle,int radius)
{
	sector(x,y,stangle,endangle,radius);
	if(stangle == 0) stangle = 360;
	else if(stangle == 360) stangle = 0;
	if(endangle == 0 )endangle = 360;
	else if(endangle == 360 )endangle = 0;
	if(stangle>endangle) intswap(&stangle,&endangle);
	arc(x,y,stangle,endangle,radius);
}
#endif

