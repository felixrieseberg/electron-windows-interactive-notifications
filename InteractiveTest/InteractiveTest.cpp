// InteractiveTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "InteractiveNotifications.h"

using namespace std;
using namespace InteractiveNotifications;

int main()
{
	// Also: Fuck, how do we even do that in Node
	// If we're not single threaded stuff will be less fun
	CoInitialize(nullptr);

	// Sanity check
	double a = 1;
	double b = 99;

	cout << "Sanity check " << InteractiveNotificationsManager::Add(a, b);

	// Real check
	HRESULT hr = InteractiveNotificationsManager::RegisterAppForNotificationSupport();
	
	if (SUCCEEDED(hr))
	{
		cout << "\nRegisterAppForNotificationSupport worked..." << endl;
	}

	hr = InteractiveNotificationsManager::RegisterActivator();

	if (SUCCEEDED(hr))
	{
		cout << "RegisterActivator worked..." << endl;
	}

	hr = InteractiveNotificationsManager::SendTestToast();

	if (SUCCEEDED(hr))
	{
		cout << "Sending test notification worked..." << endl;
	}

	system("pause");

	return 0;
}

