
#include <windows.h>
#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <iostream>
#include <fstream>

#ifndef REDIRECTIO_H
#define REDIRECTIO_H

using namespace std;

static const WORD Mcl = 500;

void RedirectIO2Console()
{
	int hconhandle;
	long long lstdhandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE * fp;
	AllocConsole();
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
	coninfo.dwSize.Y = Mcl;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);
	
	lstdhandle = (long long) GetStdHandle(STD_OUTPUT_HANDLE);
	hconhandle = _open_osfhandle(lstdhandle,_O_TEXT);
	fp = _fdopen(hconhandle,"w");
	*stdout = *fp;
	setvbuf(stdout,NULL,_IONBF,0);
	
	lstdhandle = (long long) GetStdHandle(STD_INPUT_HANDLE);
	hconhandle = _open_osfhandle(lstdhandle,_O_TEXT);
	fp = _fdopen(hconhandle,"r");
	*stdin = *fp;
	setvbuf(stdin,NULL,_IONBF,0);
	
	lstdhandle = (long long) GetStdHandle(STD_ERROR_HANDLE);
	hconhandle = _open_osfhandle(lstdhandle,_O_TEXT);
	fp = _fdopen(hconhandle,"w");
	*stderr = *fp;
	setvbuf(stderr,NULL,_IONBF,0);
	
	ios::sync_with_stdio();
}

#endif

