// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the INTERACTIVENOTIFICATIONS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// INTERACTIVENOTIFICATIONS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef INTERACTIVENOTIFICATIONS_EXPORTS
#define INTERACTIVENOTIFICATIONS_API __declspec(dllexport)
#else
#define INTERACTIVENOTIFICATIONS_API __declspec(dllimport)
#endif

#include <windows.ui.notifications.h>

namespace InteractiveNotifications {
	INTERACTIVENOTIFICATIONS_API HRESULT RegisterAppForNotificationSupport(_In_ PCWSTR shortcut, _In_ PCWSTR appId);
	INTERACTIVENOTIFICATIONS_API HRESULT InstallShortcut(_In_ PCWSTR shortcutPath, _In_ PCWSTR exePath, _In_ PCWSTR appId);
	INTERACTIVENOTIFICATIONS_API HRESULT RegisterComServer(_In_ PCWSTR exePath);

	INTERACTIVENOTIFICATIONS_API HRESULT RegisterActivator();
	INTERACTIVENOTIFICATIONS_API void UnregisterActivator();
	INTERACTIVENOTIFICATIONS_API void silentActivation(_In_ PCWSTR shortcut, _In_ PCWSTR appId);

	// Sanity check
	INTERACTIVENOTIFICATIONS_API double Add(double a, double b);
		
	// Sample stuff - I'm not sure that the toast stuff needs to be here
	INTERACTIVENOTIFICATIONS_API HRESULT SendTestToast();

	INTERACTIVENOTIFICATIONS_API HRESULT CreateToastXml(
		_In_ ABI::Windows::UI::Notifications::IToastNotificationManagerStatics* toastManager,
		_COM_Outptr_ ABI::Windows::Data::Xml::Dom::IXmlDocument** xml);

	INTERACTIVENOTIFICATIONS_API HRESULT CreateToast(
		_In_ ABI::Windows::UI::Notifications::IToastNotificationManagerStatics* toastManager,
		_In_ ABI::Windows::Data::Xml::Dom::IXmlDocument* xml,
		_In_ PCWSTR appId
	);
}