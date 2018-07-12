

#include "graphics.cpp"

int main()
{
	int gd=DETECT,gm;
	initgraph(&gd, &gm, "" );
	//setviewport(100,100,400,400,true);
    setcolor(WHITE);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setcolor(RED);
	circle(100,100,50);
	setcolor(WHITE);
	outtextxy(getmaxx()>>1,getmaxy()>>1,"THIS IS A WINDOWS BGI TEST PROGRAM.");
	outtextxy(getmaxx()>>1,(getmaxy()>>1)+textheight("THIS IS WINDOWS BGI TEST PROGRAM."),"Created by @SD.");
	setcolor(GREEN);
	ellipse(getmaxx()-100,getmaxy()-100,0,360,70,40);
	setcolor(YELLOW);
	rectangle(getmaxx()-150,50,getmaxx()-50,150);
	setcolor(BLUE);
	pieslice(100,getmaxy()-100,0,90,50);
    getch();
	closegraph();
	return 0;
}


