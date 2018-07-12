
#ifndef WINGRAPHICSCONCERTER_H
#define WINGRAPHICSCONCERTER_H
#include <windows.h>
#include <stdio.h>
#include "utility.cpp"
#include "collection\Avl.c"

typedef struct {
	BYTE initialized;
	WNDCLASSEX wc;
	HWND hwnd;
	HWND Cnhwnd;
	MSG msg;
	PAINTSTRUCT ps;
	int bgcolor;
	int color;
	HDC hdcWindow;
	BYTE fillpattern;
	int fillcolor;
	struct palettetype activepalette;
	int grErrorCode;
	int horitextjust;
	int vertextjust;
	HFONT font;
	short fontnum;
	short direction;
	short charsize;
	short linestyle;
	short linepattern;
	short linethickness;
	struct viewporttype activeviewport;
	//dict ColorIndex ;
} turbograph ; 

ULONG colors[] =  { /* BLACK */ RGB(0,0,0), /*BLUE =*/ RGB(0,0,255), /*GREEN=*/ RGB(0,255,0), /*CYAN=*/RGB(224,255,255), 
/*RED=*/RGB(255,0,0), /*MAGENTA =*/ RGB(139,0,139), /*BROWN =*/ RGB(165,42,42) , /*LIGHTGRAY =*/RGB(192,192,192), /*DARKGRAY =*/RGB(128,128,128) ,
/*LIGHTBLUE =*/ RGB(173,216,230), /*LIGHTGREEN =*/RGB(144,238,144) , /*LIGHTCYAN =*/ RGB(224,255,255),
 /*LIGHTRED =*/  RGB(255,99,71), /*LIGHTMAGENTA =*/ RGB(255,0,255), /*YELLOW =*/ RGB(255,255,0), /*WHITE =*/ RGB(255,255,255) };

int maxcolors = sizeof(colors)/sizeof(ULONG);

static turbograph __Current ;

typedef int64_t int64;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI windowsetup(HINSTANCE hInstance) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_WINLOGO); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","BGIGRAPH",WS_VISIBLE|WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	__Current.initialized = true;
	__Current.hwnd = hwnd;
	__Current.wc = wc;
	__Current.bgcolor = BLACK;
	__Current.msg = msg;
	__Current.color = WHITE;
	__Current.hdcWindow = BeginPaint(hwnd, &__Current.ps);
	__Current.fillpattern = EMPTY_FILL;
	__Current.fillcolor = BLACK;
	__Current.charsize = 12;
	__Current.direction = 0;
	__Current.fontnum = DEFAULT_FONT;
	__Current.font = CreateFont(12, 0, 0, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Arial");
	__Current.linestyle = SOLID_LINE;
	__Current.linepattern = 0;
	__Current.linethickness = 1;
	RECT rc;
   	GetClientRect(__Current.hwnd, &rc);
   	__Current.activeviewport.left = 0;
   	__Current.activeviewport.top = 0;
   	__Current.activeviewport.right = rc.right;
   	__Current.activeviewport.bottom  = rc.bottom;
   	__Current.activeviewport.clip = false;
	return msg.wParam;
}

void clearviewport();

void graphdefaults(void)
{
	__Current.bgcolor = BLACK;
	__Current.color = WHITE;
	__Current.fillpattern = EMPTY_FILL;
	__Current.fillcolor = BLACK;
	__Current.charsize = 12;
	__Current.direction = 0;
	__Current.fontnum = DEFAULT_FONT;
	DeleteObject(__Current.font);
	__Current.font = CreateFont(12, 0, 0, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Arial");
	__Current.linestyle = SOLID_LINE;
	__Current.linepattern = 0;
	__Current.linethickness = 1;
	clearviewport();
}

int getmaxcolor(void)
{
	return maxcolors;
}

ULONG tc2wc(int tc)
{
	return colors[tc];
}

int wc2tc(uint64_t wc)
{
  	int i;
	for(i=0;i<maxcolors;i++)
	{
		if(colors[i] == wc) return i;
	}
	return -1;
}

void restorecrtmode(void)
{
	BringWindowToTop(__Current.Cnhwnd);
}

void setgraphmode(int mode)
{
	if(mode >=0 and mode <= 5 )
	BringWindowToTop(__Current.hwnd);
}

#endif
