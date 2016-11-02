#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//InteractiveTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InteractiveNotifications.h"

#include <iostream>
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

using namespace ABI::Windows::Foundation;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

int main()
{
	// Also: Fuck, how do we even do that in Node
	// If we're not single threaded stuff will be less fun
	//RoInitializeWrapper winRtInitializer(RO_INIT_MULTITHREADED);
	//CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	CoInitialize(nullptr);

	const wchar_t appId[] = L"Felix.Lol.Test";
	const wchar_t shortcut[] = LR"(Microsoft\Windows\Start Menu\Lol.lnk)";

	HRESULT hr = InteractiveNotifications::RegisterAppForNotificationSupport(shortcut, appId);
	
	if (SUCCEEDED(hr))
	{
		cout << "\nRegisterAppForNotificationSupport worked..." << endl;
	}

	hr = InteractiveNotifications::RegisterActivator();

	if (SUCCEEDED(hr))
	{
		cout << "RegisterActivator worked..." << endl;
	}

	if (SUCCEEDED(hr))
	{
		cout << "Sending test notification worked..." << endl;
	}

	//system("pause");

	return 0;
}

