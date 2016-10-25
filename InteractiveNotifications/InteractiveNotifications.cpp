// InteractiveNotifications.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
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
#include <windows.ui.notifications.h>
#include <windows.ui.notifications.h>
#include "NotificationActivationCallback.h"

//  Name:     System.AppUserModel.ToastActivatorCLSID -- PKEY_AppUserModel_ToastActivatorCLSID
//  Type:     Guid -- VT_CLSID
//  FormatID: {9F4C2855-9F79-4B39-A8D0-E1D42DE1D5F3}, 26
//  
//  Used to CoCreate an INotificationActivationCallback interface to notify about toast activations.
EXTERN_C const PROPERTYKEY DECLSPEC_SELECTANY PKEY_AppUserModel_ToastActivatorCLSID = { { 0x9F4C2855, 0x9F79, 0x4B39,{ 0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3 } }, 26 };


using namespace ABI::Windows::Data::Xml::Dom;
using namespace ABI::Windows::UI::Notifications;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

struct CoTaskMemStringTraits
{
	typedef PWSTR Type;

	inline static bool Close(_In_ Type h) throw() { ::CoTaskMemFree(h); return true; }

	inline static Type GetInvalidValue() throw() { return nullptr; }
};
typedef HandleT<CoTaskMemStringTraits> CoTaskMemString;

// Todo: Make this magically dynamic
const wchar_t AppId[] = L"Felix.Lol.WhatAmIDoing";

// For the app to be activated from Action Center, it needs to provide a COM server to be called
// when the notification is activated.  The CLSID of the object needs to be registered with the
// OS via its shortcut so that it knows who to call later.
class DECLSPEC_UUID("23A5B06E-20BB-4E7E-A0AC-6982ED6A6041") NotificationActivator WrlSealed
: public RuntimeClass < RuntimeClassFlags<ClassicCom>,
	INotificationActivationCallback > WrlFinal
{
public:
	virtual HRESULT STDMETHODCALLTYPE Activate(
		_In_ LPCWSTR /*appUserModelId*/,
		_In_ LPCWSTR /*invokedArgs*/,
		/*_In_reads_(dataCount)*/ const NOTIFICATION_USER_INPUT_DATA* /*data*/,
		ULONG /*dataCount*/) override
	{
		return HRESULT();
	}
};
CoCreatableClass(NotificationActivator);

namespace InteractiveNotifications
{
	INTERACTIVENOTIFICATIONS_API double InteractiveNotificationsManager::Add(double a, double b)
	{
		// Sanity check
		return a + b;
	}

	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::RegisterAppForNotificationSupport()
	{
		return HRESULT();
	}

	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::InstallShortcut(PCWSTR shortcutPath, PCWSTR exePath)
	{
		return HRESULT();
	}

	_Use_decl_annotations_
	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::RegisterComServer(PCWSTR exePath)
	{
		// We don't need to worry about overflow here as ::GetModuleFileName won't
		// return anything bigger than the max file system path (much fewer than max of DWORD).
		DWORD dataSize = static_cast<DWORD>((::wcslen(exePath) + 1) * sizeof(WCHAR));

		// We should figure out what the hell we actually want to do here
		return HRESULT_FROM_WIN32(::RegSetKeyValue(
			HKEY_CURRENT_USER,
			LR"(SOFTWARE\Classes\CLSID\{23A5B06E-20BB-4E7E-A0AC-6982ED6A6041}\LocalServer32)",
			nullptr,
			REG_SZ,
			reinterpret_cast<const BYTE*>(exePath),
			dataSize));
	}

	_Use_decl_annotations_
	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::RegisterActivator()
	{
		// Module<OutOfProc> needs a callback registered before it can be used.
		// Since we don't care about when it shuts down, we'll pass an empty lambda here.
		// That being said, I'm not sure if that's even true?
		Module<OutOfProc>::Create([] {});

		// If a local server process only hosts the COM object then COM expects
		// the COM server host to shutdown when the references drop to zero.
		// Since the user might still be using the program after activating the notification,
		// we don't want to shutdown immediately.  Incrementing the object count tells COM that
		// we aren't done yet.
		Module<OutOfProc>::GetModule().IncrementObjectCount();

		return Module<OutOfProc>::GetModule().RegisterObjects();
	}

	_Use_decl_annotations_
	INTERACTIVENOTIFICATIONS_API void InteractiveNotificationsManager::UnregisterActivator()
	{
		Module<OutOfProc>::GetModule().UnregisterObjects();
		Module<OutOfProc>::GetModule().DecrementObjectCount();
	}
}