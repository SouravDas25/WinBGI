/*  graphics.h

    Definitions for Graphics Package.

    Copyright (c) 1987, 1991 by Borland International
    All Rights Reserved.
*/

#if !defined(__GRAPHICS_H)
#define __GRAPHICS_H

enum graphics_errors {      /* graphresult error return codes */
    grOk                =   0,
    grNoInitGraph       =  -1,
    grNotDetected       =  -2,
    grFileNotFound      =  -3,
    grInvalidDriver     =  -4,
    grNoLoadMem         =  -5,
    grNoScanMem         =  -6,
    grNoFloodMem        =  -7,
    grFontNotFound      =  -8,
    grNoFontMem         =  -9,
    grInvalidMode       = -10,
    grError             = -11,   /* generic error */
    grIOerror           = -12,
    grInvalidFont       = -13,
    grInvalidFontNum    = -14,
    grInvalidVersion    = -18
};

enum graphics_drivers {     /* define graphics drivers */
    DETECT,         /* requests autodetection */
    CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514,    /* 1 - 6 */
    HERCMONO, ATT400, VGA, PC3270,          /* 7 - 10 */
    CURRENT_DRIVER = -1
};

enum graphics_modes {       /* graphics modes for each driver */
    CGAC0      = 0,  /* 320x200 palette 0; 1 page   */
    CGAC1      = 1,  /* 320x200 palette 1; 1 page   */
    CGAC2      = 2,  /* 320x200 palette 2: 1 page   */
    CGAC3      = 3,  /* 320x200 palette 3; 1 page   */
    CGAHI      = 4,  /* 640x200 1 page          */
    MCGAC0     = 0,  /* 320x200 palette 0; 1 page   */
    MCGAC1     = 1,  /* 320x200 palette 1; 1 page   */
    MCGAC2     = 2,  /* 320x200 palette 2; 1 page   */
    MCGAC3     = 3,  /* 320x200 palette 3; 1 page   */
    MCGAMED    = 4,  /* 640x200 1 page          */
    MCGAHI     = 5,  /* 640x480 1 page          */
    EGALO      = 0,  /* 640x200 16 color 4 pages    */
    EGAHI      = 1,  /* 640x350 16 color 2 pages    */
    EGA64LO    = 0,  /* 640x200 16 color 1 page     */
    EGA64HI    = 1,  /* 640x350 4 color  1 page     */
    EGAMONOHI  = 0,  /* 640x350 64K on card, 1 page - 256K on card, 4 pages */
    HERCMONOHI = 0,  /* 720x348 2 pages         */
    ATT400C0   = 0,  /* 320x200 palette 0; 1 page   */
    ATT400C1   = 1,  /* 320x200 palette 1; 1 page   */
    ATT400C2   = 2,  /* 320x200 palette 2; 1 page   */
    ATT400C3   = 3,  /* 320x200 palette 3; 1 page   */
    ATT400MED  = 4,  /* 640x200 1 page          */
    ATT400HI   = 5,  /* 640x400 1 page          */
    VGALO      = 0,  /* 640x200 16 color 4 pages    */
    VGAMED     = 1,  /* 640x350 16 color 2 pages    */
    VGAHI      = 2,  /* 640x480 16 color 1 page     */
    PC3270HI   = 0,  /* 720x350 1 page          */
    IBM8514LO  = 0,  /* 640x480 256 colors      */
    IBM8514HI  = 1   /*1024x768 256 colors      */
};

/* Colors for setpalette and setallpalette */

#if !defined(__COLORS)
#define __COLORS

enum COLORS {
    BLACK,          /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,       /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};
#endif

enum line_styles {      /* Line styles for get/setlinestyle */
    SOLID_LINE   = 0,
    DOTTED_LINE  = 1,
    CENTER_LINE  = 2,
    DASHED_LINE  = 3,
    USERBIT_LINE = 4,   /* User defined line style */
};

enum line_widths {      /* Line widths for get/setlinestyle */
    NORM_WIDTH  = 1,
    THICK_WIDTH = 3,
};

enum font_names {
    DEFAULT_FONT        = 0,    /* 8x8 bit mapped font */
    TRIPLEX_FONT        = 1,    /* "Stroked" fonts */
    SMALL_FONT          = 2,
    SANS_SERIF_FONT     = 3,
    GOTHIC_FONT         = 4,
    SCRIPT_FONT         = 5,        
    SIMPLEX_FONT        = 6,       
    TRIPLEX_SCR_FONT    = 7,
    COMPLEX_FONT        = 8,       
    EUROPEAN_FONT       = 9,  
    BOLD_FONT           = 10      
};

#define HORIZ_DIR   0   /* left to right */
#define VERT_DIR    1   /* bottom to top */

#define USER_CHAR_SIZE  0   /* user-defined char size */

enum fill_patterns {    /* Fill patterns for get/setfillstyle */
    EMPTY_FILL,         /* fills area in background color */
    SOLID_FILL,         /* fills area in solid fill color */
    LINE_FILL,          /* --- fill */
    LTSLASH_FILL,       /* /// fill */
    SLASH_FILL,         /* /// fill with thick lines */
    BKSLASH_FILL,       /* \\\ fill with thick lines */
    LTBKSLASH_FILL,     /* \\\ fill */
    HATCH_FILL,         /* light hatch fill */
    XHATCH_FILL,        /* heavy cross hatch fill */
    INTERLEAVE_FILL,    /* interleaving line fill */
    WIDE_DOT_FILL,      /* Widely spaced dot fill */
    CLOSE_DOT_FILL,     /* Closely spaced dot fill */
    USER_FILL           /* user defined fill */
};

enum putimage_ops {     /* BitBlt operators for putimage */
    COPY_PUT,           /* MOV */
    XOR_PUT,            /* XOR */
    OR_PUT,             /* OR  */
    AND_PUT,            /* AND */
    NOT_PUT             /* NOT */
};

enum text_just {        /* Horizontal and vertical justification
                           for settextjustify */
    LEFT_TEXT   = 0,
    CENTER_TEXT = 1,
    RIGHT_TEXT  = 2,

    BOTTOM_TEXT = 0,
     /* CENTER_TEXT = 1,  already defined above */
    TOP_TEXT    = 2
};


#define MAXCOLORS 15

struct palettetype {
    unsigned char size;
    signed char colors[MAXCOLORS+1];
};

struct linesettingstype {
    int linestyle;
    unsigned upattern;
    int thickness;
};

struct textsettingstype {
    int font;
    int direction;
    int charsize;
    int horiz;
    int vert;
};

struct fillsettingstype {
    int pattern;
    int color;
};

struct pointtype {
    int x, y;
};

struct viewporttype {
    int left, top, right, bottom;
    int clip;
};

struct arccoordstype {
    int x, y;
    int xstart, ystart, xend, yend;
};

#ifdef __cplusplus
extern "C" {
#endif

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

void drawpoly(int numpoints ,pointtype * polypoints);
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

void getaspectratio(int *xasp, int *yasp);

const char*getdrivername( void );

void cleardevice(void);

void outtext(const char *textstring);
void outtextxy(int x, int y, const char *textstring);
void settextjustify(int horiz, int vert);
void settextstyle(int font, int direction, int charsize);
void setusercharsize(int multx, int divx,int multy, int divy);
int textheight(const char *__textstring);
int textwidth(const char *__textstring);
void gettextsettings(struct textsettingstype *__texttypeinfo);

void getpalette(struct palettetype * palette);
struct palettetype *getdefaultpalette( void );
int getpalettesize( void );

int getgraphmode(void);
int graphresult(void);

int gety(void);
int getx(void);

void getimage(int left, int top, int right, int bottom,void * bitmap);
unsigned int imagesize(int left, int top, int right, int bottom);
void putimage(int left, int top, const void *bitmap,int op);

void clearviewport(void);
void getviewsettings(struct viewporttype * viewport);
void setviewport(int left, int top, int right, int bottom,int clip);

#ifdef __cplusplus
}
#endif

#endif
