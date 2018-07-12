

#include "graphics.cpp"

int main()
{
	int gd=DETECT,gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI" );
    //setcolor(WHITE);
    setfillstyle(3,GREEN);
  	fillellipse(100,100,50,50);
//  ellipse(200,200,0,360,150,50);
//	circle(0,0,50);
	//setviewport(100,100,400,400,true);
//	floodfill(100,100,RED);
	int size = imagesize(50,50,150,150);
	void* ball = malloc(size);
	getimage(50,50,150,150,ball);
	int i;
	for(i=1;;i = (i+1)%10)
	{
		setbkcolor(BLACK);
		putimage(50+i*10,50,ball,COPY_PUT);
		delay(50);
	}
//
//	//floodfill(50,50,RED);
//	
//	bar3d(100,100,200,200,10,1);
	
	//floodfill(200,200,WHITE);
    getch();
	closegraph();
	return 0;
}


