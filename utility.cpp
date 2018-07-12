


#ifndef UTILITYGRAPHICSDOTH_H
#define UTILITYGRAPHICSDOTH_H

#include <windows.h>

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

#define HORIZ_DIR   0   /* left to right */
#define VERT_DIR    1   /* bottom to top */

enum text_just {        /* Horizontal and vertical justification
                           for settextjustify */
    LEFT_TEXT   = 0,
    CENTER_TEXT = 1,
    RIGHT_TEXT  = 2,

    BOTTOM_TEXT = 0,
     /* CENTER_TEXT = 1,  already defined above */
    TOP_TEXT    = 2
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

enum putimage_ops {     /* BitBlt operators for putimage */
    COPY_PUT,           /* MOV */
    XOR_PUT,            /* XOR */
    OR_PUT,             /* OR  */
    AND_PUT,            /* AND */
    NOT_PUT             /* NOT */
};

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

#define MAXCOLORS 15

typedef struct  {
    int x, y;
}pointtype;

struct arccoordstype {
    int x, y;
    int xstart, ystart, xend, yend;
};

struct fillsettingstype {
    int pattern;
    int color;
};

struct textsettingstype {
    int font;
    int direction;
    int charsize;
    int horiz;
    int vert;
};

struct linesettingstype {
    int linestyle;
    unsigned upattern;
    int thickness;
};

struct palettetype {
    unsigned char size;
    signed char colors[MAXCOLORS+1];
};

struct viewporttype {
    int left, top, right, bottom;
    int clip;
};

#define USER_CHAR_SIZE  0

#endif

