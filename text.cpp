

#ifndef GRAPHICSDOTHTEXT_H
#define GRAPHICSDOTHTEXT_H

#include "HF.cpp"
#include "lines.cpp"

const char * bgifontnames[] = { "DEFAULT font","TRIPLEX font","SMALL font","SANS SERIF_font", "GOTHIC_font","SCRIPT font","SIMPLEX font",
"TRIPLEX SCRIPT font","COMPLEX font","EUROPEAN font","BOLD font"};

extern pointtype LineActivePoints ;
extern turbograph __Current;

int textheight(const char *textstring)
{
	SIZE s ;
	GetTextExtentPoint32(__Current.hdcWindow,textstring,strlen(textstring),&s);
	return s.cy;
}

int textwidth(const char *textstring)
{
	SIZE s ;
	GetTextExtentPoint32(__Current.hdcWindow,textstring,strlen(textstring),&s);
	return s.cx;
}

void settextjustify(int horiz, int vert)
{
	__Current.horitextjust = horiz;
	__Current.vertextjust = vert;
}

pointtype processtextjust(int x,int y,int textwidth,int textheight)
{
	if(__Current.horitextjust == CENTER_TEXT)
	{
		x -= textwidth>>1;
	}
	else if( __Current.horitextjust == RIGHT_TEXT )
	{
		x -= textwidth;
	}
	if(__Current.vertextjust == CENTER_TEXT )
	{
		y -= textheight>>1;
	}
	else if( __Current.vertextjust == BOTTOM_TEXT )
	{
		y -= textheight;
	}
	pointtype p = {x,y};
	return p;
}

int bgicharheight =0 , bgicharwidth=0 ;

void initializeFont(int font,int direction,int size)
{
	if(__Current.font != 0)
	{
		DeleteObject(__Current.font);
	}
	int orient ;
	if(direction == HORIZ_DIR )
	{
		orient = 0;
	}
	else
	{
		orient = 2700;
	}
	int cheight , cwidth ;
	if(size == 0)
	{
		cheight = bgicharheight;
		cwidth = bgicharwidth;
	}
	else
	{
		cheight = -MulDiv(size, GetDeviceCaps(__Current.hdcWindow, LOGPIXELSY), 72);
		cwidth = 0;
	}
	switch(font)
	{
		case TRIPLEX_FONT : {
			__Current.font = CreateFont(cheight, cwidth, orient, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Times New Roman");
			if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
		case SMALL_FONT : {
			__Current.font = CreateFont((cheight>>1)+1, (cwidth>>1)+1, orient, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Arial");
		    if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
		case DEFAULT_FONT : {
			__Current.font = CreateFont(cheight, cwidth, orient, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Arial");
		    if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
		case SANS_SERIF_FONT : {
			__Current.font = CreateFont(cheight, cwidth, orient, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Tw Cen MT Condensed");
		    if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
		case GOTHIC_FONT : {
			__Current.font = CreateFont(cheight, cwidth, orient, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Old English Text MT");
		    if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
		case SCRIPT_FONT : {
			__Current.font = CreateFont(cheight, cwidth, orient, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Script MT Bold");
		    if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
		case BOLD_FONT : {
			__Current.font = CreateFont(cheight, cwidth, orient, 0,FW_BOLD, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Arial");
		    if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
		default : {
			__Current.font = CreateFont(cheight, cwidth, orient, 0,FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		         DEFAULT_PITCH | FF_ROMAN,"Arial");
		    if(__Current.font == NULL) setgraphresult(grFontNotFound);
			break;
		}
			
	}
}

int bgipreviouscharsize = 0;

void settextstyle(int font, int direction, int charsize)
{
	if(charsize == 0)
	{
		bgipreviouscharsize = __Current.charsize;
	}
	__Current.charsize = charsize;
	__Current.direction = direction;
	__Current.fontnum = font;
	if(charsize!=0)initializeFont(font,direction,charsize);
}

void setusercharsize(int multx, int divx,int multy, int divy)
{
	if(__Current.charsize == 0)
	{
		bgicharheight = (bgipreviouscharsize*multy)/divy;
		bgicharwidth = (bgipreviouscharsize*multx)/divx;
	}
	initializeFont(__Current.fontnum,__Current.direction,__Current.charsize);
}

void gettextsettings(struct textsettingstype *texttypeinfo)
{
	texttypeinfo->charsize = __Current.charsize;
	texttypeinfo->direction = __Current.direction;
	texttypeinfo->font = __Current.fontnum;
	texttypeinfo->horiz = __Current.horitextjust;
	texttypeinfo->vert = __Current.vertextjust;
}

void outtext(const char *textstring)
{
	SelectObject(__Current.hdcWindow,__Current.font);
	pointtype p = processtextjust(LineActivePoints.x,LineActivePoints.y,textwidth(textstring),textheight(textstring));
	SetTextColor(__Current.hdcWindow,tc2wc(getcolor()));
	SetBkMode(__Current.hdcWindow, TRANSPARENT);
	TextOut(__Current.hdcWindow,p.x,p.y,textstring,strlen(textstring));
}

void outtextxy(int x, int y, const char *textstring)
{
	SelectObject(__Current.hdcWindow,__Current.font);
	pointtype p = processtextjust(x,y,textwidth(textstring),textheight(textstring));
	SetTextColor(__Current.hdcWindow,tc2wc(getcolor()));
	SetBkMode(__Current.hdcWindow, TRANSPARENT);
	TextOut(__Current.hdcWindow,p.x,p.y,textstring,strlen(textstring));
}


#endif

