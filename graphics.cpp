#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "HF.cpp"
#include "rectangle.cpp"
#include "circle.cpp"
#include "ellipse.cpp"
#include "polygon.cpp"
#include "fillpatternstyle.cpp"
#include "lines.cpp"
#include "text.cpp"
#include "image.cpp"

#ifndef GRAPHICSH__H
#define GRAPHICSH__H


void initgraph(int * graphdriver ,int*graphmode ,const char * path);
void closegraph(void);
void detectgraph(int * graphdriver,int * graphmode);
void graphdefaults(void);

void line( int x1, int y1, int x2, int y2 );
void linerel(int dx, int dy);
void lineto(int x, int y);
void getlinesettings(struct linesettingstype *lineinfo);
void setlinestyle(int linestyle, unsigned int upattern,int thickness);

void moverel(int dx, int dy);
void moveto(int x, int y);

void circle( int x, int y, int radius );
void fillcircle( int x0, int y0, int radius );

void ellipse(int x, int y, int stangle, int endangle,int xradius, int yradius);
void fillellipse( int x, int y, int xradius, int yradius );

void rectangle( int left, int top, int right, int bottom );
void bar(int left, int top, int right, int bottom);
void bar3d(int left, int top, int right, int bottom,int depth, int topflag);

void arc( int x, int y, int stangle, int endangle, int radius );
void getarccoords(struct arccoordstype *arccoords);

void sector( int x, int y, int stangle, int endangle, int radius );

void pieslice(int x, int y, int stangle, int endangle,int radius);

void drawpoly(int numpoints ,const int * polypoints);
void fillpoly(int numpoints, const int * polypoints);

void floodfill(int x, int y, int bordercolor);

int getmaxx();
int getmaxy();

void delay( int msec );
int getmaxmode(void);
const char* getmodename( int mode_number );
void getmoderange(int graphdriver, int *lomode,int *himode);

int getbkcolor();
void  setbkcolor(int color);

int getcolor();
void setcolor(int color);

int getmaxcolor(void);

int getpixel(int x, int y);
void putpixel(int x,int y,int color);

void setfillstyle(int pattern, int color);
void getfillpattern(char * pattern);
void getfillsettings(struct fillsettingstype *fillinfo);
void setfillpattern(const char *upattern, int color);

int getch();
int kbhit();
void restorecrtmode(void);
void setgraphmode(int mode);
void setpalette(int colornum, int color);
void setallpalette(const struct palettetype * palette);

void getaspectratio(int *xasp, int *yasp);

const char*getdrivername( void );

void cleardevice(void);

void outtext(const char far *textstring);
void outtextxy(int x, int y, const char *textstring);
void settextjustify(int horiz, int vert);
void settextstyle(int font, int direction, int charsize);
void setusercharsize(int multx, int divx,int multy, int divy);
int textheight(const char far *__textstring);
int textwidth(const char far *__textstring);
void gettextsettings(struct textsettingstype far *__texttypeinfo);

void getpalette(struct palettetype * palette);
struct palettetype *getdefaultpalette( void );
int getpalettesize( void );

int getgraphmode(void);
int graphresult(void);
const char* grapherrormsg(int errorcode);


int gety(void);
int getx(void);

void getimage(int left, int top, int right, int bottom,void * bitmap);
unsigned int imagesize(int left, int top, int right, int bottom);
void putimage(int left, int top, const void *bitmap,int op);

void clearviewport(void);
void getviewsettings(struct viewporttype * viewport);
void setviewport(int left, int top, int right, int bottom,int clip);

#endif

