
#ifndef GRAPHICSHFH__H
#define GRAPHICSHFH__H

#include "winGraphics.cpp"

#ifdef _INC_CONIO
#error cannot use conio.h with graphics.h
#endif

void setbkcolor(int color);

int getch()
{
	if(__Current.initialized == false) return 0 ;
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg);/* Translate key codes to chars if present */
		//printf("\nmessage = %u %lu ,point = %ld,%ld",msg.message,msg.wParam,msg.pt.x,msg.pt.y);
		if(msg.message == WM_CHAR )
			return msg.wParam;
		else 
			DispatchMessage(&msg); /* Send it to WndProc */
	}
	return 0;
}
int kbhit()
{
	if(__Current.initialized == false) return 0 ;
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg);/* Translate key codes to chars if present */
		//printf("\nmessage = %u %lu ,point = %ld,%ld",msg.message,msg.wParam,msg.pt.x,msg.pt.y);
		if(msg.message == WM_KEYDOWN )
			return true;
		else
			DispatchMessage(&msg); /* Send it to WndProc */
	}
	return false;
}

void setgraphresult(int errcd)
{
	__Current.grErrorCode = errcd;
}

void detectgraph(int * graphdriver,int * graphmode)
{
	*graphdriver = 0 ;
	*graphmode = 0 ;
}

void initgraph(int * gd ,int*gm ,const char * path)
{
	*gd = 0;*gm=0;
	if(gd == 0|| strlen(path) )
	{
		setgraphresult(grOk);
	}
	HINSTANCE hInstance = GetModuleHandle(NULL);
	windowsetup(hInstance);
	int i;
	for(i=0;i<getmaxcolor();i++)
	{
		__Current.activepalette.colors[i] = i;
	}
	__Current.activepalette.size = 15;
	__Current.Cnhwnd = GetConsoleWindow();
}

void clearviewport(void)
{
	RECT rc;
   	GetClientRect(__Current.hwnd, &rc);
   	__Current.activeviewport.left = 0;
   	__Current.activeviewport.top = 0;
   	__Current.activeviewport.right = rc.right;
   	__Current.activeviewport.bottom  = rc.bottom;
   	__Current.activeviewport.clip = false;
   	setbkcolor(BLACK);
}

void getviewsettings(struct viewporttype * viewport)
{
	*viewport = __Current.activeviewport;
}

void rectangle( int left, int top, int right, int bottom );
int getmaxx();
int getmaxy();

void setviewport(int left, int top, int right, int bottom,int clip)
{
	RECT rect;
	rect.left=0;
	rect.right=getmaxx();
	rect.top=0;
	rect.bottom=top;
	HBRUSH hbrsh = CreateSolidBrush(RGB(0,0,0));
	FillRect(__Current.hdcWindow,&rect,hbrsh);
	
	rect.left=0;
	rect.right=left;
	rect.top=top;
	rect.bottom=bottom;
	FillRect(__Current.hdcWindow,&rect,hbrsh);
	
	rect.left=0;
	rect.right=getmaxx();
	rect.top=bottom;
	rect.bottom=getmaxy();
	FillRect(__Current.hdcWindow,&rect,hbrsh);
	
	rect.left=right;
	rect.right=getmaxx();
	rect.top=top;
	rect.bottom=bottom;
	FillRect(__Current.hdcWindow,&rect,hbrsh);
	
	rectangle(left,top,right,bottom);
	__Current.activeviewport.bottom = bottom;
	__Current.activeviewport.clip = clip;
	__Current.activeviewport.left = left;
	__Current.activeviewport.right = right;
	__Current.activeviewport.top = top;
	
}

int getmaxx()
{
   	return __Current.activeviewport.right - __Current.activeviewport.left;
}

int getmaxy()
{
   	return __Current.activeviewport.bottom - __Current.activeviewport.top;
}

bool isWithinViewPort(int x, int y)
{
	int maxx = __Current.activeviewport.right;
	int maxy  = __Current.activeviewport.bottom;
	if(__Current.activeviewport.clip)
	{
		if( x > __Current.activeviewport.left && x < maxx )
		{
			if( y < maxy && y > __Current.activeviewport.top ) 
			return true;
		}
	}
	else
	{
		if( x == __Current.activeviewport.left || x == maxx )
		{
			if( y == maxy || y == __Current.activeviewport.top ) 
			return false;
		}
		return true;
	}
	return false;
}

void putpixel(int x,int y,int color)
{
	if(__Current.initialized == false)return ;
	if((signed)color == -1)color = __Current.color;
	x = __Current.activeviewport.left + x;
	y = __Current.activeviewport.top + y;
	if(isWithinViewPort(x,y))SetPixel(__Current.hdcWindow,x,y,tc2wc(color));
}

int getpixel(int x, int y)
{
	x = __Current.activeviewport.left + x;
	y = __Current.activeviewport.top + y;
	return wc2tc(GetPixel(__Current.hdcWindow,x,y));
}

int getbkcolor()
{
	return __Current.bgcolor;
}

void setbkcolor(int color)
{
	__Current.bgcolor = color ;
	HBRUSH hBrush = CreateSolidBrush(tc2wc(color));
	FillRect(__Current.hdcWindow,&__Current.ps.rcPaint,hBrush);
	DeleteObject(hBrush);
}

void setcolor(int color)
{
	__Current.color = color;
}
int getcolor()
{
	return __Current.color;
}

BYTE Internalgetfillpattern()
{
	return __Current.fillpattern;
}

int getfillcolor()
{
	return __Current.fillcolor;
}

void setfillstyle(int pattern, int color)
{
	__Current.fillpattern = pattern;
	__Current.fillcolor = color;
}

void getpalette(struct palettetype * palette)
{
	*palette = __Current.activepalette;
}

struct palettetype *getdefaultpalette( void )
{
	return &__Current.activepalette;
}

int getpalettesize( void )
{
	return __Current.activepalette.size;
}

void setpalette(int colornum, int color)
{
	__Current.activepalette.colors[colornum] = color;
}

void setallpalette(const struct palettetype * palette)
{
	__Current.activepalette = *palette;
}

int getgraphmode(void)
{
	return VGAHI;
}

int graphresult(void)
{
	return __Current.grErrorCode;
}

const char* grapherrormsg(int errorcode)
{
    switch(errorcode)
    {
    	case grOk :
    		return "GrOK";
    	case grNoInitGraph :
    		return "grNoInitGraph";
    	case grNotDetected :
    		return "grNotDetected";
		case grFileNotFound :
			return "grFileNotFound";
		case grInvalidDriver :
			return "grInvalidDriver";
		case grNoLoadMem :
			return "grNoLoadMem";
		case grNoScanMem :
			return "grNoScanMem";
		case grNoFloodMem :
			return "grNoFloodMem";
		case grFontNotFound :
			return "grFontNotFound";
		case grNoFontMem :
			return "grNoFontMem";
		case grInvalidMode :
			return "grInvalidMode";
		case grInvalidVersion :
			return "grInvalidVersion";
		case grIOerror :
			return "grIOerror";
		case grInvalidFont :
			return "grInvalidFont";
  		case grInvalidFontNum :
			return "grInvalidFontNum";
		default :
			return "grError";
	}
}

void closegraph(void)
{
	if(__Current.initialized == false)return ;
	//freedict(__Current.ColorIndex);
	ReleaseDC(__Current.hwnd,__Current.hdcWindow);
	EndPaint(__Current.hwnd, &__Current.ps);
	DestroyWindow(__Current.hwnd);
}

#endif


