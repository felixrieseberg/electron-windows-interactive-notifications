#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//InteractiveTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "InteractiveNotifications.h"

#include <SDKDDKVer.h>
#include <Windows.h>
#include <Psapi.h>
#include <strsafe.h>
#include <ShObjIdl.h>
#include <Shlobj.h>
#include <Pathcch.h>
#include <propvarutil.h>
#include <propkey.h>
#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>

using namespace std;
using namespace InteractiveNotifications;

using namespace ABI::Windows::Foundation;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

int main()
{
	// Also: Fuck, how do we even do that in Node
	// If we're not single threaded stuff will be less fun
	//RoInitializeWrapper winRtInitializer(RO_INIT_MULTITHREADED);
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	// Sanity check
	double a = 1;
	double b = 99;

	cout << "Sanity check " << Add(a, b);

	// Real check
	HRESULT hr = RegisterAppForNotificationSupport();
	
	if (SUCCEEDED(hr))
	{
		cout << "\nRegisterAppForNotificationSupport worked..." << endl;
	}

	hr = RegisterActivator();

	if (SUCCEEDED(hr))
	{
		cout << "RegisterActivator worked..." << endl;
	}

	hr = SendTestToast();

	if (SUCCEEDED(hr))
	{
		cout << "Sending test notification worked..." << endl;
	}

	system("pause");

	return 0;
}

