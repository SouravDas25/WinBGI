#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <graphics.h>

using namespace std;

typedef pointtype Point;

int factorial(int n)
{
	if(n<=1) return 1;
	return factorial(n-1)*n;
}

int Combination(int n,int r)
{
	return factorial(n) / ( factorial(n-r) * factorial(r) );
}

int rund(double f)
{
	int o = f;
	if( f-(double)o >= 0.50000) return o+1;
	return o;
}

Point Bezier_Summation(float u,Point* p,int size)
{
	int i;int n = size-1;
	Point f = {0,0};
	for( i=0 ; i<size ; i++)
	{
		f.x += rund( p[i].x*Combination(n,i)*pow(1-u,n-i)*pow(u,i) );
		f.y += rund( p[i].y*Combination(n,i)*pow(1-u,n-i)*pow(u,i) );
	}
	return f;
}

void Bezier_Curve( Point* p,int size )
{
	float d;Point f,pr={-1,-1};
	for( d=0.0 ; d<=1.0000 ; d+=0.01 )
	{
		f = Bezier_Summation(d,p,size);
		if(pr.x!=-1)line(pr.x,pr.y,f.x,f.y);
		pr = f;
	}
}

void draw_polygon(int numpoints ,const Point * poly,bool last=true)
{
	numpoints*=2;
	if(numpoints%2 != 0 ) return ;
	if(numpoints < 6 ) return ;
	int i,*polypoints=(int*)poly;
	for(i=0;i<=numpoints-4;i+=2)
	{
		line(polypoints[i],polypoints[i+1],polypoints[i+2],polypoints[i+3]);
	}
	if(last)line(polypoints[0],polypoints[1],polypoints[numpoints-2],polypoints[numpoints-1]);
}


int main()
{
	int gd,gr;
	Point p[] = {{70,300},{180,72},{456,86},{554,278},{619,114}};
	int size = 5;
	initgraph(&gd,&gr,"C://TC//BIN");
	draw_polygon(size,p,0);
	setcolor(RED);
	Bezier_Curve(p,size);
	getch();
	closegraph();
}
