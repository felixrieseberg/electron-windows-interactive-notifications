// InteractiveTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "InteractiveNotifications.h"

using namespace std;

int main()
{
	double a = 7.4;
	int b = 99;

	cout << "a + b = " <<
		InteractiveNotifications::Functions::Add(a, b) << endl;

	return 0;
}

