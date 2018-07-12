

#include <stdio.h>

#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "graphics.cpp"

typedef pointtype Point;

typedef struct {
	int left;
	int right;
	int top;
	int bottom;
} rect;

typedef struct {
	Point P1;
	Point P2;
} Line ;

int8_t getRegionCode(rect viewport ,Point p)
{
	int8_t rc = 0 ;
	if(p.y < viewport.top ) rc = rc | 0x1 ;
	rc = rc << 1;
	if(p.y > viewport.bottom ) rc = rc | 0x1 ;
	rc = rc << 1;
	if(p.x > viewport.right) rc = rc | 0x1 ;
	rc = rc << 1;
	if(p.x < viewport.left) rc = rc | 0x1 ;
	return rc;
}

Point clip_Cohen_Sutherland_linepoint( rect viewport,int rc,float slope,Point p )
{
	if(rc == 0 ) return p;
	if((rc&1))
	{
		p.y = p.y + slope * (viewport.left - p.x);
		p.x = viewport.left;
	}
	if( (rc&2)>>1)
	{
		p.y = p.y + slope * (viewport.right - p.x);
		p.x = viewport.right;
	}
	if( (rc&4)>>2)
	{
		p.x = p.x + (viewport.bottom - p.y) / slope;
		p.y = viewport.bottom;
	}
	if( (rc&8)>>3)
	{
		p.x = p.x + (viewport.top - p.y) / slope;
		p.y = viewport.top;
	}
	return p;
}

void Cohen_Sutherland_LineClipping( rect viewport , Line l)
{
	float m = ( l.P2.y - l.P1.y ) /(float) ( l.P2.x - l.P1.x );
	int rc1 = getRegionCode(viewport,l.P1);
	int	rc2 = getRegionCode(viewport,l.P2);
	if( (rc1 & rc2) != 0) return ;
	while(rc1 != 0 && rc2 != 0)
	{
		l.P1 = clip_Cohen_Sutherland_linepoint(viewport,rc1,m,l.P1);
		l.P2 = clip_Cohen_Sutherland_linepoint(viewport,rc2,m,l.P2);
		rc1 = getRegionCode(viewport,l.P1);
		rc2 = getRegionCode(viewport,l.P2);
	}
	return line(l.P1.x,l.P1.y,l.P2.x,l.P2.y);
}

float maxfloat(int cnt,float * a)
{
	int i;float max = a[0];
	for(i=1;i<cnt;i++)
	{
		if(a[i]>max) max = a[i];
	}
	return max;
}

float minfloat(int cnt,float * a)
{
	int i;float min = a[0];
	for(i=1;i<cnt;i++)
	{
		if(a[i]<min) min = a[i];
	}
	return min;
}

void Liang_Barsky_Drawline( rect viewport , Line l)
{
	int dx = l.P2.x - l.P1.x, dy = l.P2.y - l.P1.y;
	float ul[5],um[5]; int umc=0,ulc=0;
 	memset(ul,0,sizeof(float)*5);
 	memset(um,0,sizeof(float)*5);
	ul[ulc++] = 0;
	um[umc++] = 1;
	int p = dx*-1;
	int q = l.P1.x - viewport.left;
	if(p < 0) ul[ulc++] = (float)q/p;
	else um[umc++] = (float)q/p;
	p = dx;
	q = viewport.right - l.P1.x;
	if(p < 0 ) ul[ulc++] = (float)q/p;
	else um[umc++] = (float)q/p;
	p = dy*-1;
	q = l.P1.y - viewport.top;
	if(p < 0 ) ul[ulc++] = (float)q/p;
	else um[umc++] = (float)q/p;
	p = dy;
	q = viewport.bottom - l.P1.y;
	if(p < 0 ) ul[ulc++] = (float)q/p;
	else um[umc++] = (float)q/p;
	
	float t1 = maxfloat(ulc,ul);
	float t2 = minfloat(umc,um);
	if(t1>t2) return ;
	int x1 = l.P1.x + t1*(dx);
	int y1 = l.P1.y + t1*(dy);
	int x2 = l.P1.x + t2*(dx);
	int y2 = l.P1.y + t2*(dy);
	return line(x1,y1,x2,y2);
}

int findy(Point p1,Point p2,int x)
{
	float m = (p2.y-p1.y)/(float)(p2.x-p1.x);
	return p1.y + m*( x - p1.x);
}

int findx(Point p1,Point p2,int y)
{
	float m = (p2.y-p1.y)/(float)(p2.x-p1.x);
	return p1.x + (y - p1.y) / m;
}

int GetRelPosition(int frame,int pos,Point*poly,int size,Point*a)
{
	int i,cnt=0;Point p;int mod;
	if( pos == 0 )
	{
		for(i=0;i<size;i++)
		{
			mod = (i+1) % size;
			if(poly[i].x > frame && poly[mod].x > frame) /* inside-inside */
			{
				a[cnt] = poly[mod];
				cnt++;
			}
			else if( poly[i].x > frame && poly[mod].x < frame ) /* inside-outside */
			{
				p.x = frame;
				p.y = findy(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
			}
			else if( poly[i].x < frame && poly[mod].x > frame ) /*outside-inside*/
			{
				p.x = frame;
				p.y = findy(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
				a[cnt] = poly[mod];
				cnt++;
			}
		}
	}
	else if(pos == 1) /*bottom*/
	{
		for(i=0;i<size;i++)
		{
			mod = (i+1) % size;
			if(poly[i].y < frame && poly[mod].y < frame) /* inside-inside */
			{
				a[cnt] = poly[mod];
				cnt++;
			}
			else if( poly[i].y < frame && poly[mod].y > frame ) /*inside-outside*/
			{
				p.y = frame;
				p.x = findx(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
			}
			else if( poly[i].y > frame && poly[mod].y < frame ) /*outside-inside*/
			{
				p.y = frame;
				p.x = findx(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
				a[cnt] = poly[mod];
				cnt++;
			}
		}
	}
	else if(pos == 2) /*right*/
	{
		for(i=0;i<size;i++)
		{
			mod = (i+1) % size;
			if(poly[i].x < frame && poly[mod].x < frame) /* inside-inside */
			{
				a[cnt] = poly[mod];
				cnt++;
			}
			else if( poly[i].x < frame && poly[mod].x > frame ) /*inside-outside*/
			{
				p.x = frame;
				p.y = findy(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
			}
			else if( poly[i].x > frame && poly[mod].x < frame ) /*outside-inside*/
			{
				p.x = frame;
				p.y = findy(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
				a[cnt] = poly[mod];
				cnt++;
			}
		}
	}
	else if(pos == 3)
	{
		for(i=0;i<size;i++)
		{
			mod = (i+1) % size;
			if(poly[i].y > frame && poly[mod].y > frame) /* inside-inside */
			{
				a[cnt] = poly[mod];
				cnt++;
			}
			else if( poly[i].y > frame && poly[mod].y < frame ) /*inside-outside*/
			{
				p.y = frame;
				p.x = findx(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
			}
			else if( poly[i].y < frame && poly[mod].y > frame ) /*outside-inside*/
			{
				p.y = frame;
				p.x = findx(poly[i],poly[mod],frame);
				a[cnt] = p;
				cnt++;
				a[cnt] = poly[mod];
				cnt++;
			}
		}
	}
	return cnt;
}

void Sutherland_Hodgman_PolygonClipping(rect viewport,Point*poly,int size)
{
	Point a[size*2],p[size*2];int cnt ;
	memcpy(p,poly,sizeof(Point)*size);
	cnt = GetRelPosition(viewport.left,0,p,size,a);
	size = GetRelPosition(viewport.bottom,1,a,cnt,p);
	cnt = GetRelPosition(viewport.right,2,p,size,a);
	size = GetRelPosition(viewport.top,3,a,cnt,p);
	return drawpoly(size*2,(int*)p);
}

int main()
{
	rect viewport = {100,200,100,200};
	Point p[3] = {{178,80},{125,250},{230,150}};
	Line l = {{25,175},{250,70}};
	int gd , gr;
	initgraph(&gd,&gr,"");
	rectangle(100,100,200,200);
	drawpoly(3*2,(int*)p);
	line(25,175,250,70);
	setcolor(RED);
	Sutherland_Hodgman_PolygonClipping(viewport,p,3);
	Liang_Barsky_Drawline(viewport,l);
	getch();
	closegraph();
}

