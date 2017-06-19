//============================================================================
// Name        : DooR.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string>
#include "Door.h"
using namespace std;

int main()
{
	 int doorWidth;

	    std::cout << "enter door width: " << std::endl;
	    std::cin >> doorWidth;

	    int doorHeigth;

	    std::cout << "enter door heigth: " << std::endl;
	    std::cin >> doorHeigth;

	    std::string doorColor;

	    std::cout << "enter door color: " << std::endl;
	    std::cin >> doorColor;

	    Door door(doorWidth, doorHeigth, doorColor);
	    return 0;
}
