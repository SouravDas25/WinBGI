



#ifndef GRAPHICSPOLYGONDOTH_H
#define GRAPHICSPOLYGONDOTH_H

#include "lines.cpp"
#include <math.h>
#include "HF.cpp"
#include "utility.cpp"
#include "fillpatternstyle.cpp"

void drawpoly(int numpoints ,const int * polypoints)
{
	if(numpoints%2 != 0 ) return ;
	if(numpoints < 6 ) return ;
	int i;
	for(i=0;i<=numpoints-4;i+=2)
	{
		line(polypoints[i],polypoints[i+1],polypoints[i+2],polypoints[i+3]);
	}
	line(polypoints[0],polypoints[1],polypoints[numpoints-2],polypoints[numpoints-1]);
}

typedef pointtype Point;

/*
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}

bool isInsidePolygon(Point * polygon, int n, Point p,int xmax)
{
    // There must be at least 3 vertices in polygon[]
    if (n < 3)  return false;
 
    // Create a point for line segment from p to infinite
    Point extreme = {xmax , p.y};
 
    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;
 
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[next]) == 0)
               return onSegment(polygon[i], p, polygon[next]);
 
            count++;
        }
        i = next;
    } while (i != 0);
 
    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
}
*/


void numpoints2polygonPoint(int numpoints,const int *  polypoints,Point * polygon,Point * minmax)
{
	int i,cnt = 0;int xmax = polypoints[0] ,ymax = polypoints[1],ymin = polypoints[1],xmin= polypoints[0] ;
	for(i=0; i < numpoints ;i+=2)
	{
		polygon[cnt].x = polypoints[i];
		polygon[cnt].y = polypoints[i+1];
		cnt++;
		if(polypoints[i] > xmax) xmax = polypoints[i] ;
		if(polypoints[i+1] > ymax) ymax = polypoints[i+1] ;
		if(polypoints[i] < xmin) xmin = polypoints[i] ;
		if(polypoints[i+1] < ymin) ymin = polypoints[i+1] ;
	}
	polygon[cnt].x = polypoints[0];
	polygon[cnt].y = polypoints[1];
	minmax[0].x = xmax;
	minmax[0].y = ymax;
	minmax[1].x = xmin;
	minmax[1].y = ymin;
}

int isLeft( Point P0, Point P1, Point P2 )
{
    return ( (P1.x - P0.x) * (P2.y - P0.y) - (P2.x -  P0.x) * (P1.y - P0.y) );
}

int wn_PnPoly( Point P, Point* V, int n )
{
    int    wn = 0;    // the  winding number counter

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {   // edge from V[i] to  V[i+1]
        if (V[i].y <= P.y) {          // start y <= P.y
            if (V[i+1].y  > P.y)      // an upward crossing
                 if (isLeft( V[i], V[i+1], P) > 0)  // P left of  edge
                     ++wn;            // have  a valid up intersect
        }
        else {                        // start y > P.y (no test needed)
            if (V[i+1].y  <= P.y)     // a downward crossing
                 if (isLeft( V[i], V[i+1], P) < 0)  // P right of  edge
                     --wn;            // have  a valid down intersect
        }
    }
    return wn;
}

void fillpoly(int numpoints, const int *  polypoints)
{
	int x , y ;
	Point polygon[(numpoints>>1)+1] ,minmax[2];
	numpoints2polygonPoint(numpoints,polypoints,polygon,minmax);
	int ymax = minmax[0].x ;
	int xmax = minmax[0].y ;
	
	pointtype parray[maxpatternbit*maxpatternbit];
	char * array = getpatternarray(Internalgetfillpattern());
	int size = fillarray2points(array,parray);
	
	for( y = minmax[1].y ; y < ymax ; y+= maxpatternbit )
	{
		for(x = minmax[1].x ; x < xmax ; x+= maxpatternbit)
		{
			int i;
			for(i=0;i<size;i++)
			{
				Point p = {x + parray[i].x,y + parray[i].y};
				if( wn_PnPoly(p,polygon,(numpoints>>1)+1) != 0)
				{
					putpixel(x + parray[i].x ,y + parray[i].y ,getfillcolor());
				}
			}
		}
	}
}

#endif

