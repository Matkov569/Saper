#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include "funlist.h"

using namespace std;

int main()
{
	SetConsoleTitleA("CMD Saper");

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	SMALL_RECT sr;

	sr.Left = 0;
	sr.Top = 0;
	sr.Right = 45;
	sr.Bottom = 37;
	SetConsoleWindowInfo(handle, true, &sr);
	
	srand(time(NULL));
    menu();

	return 0;
}