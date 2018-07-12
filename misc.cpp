

#ifndef GRAPHICSMISC_H
#define GRAPHICSMISC_H

#include"utility.cpp"

void delay( int msec )
{
	Sleep(msec);
}

void getaspectratio(int *xasp, int *yasp)
{
	*xasp = 4;
	*yasp = 3;
}

const char grDriver [] = "VGAHI";

const char *getdrivername( void )
{
	return grDriver;
}

int getmaxmode(void)
{
	return 2;
}

const char* getmodename( int mode_number )
{
	if(mode_number == 2)
	return grDriver;
	return "\0";
}

void getmoderange(int graphdriver, int *lomode,int *himode)
{
	if(graphdriver == VGA)
	{
		*lomode = 0;
		*himode = 2;
	}
}

#endif

