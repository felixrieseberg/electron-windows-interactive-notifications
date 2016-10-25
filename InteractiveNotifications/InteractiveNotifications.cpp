// InteractiveNotifications.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "InteractiveNotifications.h"
#include "NotificationActivationCallback.h"

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


// Correct flow
// RegisterAppForNotificationSupport()
// RegisterActivator()

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
		CoTaskMemString appData;
		auto hr = ::SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, appData.GetAddressOf());

		if (SUCCEEDED(hr))
		{
			wchar_t shortcutPath[MAX_PATH];
			// Todo: Don't hardcode the path
			hr = ::PathCchCombine(shortcutPath, ARRAYSIZE(shortcutPath), appData.Get(), LR"(Microsoft\Windows\Start Menu\Lol.lnk)");

			if (SUCCEEDED(hr))
			{
				DWORD attributes = ::GetFileAttributes(shortcutPath);
				bool fileExists = attributes < 0xFFFFFFF;

				if (!fileExists)
				{
					// Todo: This is probably the wrong path bc Squirrel
					wchar_t exePath[MAX_PATH];
					DWORD charWritten = ::GetModuleFileName(nullptr, exePath, ARRAYSIZE(exePath));
					hr = charWritten > 0 ? S_OK : HRESULT_FROM_WIN32(::GetLastError());

					if (SUCCEEDED(hr))
					{
						hr = InstallShortcut(shortcutPath, exePath);
						if (SUCCEEDED(hr))
						{
							hr = RegisterComServer(exePath);
						}
					}
				}
			}
		}
		return hr;
	}

	_Use_decl_annotations_
	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::InstallShortcut(PCWSTR shortcutPath, PCWSTR exePath)
	{
		// This looks like callback hell, this should be cleaner
		ComPtr<IShellLink> shellLink;
		HRESULT hr = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shellLink));
		if (SUCCEEDED(hr))
		{
			hr = shellLink->SetPath(exePath);
			if (SUCCEEDED(hr))
			{
				ComPtr<IPropertyStore> propertyStore;

				hr = shellLink.As(&propertyStore);
				if (SUCCEEDED(hr))
				{
					PROPVARIANT propVar;
					propVar.vt = VT_LPWSTR;
					propVar.pwszVal = const_cast<PWSTR>(AppId); // for _In_ scenarios, we don't need a copy
					hr = propertyStore->SetValue(PKEY_AppUserModel_ID, propVar);
					if (SUCCEEDED(hr))
					{
						propVar.vt = VT_CLSID;
						propVar.puuid = const_cast<CLSID*>(&__uuidof(NotificationActivator));
						hr = propertyStore->SetValue(PKEY_AppUserModel_ToastActivatorCLSID, propVar);
						if (SUCCEEDED(hr))
						{
							hr = propertyStore->Commit();
							if (SUCCEEDED(hr))
							{
								ComPtr<IPersistFile> persistFile;
								hr = shellLink.As(&persistFile);
								if (SUCCEEDED(hr))
								{
									hr = persistFile->Save(shortcutPath, TRUE);
								}
							}
						}
					}
				}
			}
		}
		return hr;
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

	_Use_decl_annotations_
	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::CreateToastXml(IToastNotificationManagerStatics* toastManager, IXmlDocument** inputXml)
	{
		*inputXml = nullptr;

		// Retrieve the xml
		// Todo: lol this isn't even right
		HRESULT hr = toastManager->GetTemplateContent(ToastTemplateType_ToastImageAndText04, inputXml);
		return hr;
	}

	_Use_decl_annotations_
	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::CreateToast(IToastNotificationManagerStatics* toastManager, IXmlDocument* xml)
	{
		ComPtr<IToastNotifier> notifier;
		HRESULT hr = toastManager->CreateToastNotifierWithId(HStringReference(AppId).Get(), &notifier);
		if (SUCCEEDED(hr))
		{
			ComPtr<IToastNotificationFactory> factory;
			hr = Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotification).Get(), &factory);
			if (SUCCEEDED(hr))
			{
				ComPtr<IToastNotification> toast;
				hr = factory->CreateToastNotification(xml, &toast);

				if (SUCCEEDED(hr))
				{
					// Register the event handlers
					EventRegistrationToken activatedToken, dismissedToken, failedToken;

					using namespace ABI::Windows::Foundation;

					hr = toast->add_Activated(
						Callback < Implements < RuntimeClassFlags<ClassicCom>,
						ITypedEventHandler<ToastNotification*, IInspectable* >> >(
							[](IToastNotification*, IInspectable*)
					{
						// When the user clicks or taps on the toast, the registered
						// COM object is activated, and the Activated event is raised.
						// There is no guarantee which will happen first.
						return S_OK;
					}).Get(), &activatedToken);

					if (SUCCEEDED(hr))
					{
						hr = toast->add_Dismissed(Callback < Implements < RuntimeClassFlags<ClassicCom>,
							ITypedEventHandler<ToastNotification*, ToastDismissedEventArgs* >> >(
								[](IToastNotification*, IToastDismissedEventArgs* e)
						{
							ToastDismissalReason reason;

							// This could be useful, but who knows, amirite?
							if (SUCCEEDED(e->get_Reason(&reason)))
							{
								switch (reason)
								{
								case ToastDismissalReason_ApplicationHidden:
									break;
								case ToastDismissalReason_UserCanceled:
									break;
								case ToastDismissalReason_TimedOut:
									break;
								default:
									break;
								}
							}
							return S_OK;
						}).Get(), &dismissedToken);

						if (SUCCEEDED(hr))
						{
							hr = toast->add_Failed(Callback < Implements < RuntimeClassFlags<ClassicCom>,
								ITypedEventHandler<ToastNotification*, ToastFailedEventArgs* >> >(
									[](IToastNotification*, IToastFailedEventArgs* /*e */)
							{
								// Oh noes errors
								return S_OK;
							}).Get(), &failedToken);

							if (SUCCEEDED(hr))
							{
								hr = notifier->Show(toast.Get());
							}
						}
					}

				}
			}
		}

		return hr;
	}

	_Use_decl_annotations_
	INTERACTIVENOTIFICATIONS_API HRESULT InteractiveNotificationsManager::SendTestToast() {
		ComPtr<IToastNotificationManagerStatics> toastStatics;
		HRESULT hr = Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager).Get(), &toastStatics);

		if (SUCCEEDED(hr))
		{
			ComPtr<IXmlDocument> toastXml;
			hr = CreateToastXml(toastStatics.Get(), &toastXml);
			if (SUCCEEDED(hr))
			{
				hr = CreateToast(toastStatics.Get(), toastXml.Get());
			}
		}
		return hr;
	}
}